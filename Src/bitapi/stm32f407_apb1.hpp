#pragma once

#include "stm32f407_mem.hpp"
#include "stm32f407_utils.hpp"

// Advanced Peripheral Bus 1.
namespace Stm32f407::Apb1
{
    static constexpr Common::Address k_addr = Mem::k_peripheralsBaseAddr + 0x0U;
    static constexpr Common::Address k_endAddr = Mem::k_peripheralsBaseAddr + 0x7fffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
} // namespace Stm32f407::Apb1
