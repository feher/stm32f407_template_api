#pragma once

#include <array>
#include <atomic>
#include <cstdint> // size_t
#include <limits>
#include <optional>
#include <utility> // move

namespace Ao
{
    template <std::size_t N>
    concept PowerOfTwo = (N & (N - 1)) == 0;

    namespace detail
    {
        // Sets atomicVar to the result of newValueFunc if the predicate is true.
        // Returns (true, new value) if the predicate was true.
        // Returns (false, current value) if the predicate was false.
        template <typename TValue, typename TNewValueFunc, typename TPredicate>
        std::pair<bool, TValue> atomicCalcIf(
                std::atomic<TValue>& atomicVar, TNewValueFunc newValueFunc, TPredicate predicate)
        {
            TValue value = atomicVar.load();
            TValue newValue;
            do
            {
                if (predicate(value) == false)
                {
                    return std::make_pair(false, value);
                }
                newValue = newValueFunc(value);
            } while (atomicVar.compare_exchange_weak(value, newValue) == false);
            return std::make_pair(true, newValue);
        }

        // Sets atomicVar to newValue if the predicate is true.
        template <typename TValue, typename TPredicate>
        void atomicSetIf(std::atomic<TValue>& atomicVar, TValue newValue, TPredicate predicate)
        {
            TValue value = atomicVar.load();
            TValue v;
            do
            {
                v = predicate(value) ? newValue : value;
            } while (atomicVar.compare_exchange_weak(value, v) == false);
        }

        // Waits for the predicate to be true and sets atomicVar to newValue.
        template <typename TValue, typename TPredicate>
        void atomicWaitAndSet(std::atomic<TValue>& atomicVar, TValue newValue, TPredicate predicate)
        {
            TValue value = atomicVar.load();
            do
            {
                while (!predicate(value))
                {
                    // Wait for the predicate to become true.
                    value = atomicVar.load();
                }
            } while (atomicVar.compare_exchange_weak(value, newValue) == false);
        }
    } // namespace detail

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

    // Circular queue.
    // - fixed size
    // - not thread safe
    template <typename TItem, std::size_t TVSize>
        requires(TVSize >= 2)
    class CircularQueue
    {
    public:
        void add(TItem item)
        {
            m_buffer[m_tail] = item;
            m_tail = incPos(m_tail);
            if (m_tail == m_head)
            {
                m_head = incPos(m_head);
            }
        }

        std::optional<TItem> take()
        {
            if (isEmpty())
            {
                return {};
            }
            const auto itemPos = m_head;
            m_head = incPos(m_head);
            return m_buffer[itemPos];
        }

        bool isEmpty() const
        {
            return m_head == m_tail;
        }

        std::size_t count() const
        {
            if (m_head <= m_tail)
            {
                return m_tail - m_head;
            }
            return (TVSize - m_head) + m_tail;
        }

    private:
        std::size_t incPos(std::size_t pos)
        {
            return (pos + 1) % TVSize;
        }

        std::array<TItem, TVSize> m_buffer;
        std::size_t m_head = 0;
        std::size_t m_tail = 0;
    };

} // namespace Ao
