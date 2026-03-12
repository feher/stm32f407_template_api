#include "stm32f407_drivers/gpio.hpp"

namespace Stm32f407::Driver::detail
{
    std::array<IrqHandler, Bitapi::Apb2::Exti::k_lineCount> g_gpioIrqHandlers;

    void gpioIrqHandler(unsigned int extiLine)
    {
        // Clear the pending interrupt flag on EXTI.
        Bitapi::Apb2::Exti::Pr::Bits::set(
                static_cast<Bitapi::Apb2::Exti::LineNumber>(extiLine), Bitapi::Apb2::Exti::Pr::PrWrite::Clear);

        // Call the registered handler.
        auto& handler = g_gpioIrqHandlers[extiLine];
        if (handler != nullptr)
        {
            handler();
        }
    }
} // namespace Stm32f407::Driver::detail
