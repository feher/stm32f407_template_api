#pragma once

#include <array>
#include <atomic>
#include <cstdint> // size_t
#include <limits>
#include <optional>
#include <utility> // move

namespace Ds
{
    template <std::size_t N>
    concept IsPowerOfTwo = (N & (N - 1)) == 0;

    namespace Internal
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
    } // namespace Internal

} // namespace Ds
