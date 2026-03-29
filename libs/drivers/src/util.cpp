#include "stm32f407_drivers/util.hpp"

#include <stm32f407_bitapi/stm32f407_clocks.hpp>

namespace Stm32f407::Driver::Util
{
    void busyWait(unsigned int Nms)
    {
        // TODO: Verify this calculation.
        // We calculate the loop count from CPU clock frequency.

        // Approximate cycles needed to perform one loop iteration.
        // We assume 2 cycles = check-counter + inc-counter
        constexpr auto cyclesPerForLoop = 2u;

        const auto cyclesPerNms = Stm32f407::Bitapi::Clocks::k_sysClkHz / (Nms * 1000u); // cycles / N ms

        const auto iterCount =  cyclesPerNms / cyclesPerForLoop;

        for (unsigned int i = 0u; i < iterCount; ++i)
        {
            // Nothing.
        }
    }
} // namespace Stm32f407::Driver::Util