#include <stm32f407_bitapi/stm32f407_apb1_tim2_5.hpp>
#include <stm32f407_bitapi/stm32f407_apb2_exti.hpp>

namespace Stm32f407::Driver::detail
{
    void sysTickHandler();
    void gpioIrqHandler(unsigned int extiLine);
    void timIrqHandler(unsigned int timerNumber);
} // namespace Stm32f407::Driver::detail

extern "C"
{
    void NMI_Handler(void)
    {
        while (true)
            ;
    }

    void HardFault_Handler(void)
    {
        while (true)
            ;
    }

    void MemManage_Handler(void)
    {
        while (true)
            ;
    }

    void BusFault_Handler(void)
    {
        while (true)
            ;
    }

    void UsageFault_Handler(void)
    {
        while (true)
            ;
    }

    void SVC_Handler(void)
    {
        while (true)
            ;
    }

    void DebugMon_Handler(void)
    {
        while (true)
            ;
    }

    void PendSV_Handler(void)
    {
        while (true)
            ;
    }

    void SysTick_Handler(void)
    {
        Stm32f407::Driver::detail::sysTickHandler();
    }

    void WWDG_IRQHandler(void)
    {
        while (true)
            ;
    }

    void PVD_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TAMP_STAMP_IRQHandler(void)
    {
        while (true)
            ;
    }

    void RTC_WKUP_IRQHandler(void)
    {
        while (true)
            ;
    }

    void RCC_IRQHandler(void)
    {
        while (true)
            ;
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

    void FPU_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream0_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream1_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream2_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream3_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream4_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream5_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream6_IRQHandler(void)
    {
        while (true)
            ;
    }

    void ADC_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN1_TX_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN1_RX0_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN1_RX1_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN1_SCE_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM1_BRK_TIM9_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM1_UP_TIM10_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM1_TRG_COM_TIM11_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM1_CC_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM3_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM4_IRQHandler(void)
    {
        while (true)
            ;
    }

    void I2C1_EV_IRQHandler(void)
    {
        while (true)
            ;
    }

    void I2C1_ER_IRQHandler(void)
    {
        while (true)
            ;
    }

    void I2C2_EV_IRQHandler(void)
    {
        while (true)
            ;
    }

    void I2C2_ER_IRQHandler(void)
    {
        while (true)
            ;
    }

    void SPI1_IRQHandler(void)
    {
        while (true)
            ;
    }

    void SPI2_IRQHandler(void)
    {
        while (true)
            ;
    }

    void USART1_IRQHandler(void)
    {
        while (true)
            ;
    }

    void USART2_IRQHandler(void)
    {
        while (true)
            ;
    }

    void USART3_IRQHandler(void)
    {
        while (true)
            ;
    }

    void RTC_Alarm_IRQHandler(void)
    {
        while (true)
            ;
    }

    void OTG_FS_WKUP_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM8_BRK_TIM12_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM8_UP_TIM13_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM8_TRG_COM_TIM14_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM8_CC_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA1_Stream7_IRQHandler(void)
    {
        while (true)
            ;
    }

    void FSMC_IRQHandler(void)
    {
        while (true)
            ;
    }

    void SDIO_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM5_IRQHandler(void)
    {
        while (true)
            ;
    }

    void SPI3_IRQHandler(void)
    {
        while (true)
            ;
    }

    void UART4_IRQHandler(void)
    {
        while (true)
            ;
    }

    void UART5_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM6_DAC_IRQHandler(void)
    {
        while (true)
            ;
    }

    void TIM7_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream0_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream1_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream2_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream3_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream4_IRQHandler(void)
    {
        while (true)
            ;
    }

    void ETH_IRQHandler(void)
    {
        while (true)
            ;
    }

    void ETH_WKUP_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN2_TX_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN2_RX0_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN2_RX1_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CAN2_SCE_IRQHandler(void)
    {
        while (true)
            ;
    }

    void OTG_FS_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream5_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream6_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DMA2_Stream7_IRQHandler(void)
    {
        while (true)
            ;
    }

    void USART6_IRQHandler(void)
    {
        while (true)
            ;
    }

    void I2C3_EV_IRQHandler(void)
    {
        while (true)
            ;
    }

    void I2C3_ER_IRQHandler(void)
    {
        while (true)
            ;
    }

    void OTG_HS_EP1_OUT_IRQHandler(void)
    {
        while (true)
            ;
    }

    void OTG_HS_EP1_IN_IRQHandler(void)
    {
        while (true)
            ;
    }

    void OTG_HS_WKUP_IRQHandler(void)
    {
        while (true)
            ;
    }

    void OTG_HS_IRQHandler(void)
    {
        while (true)
            ;
    }

    void DCMI_IRQHandler(void)
    {
        while (true)
            ;
    }

    void CRYP_IRQHandler(void)
    {
        while (true)
            ;
    }

    void HASH_RNG_IRQHandler(void)
    {
        while (true)
            ;
    }
}
