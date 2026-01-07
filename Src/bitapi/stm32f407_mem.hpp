#pragma once

#include "stm32f407_utils.hpp"

#ifndef STM32F407_MEM_ADDR_FLASH_START
#define STM32F407_MEM_ADDR_FLASH_START 0x0800'0000U
#endif

#ifndef STM32F407_MEM_ADDR_SYS_START
#define STM32F407_MEM_ADDR_SYS_START 0x1fff'0000U
#endif

#ifndef STM32F407_MEM_ADDR_SRAM1_START
#define STM32F407_MEM_ADDR_SRAM1_START 0x2000'0000U
#endif

#ifndef STM32F407_MEM_ADDR_CORE_PERI_START
#define STM32F407_MEM_ADDR_CORE_PERI_START 0xe000'0000U
#endif

#ifndef STM32F407_MEM_ADDR_PERI_START
#define STM32F407_MEM_ADDR_PERI_START 0x4000'0000U
#endif

#ifndef STM32F407_MEM_ADDR_PERI_AHB3_START
#define STM32F407_MEM_ADDR_PERI_AHB3_START 0xa000'0000U
#endif

namespace Stm32f407::Mem
{
    static constexpr Common::Word k_flashSize = 1 * 1024 * 1024; // 1 MiB
    static constexpr Common::Address k_flashBaseAddr = STM32F407_MEM_ADDR_FLASH_START;
    static constexpr Common::Address k_flashEndAddr = k_flashBaseAddr + k_flashSize - 1;

    static constexpr Common::Word k_sysMemSize = 0x7800; // 30 KiB
    static constexpr Common::Address k_sysMemBaseAddr = STM32F407_MEM_ADDR_SYS_START;
    static constexpr Common::Address k_sysMemEndAddr = k_sysMemBaseAddr + k_sysMemSize - 1;

    static constexpr Common::Address k_romBaseAddr = k_sysMemBaseAddr;

    static constexpr Common::Word k_sram1Size = 112 * 1024; // 112 KiB
    static constexpr Common::Address k_sram1BaseAddr = STM32F407_MEM_ADDR_SRAM1_START;
    static constexpr Common::Address k_sram1EndAddr = k_sram1BaseAddr + k_sram1Size - 1;

    static constexpr Common::Word k_sram2Size = 16 * 1024; // 16 KiB
    static constexpr Common::Address k_sram2BaseAddr = k_sram1EndAddr + 1;
    static constexpr Common::Address k_sram2EndAddr = k_sram2BaseAddr + k_sram2Size - 1;

    static constexpr Common::Word k_corePeripheralsSize = 512 * 1024 * 1024; // 512 MiB
    static constexpr Common::Address k_corePeripheralsBaseAddr = STM32F407_MEM_ADDR_CORE_PERI_START;
    static constexpr Common::Address k_corePeripheralsEndAddr = k_corePeripheralsBaseAddr + k_corePeripheralsSize - 1;

    static constexpr Common::Word k_peripheralsSize = 512 * 1024 * 1024; // 512 MiB
    static constexpr Common::Address k_peripheralsBaseAddr = STM32F407_MEM_ADDR_PERI_START;
    static constexpr Common::Address k_peripheralsEndAddr = k_peripheralsBaseAddr + k_peripheralsSize - 1;

    static constexpr Common::Word k_periAhb3Size = 0x1000; // 4096 KiB
    static constexpr Common::Address k_periAhb3BaseAddr = STM32F407_MEM_ADDR_PERI_AHB3_START;
    static constexpr Common::Address k_periAhb3EndAddr = k_periAhb3BaseAddr + k_periAhb3Size - 1;
} // namespace Stm32f407::Mem
