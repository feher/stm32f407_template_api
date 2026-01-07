#pragma once

#include "stm32f407_ahb1_gpio.hpp"
#include "stm32f407_ahb1_rcc.hpp"
#include "stm32f407_utils.hpp"

// Advanced High performance Bus 1.
namespace Stm32f407::Ahb1
{
    static constexpr Common::Address k_baseAddr = 0x4002'0000U;
    static constexpr Common::Address k_endAddr = 0x4007'ffffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Stm32f407::Ahb1
