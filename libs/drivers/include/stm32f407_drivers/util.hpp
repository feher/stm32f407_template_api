#pragma once

namespace Stm32f407::Driver::Util
{
    void busyWait(int ms);

    template <typename TPredicate>
    void busyWaitFor(TPredicate predicate)
    {
        // Wait for predicate to become true.
        while (predicate() == false)
        {
        }
    }
} // namespace Stm32f407::Driver::Util
