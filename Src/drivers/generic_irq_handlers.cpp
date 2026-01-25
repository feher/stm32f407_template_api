#include "Src/bitapi/stm32f407_apb1_tim2_5.hpp"
#include "Src/bitapi/stm32f407_apb2_exti.hpp"

namespace Stm32f407::Driver::detail
{
    void sysTickHandler();
    void gpioIrqHandler(unsigned int extiLine);
    void timIrqHandler(unsigned int timerNumber);
} // namespace Stm32f407::Driver::detail

namespace
{

}

extern "C"
{
    void SysTick_Handler(void)
    {
        Stm32f407::Driver::detail::sysTickHandler();
    }

    void EXTI0_IRQHandler(void)
    {
        Stm32f407::Driver::detail::gpioIrqHandler(0);
    }

    void EXTI1_IRQHandler(void)
    {
        Stm32f407::Driver::detail::gpioIrqHandler(1);
    }

    void EXTI2_IRQHandler(void)
    {
        Stm32f407::Driver::detail::gpioIrqHandler(2);
    }

    void EXTI3_IRQHandler(void)
    {
        Stm32f407::Driver::detail::gpioIrqHandler(3);
    }

    void EXTI4_IRQHandler(void)
    {
        Stm32f407::Driver::detail::gpioIrqHandler(4);
    }

    void EXTI9_5_IRQHandler(void)
    {
        for (unsigned int line = 5; line <= 9; ++line)
        {
            if (Stm32f407::Bitapi::Apb2::Exti::Pr::Bits::get(static_cast<Stm32f407::Bitapi::Apb2::Exti::LineNumber>(
                        line)) == Stm32f407::Bitapi::Apb2::Exti::Pr::PrRead::Pending)
            {
                Stm32f407::Driver::detail::gpioIrqHandler(line);
            }
        }
    }

    void EXTI15_10_IRQHandler(void)
    {
        for (unsigned int line = 10; line <= 15; ++line)
        {
            if (Stm32f407::Bitapi::Apb2::Exti::Pr::Bits::get(static_cast<Stm32f407::Bitapi::Apb2::Exti::LineNumber>(
                        line)) == Stm32f407::Bitapi::Apb2::Exti::Pr::PrRead::Pending)
            {
                Stm32f407::Driver::detail::gpioIrqHandler(line);
            }
        }
    }

    void TIM2_IRQHandler(void)
    {
        // Clear the pending interrupt flag.
        if (Stm32f407::Bitapi::Apb1::Tim2_5::Tim2::Sr::Uif::get() !=
                Stm32f407::Bitapi::Apb1::Tim2_5::EventFlagRead::Pending)
        {
            return;
        }
        Stm32f407::Bitapi::Apb1::Tim2_5::Tim2::Sr::Uif::set(Stm32f407::Bitapi::Apb1::Tim2_5::EventFlagWrite::Clear);

        Stm32f407::Driver::detail::timIrqHandler(2);
    }
}
