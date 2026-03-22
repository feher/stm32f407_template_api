#pragma once

#include "atomic_utils.hpp"

#include <array>
#include <atomic>
#include <cstdint> // size_t
#include <limits>
#include <optional>
#include <utility> // move
#include <algorithm> // ranges::fill

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
    template <typename TItem, std::size_t TVSize, typename TIndex = std::size_t, int TVDebugEatenItem = 0>
        requires(TVSize >= 1 && IsPowerOfTwo<TVSize>)
    class CircularQueueMpMcLf3
    {
    public:
        CircularQueueMpMcLf3()
        {
            // Only for debugging.
            if constexpr (TVDebugEatenItem != 0)
            {
                std::ranges::fill(m_queue, TItem{});
            }
        }

        bool add(TItem item)
        {
            // 1: Reserve
            const auto maybeReservedTail = Internal::atomicCalcIf(
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
            Internal::atomicWaitAndSet(m_tail, myReservedTail, [pos](auto tail) { return tail == pos; });

            return true;
        }

        std::optional<TItem> take()
        {
            // 1: Reserve
            const auto maybeReservedHead = Internal::atomicCalcIf(
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

            // This is used only for testing and debugging.
            if constexpr (TVDebugEatenItem != 0)
            {
                m_queue[rpos] = TVDebugEatenItem;
            }
            // if (item == k_debugQueueEatenItem)
            // {
            //     item = k_debugQueueEatenItem + 1;
            // }
            // m_queue[rpos] = k_debugQueueEatenItem; // Needed for debugging only.
            // std::atomic_thread_fence(std::memory_order_seq_cst);

            // 3: Update the head.
            Internal::atomicWaitAndSet(m_head, myReservedHead, [pos](auto head) { return head == pos; });

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

        TIndex count() const
        {
            return count(m_head, m_tail);
        }

    private:
        // static constexpr std::size_t k_maxIndex = 16;
        static constexpr TIndex k_maxIndex = std::numeric_limits<TIndex>::max();

        static TIndex realPos(TIndex pos)
        {
            // If TVSize is power of 2 then (pos % TVSize) == (pos & (TVSize - 1)).
            return pos & (TVSize - 1);
        }

        static TIndex incPos(TIndex pos)
        {
            return ++pos;
        }

        static TIndex decPos(TIndex pos)
        {
            return --pos;
        }

        static bool isEmpty(TIndex head, TIndex tail)
        {
            return head == tail;
        }

        static bool isFull(TIndex head, TIndex tail)
        {
            // This is ">=" on purpose.
            // There is a case where the number of items may go over TVSize.
            // This may happen when the TIndex overflows.
            return count(head, tail) >= TVSize;
        }

        static TIndex count(TIndex head, TIndex tail)
        {
            if (head <= tail)
            {
                return tail - head;
            }
            else
            {
                // The tail wrapped around.
                return k_maxIndex + tail - head;
            }
        }

        std::array<TItem, TVSize> m_queue;

        std::atomic<TIndex> m_head = 0;
        std::atomic<TIndex> m_tail = 0;

        // Each concurrent consumer reserves their read-slot.
        std::atomic<TIndex> m_reservedHead = 0;

        // Each concurrent producer reserves their write-slot.
        std::atomic<TIndex> m_reservedTail = 0;
    };

} // namespace Ds
