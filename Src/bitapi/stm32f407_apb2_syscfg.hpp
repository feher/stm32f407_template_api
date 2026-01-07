#pragma once

#include "stm32f407_apb2.hpp"
#include "stm32f407_utils.hpp"

// System Configuration Controller.
namespace Stm32f407::Apb2::Syscfg
{
    static constexpr Common::Address k_addr = Apb2::k_addr + 0x3800U;
    static constexpr Common::Address k_endAddr = 0x4001'3bffU;
    static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;

    // Specifies a GPIO port as the interrupt source for a given EXTI line.
    enum class ExtiGpioAI
    {
        GpioA = 0b0000,
        GpioB = 0b0001,
        GpioC = 0b0010,
        GpioD = 0b0011,
        GpioE = 0b0100,
        GpioF = 0b0101,
        GpioG = 0b0110,
        GpioH = 0b0111,
        GpioI = 0b1000
    };

    // Specifies a GPIO port as the interrupt source for a given EXTI line.
    enum class ExtiGpioAH
    {
        GpioA = 0b0000,
        GpioB = 0b0001,
        GpioC = 0b0010,
        GpioD = 0b0011,
        GpioE = 0b0100,
        GpioF = 0b0101,
        GpioG = 0b0110,
        GpioH = 0b0111
    };
} // namespace Stm32f407::Apb2::Syscfg

// SYSCFG External Interrupt Configuration Register 1.
//
// These bits are written by software to select the source input for the EXTIx
// external interrupt.
namespace Stm32f407::Apb2::Syscfg::Exticr1
{
    static constexpr Common::Word k_offset = 0x08;
    static constexpr Common::Address k_addr = Syscfg::k_addr + k_offset;

    using Exit0 = Util::Bits<k_addr, 0, 4, ExtiGpioAI>;
    using Exit1 = Util::Bits<k_addr, 4, 4, ExtiGpioAI>;
    using Exit2 = Util::Bits<k_addr, 8, 4, ExtiGpioAI>;
    using Exit3 = Util::Bits<k_addr, 12, 4, ExtiGpioAI>;
} // namespace Stm32f407::Apb2::Syscfg::Exticr1

// SYSCFG External Interrupt Configuration Register 2.
//
// These bits are written by software to select the source input for the EXTIx
// external interrupt.
namespace Stm32f407::Apb2::Syscfg::Exticr2
{
    static constexpr Common::Word k_offset = 0x0c;
    static constexpr Common::Address k_addr = Syscfg::k_addr + k_offset;

    using Exit4 = Util::Bits<k_addr, 0, 4, ExtiGpioAI>;
    using Exit5 = Util::Bits<k_addr, 4, 4, ExtiGpioAI>;
    using Exit6 = Util::Bits<k_addr, 8, 4, ExtiGpioAI>;
    using Exit7 = Util::Bits<k_addr, 12, 4, ExtiGpioAI>;
} // namespace Stm32f407::Apb2::Syscfg::Exticr2

// SYSCFG External Interrupt Configuration Register 3.
//
// These bits are written by software to select the source input for the EXTIx
// external interrupt.
namespace Stm32f407::Apb2::Syscfg::Exticr3
{
    static constexpr Common::Word k_offset = 0x10;
    static constexpr Common::Address k_addr = Syscfg::k_addr + k_offset;

    using Exit8 = Util::Bits<k_addr, 0, 4, ExtiGpioAI>;
    using Exit9 = Util::Bits<k_addr, 4, 4, ExtiGpioAI>;
    using Exit10 = Util::Bits<k_addr, 8, 4, ExtiGpioAI>;
    using Exit11 = Util::Bits<k_addr, 12, 4, ExtiGpioAI>;
} // namespace Stm32f407::Apb2::Syscfg::Exticr3

// SYSCFG External Interrupt Configuration Register 4.
//
// These bits are written by software to select the source input for the EXTIx
// external interrupt.
//
// GPIO port I is not used.
namespace Stm32f407::Apb2::Syscfg::Exticr4
{
    static constexpr Common::Word k_offset = 0x14;
    static constexpr Common::Address k_addr = Syscfg::k_addr + k_offset;

    using Exit12 = Util::Bits<k_addr, 0, 4, ExtiGpioAH>;
    using Exit13 = Util::Bits<k_addr, 4, 4, ExtiGpioAH>;
    using Exit14 = Util::Bits<k_addr, 8, 4, ExtiGpioAH>;
    using Exit15 = Util::Bits<k_addr, 12, 4, ExtiGpioAH>;
} // namespace Stm32f407::Apb2::Syscfg::Exticr4
