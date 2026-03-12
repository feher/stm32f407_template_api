#include "stm32f407_drivers/timer.hpp"

#include <stm32f407_bitapi/stm32f407_apb1_tim2_5.hpp>

#include <array>

namespace Stm32f407::Driver::detail
{
    std::array<IrqHandler, 5> g_timerIrqHandlers;

    void timIrqHandler(unsigned int timerNumber)
    {
        auto& handler = g_timerIrqHandlers[timerNumber - 1];
        if (handler != nullptr)
        {
            handler();
        }
    }
} // namespace Stm32f407::Driver::detail
