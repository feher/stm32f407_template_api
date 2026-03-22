#pragma once

#include "atomic_utils.hpp"

#include <array>
#include <atomic>
#include <cstdint> // size_t
#include <limits>
#include <optional>
#include <utility> // move

namespace Ds
{
    //
    // h = head
    // t = tail
    //
    // Empty (h == t):
    //
    // h == t
    // |
    // .................
    //
    // Not empty (h != t, h < t)
    //
    //    h         t
    //    |         |
    // ...dddddddddd....
    //
    // Not empty (h != t, t < h)
    //
    //  t           h
    //  |           |
    // d............dddd
    //

    // Circular queue (thread-safe, lock free).
    // - fixed size
    // - multi producer
    // - multi consumer
    template <typename TItem, std::size_t TVSize, int TVDebugEatenItem = 0>
        requires(TVSize >= 1)
    class CircularQueueMpMcLf
    {
    public:
        CircularQueueMpMcLf()
        {
            // Only for debugging.
            std::ranges::fill(m_queue, 0);
        }

        bool add(TItem item)
        {
            // Pseudo code:
            //
            // 1: Signal about the "reservation" to other producers.
            // ++m_reservedTail;
            //
            // 2: Put the data to the reserved spot.
            // m_queue[m_reservedTail - 1] = item;
            //
            // 3: Signal about the "new data" to the consumers.
            // m_tail = m_reservedTail;

            // 0: Signal about the number of producers to other producers.
            ++m_producerCount;

            // 1: Reserve
            const auto maybeReservedTail = Internal::atomicCalcIf(
                    m_reservedTail, [](auto rtail) { return incPos(rtail); },
                    [this](auto rtail) { return !isFull(m_head.load(), rtail); });
            if (maybeReservedTail.first == false)
            {
                // const auto reservedTail = m_reservedTail.load();
                const auto reservedTail = maybeReservedTail.second;
                // We could not reserve a tail slot.
                // We are nevertheless an active producer. It is our responsibility to
                // update the tail, even if we did nothing.
                // For an explanation, see the comments for step 3 below.
                if (--m_producerCount == 0)
                {
                    // We detected that the producer-count became zero (or was zero for a moment).
                    // So, we can safely update m_tail up to the current snapshot of m_reservedTail.
                    // This operation is guaranteed to never decrease the value in m_tail.
                    Internal::atomicSetIf(m_tail, reservedTail,
                            [this, reservedTail](auto tail)
                            {
                                return reservedTail == m_reservedTail.load() &&
                                       canUpdateTail(m_head.load(), tail, reservedTail);
                            });
                }
                return false;
            }
            // const auto myReservedTail = *maybeReservedTail;
            const auto myReservedTail = maybeReservedTail.second;

            // 2: Put data
            m_queue[decPos(myReservedTail)] = item;
            // std::atomic_thread_fence(std::memory_order_seq_cst);

            // 3: Update the tail.
            // We try to update the tail only if we detect that we were the last producer (for a moment).
            // Otherwise, there are other active producers. It is their responsibility to update the head
            // when they are done.
            if (--m_producerCount == 0)
            {
                // We detected that the producer-count became zero (or was zero for a moment).
                // At this point, it is guaranteed that all data slots are filled
                // between [m_tail..myReservedTail - 1].
                // Proof:
                // If there is an unfilled slot then
                // a) it belongs to an __old__ active producer -> cannot be because we detected zero producer-count,
                //    even if only for a moment.
                // b) it belongs to an __new__ active producer -> cannot be because
                //    myReservedTail < newProducer.myReservedTail.
                //
                // So, we can safely update m_tail up to myReservedTail, but not to any larger value!
                // Reserved tails larger than myReservedTail belong to unfinished active producers
                // that just started "as we speak".
                Internal::atomicSetIf(m_tail, myReservedTail,
                        [this, myReservedTail](auto tail)
                        {
                            return myReservedTail == m_reservedTail.load() &&
                                   canUpdateTail(m_head.load(), tail, myReservedTail);
                        });
            }

            return true;
        }

