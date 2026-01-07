#pragma once

#include "stm32f407_apb1_i2c.hpp"
#include "stm32f407_apb1_spi.hpp"
#include "stm32f407_apb1_usart.hpp"
#include "stm32f407_utils.hpp"

// Advanced Peripheral Bus 1.
namespace Stm32f407::Apb1
{
    static constexpr Common::Address k_baseAddr = 0x4000'0000U;
    static constexpr Common::Address k_endAddr = 0x4000'7fffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Stm32f407::Apb1
