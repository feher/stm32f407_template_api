#pragma once

#include "stm32f407_apb1_i2c.hpp"
#include "stm32f407_apb1_spi.hpp"
#include "stm32f407_apb1_usart.hpp"
#include "stm32f407_utils.hpp"

// Advanced Peripheral Bus 1.
namespace Apb1
{
    static constexpr Address k_baseAddr = 0x4000'0000U;
    static constexpr Address k_endAddr = 0x4000'7fffU;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Apb1
