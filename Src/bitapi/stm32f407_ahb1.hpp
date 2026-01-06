#pragma once

#include "stm32f407_ahb1_gpio.hpp"
#include "stm32f407_ahb1_rcc.hpp"
#include "stm32f407_utils.hpp"

// Advanced High performance Bus 1.
namespace Ahb1
{
    static constexpr Address k_baseAddr = 0x4002'0000U;
    static constexpr Address k_endAddr = 0x4007'ffffU;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Ahb1
