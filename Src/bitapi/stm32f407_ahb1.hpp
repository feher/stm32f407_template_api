#pragma once

#include "stm32f407_mem.hpp"
#include "stm32f407_utils.hpp"

// Advanced High performance Bus 1.
namespace Stm32f407::Ahb1
{
    static constexpr Common::Address k_addr = Mem::k_peripheralsBaseAddr + 0x2'0000U;
    static constexpr Common::Address k_endAddr = Mem::k_peripheralsBaseAddr + 0x7'ffffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
} // namespace Stm32f407::Ahb1
