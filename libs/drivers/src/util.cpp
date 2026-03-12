#include "stm32f407_drivers/util.hpp"

namespace Stm32f407::Driver::Util
{
    void busyWait(int ms)
    {
        // TODO: Calculate loop count from CPU clock frequency.
        for (int i = 0; i < ms * 1000; ++i)
        {
            // Nothing.
        }
    }
} // namespace Stm32f407::Driver::Util