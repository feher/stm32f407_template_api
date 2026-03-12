#pragma once

#include <bit>

namespace Stm32f407::Bitapi::Clocks
{
    // LSI RC frequency.
    constexpr unsigned int k_lsiRcHz = 32'000; // 32 KHz

    // Is the HSE clock enabled.
    constexpr bool k_isHseEnabled = false;

    // HSE clock frequency.
    constexpr unsigned int k_hseHz = 8'000'000;
    consteval unsigned int getHseHz()
    {
        return k_isHseEnabled ? k_hseHz : 0;
    }

    // HSI RC oscillator.
    constexpr unsigned int k_hsiRcHz = 16'000'000;

    // Possible PLL sources.
    enum class PllSrc : unsigned int
    {
        HsiRc = 0,
        Hse = 1
    };

    // PLL source.
    constexpr PllSrc k_pllSrc = PllSrc::HsiRc;

    // PLL source frequency.
    constexpr unsigned int k_pllSrcHz = (k_pllSrc == PllSrc::HsiRc) ? k_hsiRcHz : getHseHz();
    static_assert(k_pllSrcHz != 0, "PLL source frequency cannot be zero.");

    // PLLM divider.
    constexpr unsigned int k_pllM = 8;
    static_assert(2 <= k_pllM && k_pllM <= 63, "PLL M out of range");

    // PLLN multiplier.
    constexpr unsigned int k_pllN = 168;
    static_assert(50 <= k_pllN && k_pllN <= 432, "PLL N out of range");

    // PLLP divider.
    constexpr unsigned int k_pllP = 2;
    static_assert(k_pllP == 2 || k_pllP == 4 || k_pllP == 6 || k_pllP == 8, "PLL P out of range");

    // PLLCLK frequency.
    constexpr unsigned int k_pllClkHz = (k_pllSrcHz / k_pllM) * k_pllN / k_pllP;

    // Possible SysClk sources.
    enum class SysClkSrc : unsigned int
    {
        HsiRc = 0,
        Hse = 1,
        PllClk = 2
    };

    // SysClk source.
    constexpr SysClkSrc k_sysClkSrc = SysClkSrc::HsiRc;

    // SysClk frequency.
    constexpr unsigned int k_sysClkHz = (k_sysClkSrc == SysClkSrc::Hse)     ? getHseHz()
                                        : (k_sysClkSrc == SysClkSrc::HsiRc) ? k_hsiRcHz
                                                                            : k_pllClkHz;
    static_assert(k_sysClkHz != 0, "SysClk frequency cannot be zero.");

    // AHB prescaler.
    constexpr unsigned int k_ahbPrescaler = 1;
    static_assert(1 <= k_ahbPrescaler && k_ahbPrescaler <= 256, "AHB prescaler out of range.");
    static_assert(std::popcount(k_ahbPrescaler) == 1, "AHB prescaler must be power of 2.");

    // HCLK frequency.
    constexpr unsigned int k_hclkHz = k_sysClkHz / k_ahbPrescaler;
    static_assert(k_hclkHz != 0, "HCLK frequency cannot be zero.");
    static_assert(k_hclkHz <= 168'000'000, "HCLK must be less than 168 Mhz.");

    // Ethernet PTP clock frequency.
    constexpr unsigned int k_ethernetPtpHz = k_hclkHz;

    // Clock frequency to AHB bus core, memory and DMA.
    constexpr unsigned int k_ahbMemDmaHz = k_hclkHz;

    // Cortex div.
    constexpr unsigned int k_cortexDiv = 1;
    static_assert(k_cortexDiv == 1 || k_cortexDiv == 8);

    // Cortex system timer frequency.
    constexpr unsigned int k_cortexSysTimerHz = k_hclkHz / k_cortexDiv;

    // FCLK cortex clock.
    constexpr unsigned int k_fclkCortexHz = k_hclkHz;

    // APB1 prescaler.
    constexpr unsigned int k_apb1Prescaler = 16;
    static_assert(1 <= k_apb1Prescaler && k_apb1Prescaler <= 16, "APB1 prescaler out of range.");
    static_assert(std::popcount(k_apb1Prescaler) == 1, "APB1 prescaler must be power of 2.");

    // PCLK1 frequency.
    constexpr unsigned int k_pclk1Hz = k_hclkHz / k_apb1Prescaler;
    static_assert(k_pclk1Hz <= 42'000'000, "PCLK1 must be less than 42 Mhz.");

    // APB1 peripheral clock frequency.
    constexpr unsigned int k_apb1Hz = k_pclk1Hz;

    // APB1 timer clocks frequency.
    constexpr unsigned int k_apb1TimersHz = k_pclk1Hz * 2;

    // APB2 prescaler.
    constexpr unsigned int k_apb2Prescaler = 2;
    static_assert(1 <= k_apb2Prescaler && k_apb2Prescaler <= 16, "APB2 prescaler out of range.");
    static_assert(std::popcount(k_apb2Prescaler) == 1, "APB2 prescaler must be power of 2.");

    // PCLK2 frequency.
    constexpr unsigned int k_pclk2Hz = k_hclkHz / k_apb2Prescaler;
    static_assert(k_pclk2Hz <= 84'000'000, "PCLK2 must be less than 84 Mhz.");

    // APB1 peripheral clock frequency.
    constexpr unsigned int k_apb2Hz = k_pclk2Hz;

    // APB1 timer clocks frequency.
    constexpr unsigned int k_apb2TimersHz = k_pclk2Hz * 2;

} // namespace Stm32f407::Bitapi::Clocks