        std::optional<TItem> take()
        {
            ++m_consumerCount;

            // 1: Reserve
            const auto maybeReservedHead = Internal::atomicCalcIf(
                    m_reservedHead, [](auto rhead) { return incPos(rhead); },
                    [this](auto rhead) { return !isEmpty(rhead, m_tail.load()); });
            if (maybeReservedHead.first == false)
            {
                // const auto reservedHead = m_reservedHead.load();
                const auto reservedHead = maybeReservedHead.second;
                // We could not reserve a head slot.
                // We are nevertheless an active consumer. It is our responsibility to
                // update the head, even if we did nothing.
                // For an explanation, see the comments for step 3 below.
                if (--m_consumerCount == 0)
                {
                    // We detected that the consumer-count became zero (or was zero for a moment).
                    // So, we can safely update m_head up to the current snapshot of m_reservedHead.
                    // This operation is guaranteed to never decrease the value of m_head.
                    Internal::atomicSetIf(m_head, reservedHead,
                            [this, reservedHead](auto head)
                            {
                                return reservedHead == m_reservedHead.load() &&
                                       canUpdateHead(head, m_tail.load(), reservedHead);
                            });
                }
                return {};
            }
            // const auto myReservedHead = *maybeReservedHead;
            const auto myReservedHead = maybeReservedHead.second;

            // 2: Take data
            const auto pos = decPos(myReservedHead);
            auto item = m_queue[pos];

            // This is used only for testing and debugging.
            if constexpr (TVDebugEatenItem != 0)
            {
                m_queue[pos] = TVDebugEatenItem;
            }
            // if (item == k_debugQueueEatenItem)
            // {
            //     item = k_debugQueueEatenItem + 1;
            // }
            // m_queue[pos] = k_debugQueueEatenItem; // std::numeric_limits<TItem>::max(); // Needed for debugging only.
            // std::atomic_thread_fence(std::memory_order_seq_cst);

            // 3: Update the head.
            // We try to update the head only if we detect that we were the last consumer (for a moment).
            // Otherwise, there are other active consumers. It is their responsibility to update the tail
            // when they are done.
            if (--m_consumerCount == 0)
            {
                // We detected that the consumer-count became zero (or was zero for a moment).
                // At this point, it is guaranteed that all data slots are consumed
                // between [m_head..myReservedHead - 1].
                // Proof:
                // If there is an un-consumed slot then
                // a) it belongs to an __old__ active consumer -> cannot be because we detected zero consumer-count,
                //    even if only for a moment.
                // b) it belongs to an __new__ active consumer -> cannot be because
                //    myReservedHead < newConsumer.myReservedHead.
                //
                // So, we can safely update m_head up to myReservedHead, but not to any larger value!
                // Reserved heads larger than myReservedHead belong to unfinished active consumers
                // that just started "as we speak".
                Internal::atomicSetIf(m_head, myReservedHead,
                        [this, myReservedHead](auto head)
                        {
                            return myReservedHead == m_reservedHead.load() &&
                                   canUpdateHead(head, m_tail.load(), myReservedHead);
                        });
            }

            return item;
        }

        bool isEmpty() const
        {
            return isEmpty(m_head, m_tail);
        }

        bool isFull() const
        {
            return isFull(m_head, m_tail);
        }

        std::size_t count() const
        {
            if (m_head <= m_tail)
            {
                return m_tail - m_head;
            }
            return (k_internalCapacity - m_head) + m_tail;
        }

    private:
        static std::size_t incPos(std::size_t pos)
        {
            return (pos == k_internalCapacity - 1) ? 0 : pos + 1;
        }

        static std::size_t decPos(std::size_t pos)
        {
            return (pos == 0) ? k_internalCapacity - 1 : pos - 1;
        }

        static bool isEmpty(std::size_t head, std::size_t tail)
        {
            return head == tail;
        }

        static bool isFull(std::size_t head, std::size_t tail)
        {
            return tail == decPos(head);
        }

        // True if head can be updated without jumping over the tail (towards the right).
        static bool canUpdateHead(std::size_t head, std::size_t tail, std::size_t newHead)
        {
            // Examples:
            //
            // Queue state         Can update?
            // |.....h..H..t....|  yes
            // |..H..h.....t....|  no
            // |.....h.....t..H.|  no
            // |..t..h....H.....|  yes
            // |H.t..h..........|  yes
            return (distanceRight(head, newHead) <= distanceRight(head, tail));
        }

        // True if tail can be updated without jumping over the head (towards the right).
        static bool canUpdateTail(std::size_t head, std::size_t tail, std::size_t newTail)
        {
            // Examples:
            //
            // Queue state         Can update?
            // |...h....t..T....|  yes
            // |...h..T.t.......|  no
            // |.T......t..h....|  no
            // |.T.h....t.......|  yes ???
            return (distanceRight(tail, newTail) <= distanceRight(tail, head));
        }

        // Distance to the right from a to b.
        static std::size_t distanceRight(std::size_t a, std::size_t b)
        {
            // Examples (with queue capacity 10):
            //
            // 0123456789  Distance
            // ...a....b.  5 (a < b)
            // ...b..a...  7 (a > b, overflowed)
            // ...a......  10 (a == b, overflowed)
            //    b

            // This is '<' and not '<=' on purpose!
            if (a < b)
            {
                return b - a;
            }
            else
            {
                return (k_internalCapacity + b) - a;
            }
        }

        static constexpr std::size_t k_internalCapacity = TVSize + 1;

        std::array<TItem, k_internalCapacity> m_queue;
        std::atomic_size_t m_head = 0;
        std::atomic_size_t m_tail = 0;

        // Each concurrent consumer reserves their read-slot.
        std::atomic_size_t m_reservedHead = 0;

        // Each concurrent producer reserves their write-slot.
        std::atomic_size_t m_reservedTail = 0;

        // Number of active concurrent producers.
        std::atomic_size_t m_producerCount = 0;

        // Number of active concurrent consumers.
        std::atomic_size_t m_consumerCount = 0;
    };

} // namespace Ds
