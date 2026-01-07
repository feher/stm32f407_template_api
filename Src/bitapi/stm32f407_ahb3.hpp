#pragma once

#include "stm32f407_mem.hpp"
#include "stm32f407_utils.hpp"

// Advanced High performance Bus 3.
namespace Stm32f407::Ahb3
{
    static constexpr Common::Address k_addr = Mem::k_periAhb3BaseAddr;
    static constexpr Common::Address k_endAddr = Mem::k_periAhb3BaseAddr + 0x0fffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
} // namespace Stm32f407::Ahb3
