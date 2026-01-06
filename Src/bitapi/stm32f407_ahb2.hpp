#pragma once

#include "stm32f407_utils.hpp"

// Advanced High performance Bus 2.
namespace Ahb2
{
    static constexpr Address k_baseAddr = 0x5000'0000U;
    static constexpr Address k_endAddr = 0x5006'0bffU;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Ahb2
