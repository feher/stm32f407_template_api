#pragma once

#include "stm32f407_utils.hpp"

namespace Stm32f407::Mem
{
    static constexpr Common::Word k_flashSize = 1 * 1024 * 1024; // 1 MiB
    static constexpr Common::Address k_flashBaseAddr = 0x0800'0000U;
    static constexpr Common::Address k_flashEndAddr = k_flashBaseAddr + k_flashSize - 1;

    static constexpr Common::Word k_sysMemSize = 0x7800; // 30 KiB
    static constexpr Common::Address k_sysMemBaseAddr = 0x1fff'0000U;
    static constexpr Common::Address k_sysMemEndAddr = k_sysMemBaseAddr + k_sysMemSize - 1;

    static constexpr Common::Address k_romBaseAddr = k_sysMemBaseAddr;

    static constexpr Common::Word k_sram1Size = 112 * 1024; // 112 KiB
    static constexpr Common::Address k_sram1BaseAddr = 0x2000'0000U;
    static constexpr Common::Address k_sram1EndAddr = k_sram1BaseAddr + k_sram1Size - 1;

    static constexpr Common::Word k_sram2Size = 16 * 1024; // 16 KiB
    static constexpr Common::Address k_sram2BaseAddr = k_sram1EndAddr + 1;
    static constexpr Common::Address k_sram2EndAddr = k_sram2BaseAddr + k_sram2Size - 1;
} // namespace Stm32f407::Mem
