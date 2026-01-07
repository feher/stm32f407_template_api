#pragma once

#include "stm32f407_utils.hpp"

// Advanced High performance Bus 2.
namespace Stm32f407::Ahb2
{
    static constexpr Common::Address k_baseAddr = 0x5000'0000U;
    static constexpr Common::Address k_endAddr = 0x5006'0bffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_baseAddr + 1;
} // namespace Stm32f407::Ahb2
