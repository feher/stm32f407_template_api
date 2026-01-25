#include "timer.hpp"
#include "Src/bitapi/stm32f407_apb1_tim2_5.hpp"

#include <array>

namespace Stm32f407::Driver::detail
{
    std::array<TimerIrqHandler, 5> g_timerIrqHandlers;

    void timIrqHandler(unsigned int timerNumber)
    {
        auto& handler = g_timerIrqHandlers[timerNumber - 1];
        if (handler != nullptr)
        {
            handler();
        }
    }
} // namespace Stm32f407::Driver::detail
