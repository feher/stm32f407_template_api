#pragma once

#include "stm32f407_utils.hpp"

// Advanced High performance Bus 3.
namespace Ahb3
{
    static constexpr Address k_baseAddr = 0xa000'0000U;
    static constexpr Address k_endAddr = 0xa000'0fffU;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Ahb3
