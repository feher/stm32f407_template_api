#pragma once

#include "atomic_utils.hpp"

#include <array>
#include <atomic>
#include <cstdint> // size_t
#include <limits>
#include <optional>
#include <utility> // move

namespace Ao
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

    static constexpr auto k_debugQueueEatenItem = 555555555;

    // Circular queue (thread-safe, lock free).
    // - fixed size
    // - multi producer
    // - multi consumer
    template <typename TItem, std::size_t TVSize>
        requires(TVSize >= 1 && PowerOfTwo<TVSize>)
    class CircularQueueMpMcLf3
    {
    public:
        CircularQueueMpMcLf3()
        {
            // Only for debugging.
            std::ranges::fill(m_queue, 0);
        }

        bool add(TItem item)
        {
            // 1: Reserve
            const auto maybeReservedTail = detail::atomicCalcIf(
                    m_reservedTail, [](auto rtail) { return incPos(rtail); },
                    [this](auto rtail) { return !isFull(m_head.load(), rtail); });
            if (maybeReservedTail.first == false)
            {
                return false;
            }
            // const auto myReservedTail = *maybeReservedTail;
            const auto myReservedTail = maybeReservedTail.second;

            // 2: Put data
            const auto pos = decPos(myReservedTail);
            const auto rpos = realPos(pos);
            m_queue[rpos] = item;
            // std::atomic_thread_fence(std::memory_order_seq_cst);

            // 3: Update the tail.
            detail::atomicWaitAndSet(m_tail, myReservedTail, [pos](auto tail) { return tail == pos; });

            return true;
        }

        std::optional<TItem> take()
        {
            // 1: Reserve
            const auto maybeReservedHead = detail::atomicCalcIf(
                    m_reservedHead, [](auto rhead) { return incPos(rhead); },
                    [this](auto rhead) { return !isEmpty(rhead, m_tail.load()); });
            if (maybeReservedHead.first == false)
            {
                return {};
            }
            // const auto myReservedHead = *maybeReservedHead;
            const auto myReservedHead = maybeReservedHead.second;

            // 2: Take data
            const auto pos = decPos(myReservedHead);
            const auto rpos = realPos(pos);
            auto item = m_queue[rpos];
            // if (item == k_debugQueueEatenItem)
            // {
            //     item = k_debugQueueEatenItem + 1;
            // }
            // m_queue[rpos] = k_debugQueueEatenItem; // Needed for debugging only.
            // std::atomic_thread_fence(std::memory_order_seq_cst);

            // 3: Update the head.
            detail::atomicWaitAndSet(m_head, myReservedHead, [pos](auto head) { return head == pos; });

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
            return count(m_head, m_tail);
        }

    private:
        static std::size_t realPos(std::size_t pos)
        {
            return pos % TVSize;
        }

        static std::size_t incPos(std::size_t pos)
        {
            return ++pos;
        }

        static std::size_t decPos(std::size_t pos)
        {
            return --pos;
        }

        static bool isEmpty(std::size_t head, std::size_t tail)
        {
            return head == tail;
        }

        static bool isFull(std::size_t head, std::size_t tail)
        {
            return count(head, tail) == TVSize;
        }

        static std::size_t count(std::size_t head, std::size_t tail)
        {
            if (head <= tail)
            {
                return tail - head;
            }
            else
            {
                // The tail wrapped around.
                return std::numeric_limits<std::size_t>::max() - head + tail;
            }
        }

        static constexpr std::size_t k_internalCapacity = TVSize;

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

} // namespace Ao
