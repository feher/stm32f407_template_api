#pragma once

#include "stm32f407_apb2_exti.hpp"
#include "stm32f407_apb2_spi.hpp"
#include "stm32f407_apb2_syscfg.hpp"
#include "stm32f407_apb2_usart.hpp"

// Advanced Peripheral Bus 2.
namespace Stm32f407::Apb2
{
    static constexpr Address k_baseAddr = 0x4001'0000U;
    static constexpr Address k_endAddr = 0x4001'6bffU;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Stm32f407::Apb2
