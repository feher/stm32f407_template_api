#pragma once

#include "stm32f407_mem.hpp"
#include "stm32f407_utils.hpp"

#include <cassert>
#include <type_traits>
#include <utility>

// Advanced High performance Bus 2.
namespace Stm32f407::Bitapi::Core::Nvic
{
    static constexpr Common::Address k_addr = Mem::k_corePeripheralsBaseAddr + 0xe100U;
    static constexpr Common::Address k_endAddr = Mem::k_corePeripheralsBaseAddr + 0xe4efU;
    static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;

    static constexpr int k_irqCount = 82;

    enum class IrqNumber : unsigned int
    {
        Wwdg = 0,
        Pvd = 1,
        TampStamp = 2,
        RtcWakeup = 3,
        Flash = 4,
        Rcc = 5,
        Exti0 = 6,
        Exti1 = 7,
        Exti2 = 8,
        Exti3 = 9,
        Exti4 = 10,
        Dma1Stream0 = 11,
        Dma1Stream1 = 12,
        Dma1Stream2 = 13,
        Dma1Stream3 = 14,
        Dma1Stream4 = 15,
        Dma1Stream5 = 16,
        Dma1Stream6 = 17,
        Adc = 18,
        Exti9_5 = 23,
        Tim2 = 28,
        Tim3 = 29,
        Tim4 = 30,
        Spi1 = 35,
        Spi2 = 36,
        Usart1 = 37,
        Usart2 = 38,
        Usart3 = 39,
        Exti15_10 = 40,
        Tim5 = 50,
        Uart4 = 52,
        Uart5 = 53
    };

    enum class IserReadValue : Common::Word
    {
        Disabled = 0,
        Enabled = 1
    };

    enum class IserWriteValue : Common::Word
    {
        NoEffect = 0,
        Enable = 1
    };

    // Interrupt Set-Enable Registers.
    using Iser = Util::BitsRegister<k_addr, 0x100 - 0x100, IrqNumber, 1, IserReadValue, IserWriteValue>;

    enum class IcerReadValue : Common::Word
    {
        Disabled = 0,
        Enabled = 1
    };

    enum class IcerWriteValue : Common::Word
    {
        NoEffect = 0,
        Disable = 1
    };

    // Interrupt Clear-Enable Registers.
    using Icer = Util::BitsRegister<k_addr, 0x180 - 0x100, IrqNumber, 1, IcerReadValue, IcerWriteValue>;

    enum class IsprReadValue : Common::Word
    {
        NotPending = 0,
        Pending = 1
    };

    enum class IsprWriteValue : Common::Word
    {
        NoEffect = 0,
        SetPending = 1
    };

    // Interrupt Set-Pending Registers.
    using Ispr = Util::BitsRegister<k_addr, 0x200 - 0x100, IrqNumber, 1, IsprReadValue, IsprWriteValue>;

    enum class IcprReadValue : Common::Word
    {
        NotPending = 0,
        Pending = 1
    };

    enum class IcprWriteValue : Common::Word
    {
        NoEffect = 0,
        ClearPending = 1
    };

    // Interrupt Clear-Pending Registers.
    using Icpr = Util::BitsRegister<k_addr, 0x280 - 0x100, IrqNumber, 1, IcprReadValue, IcprWriteValue>;

    enum class IabrReadValue : Common::Word
    {
        NotActive = 0,
        Active = 1
    };

    // Interrupt Active-Bit Registers.
    using Iabr = Util::BitsRegister<k_addr, 0x300 - 0x100, IrqNumber, 1, IabrReadValue, void>;

    enum class IprValue : Common::Word
    {
        Priority0 = 0b0000 << 4,
        Priority1 = 0b0001 << 4,
        Priority2 = 0b0010 << 4,
        Priority3 = 0b0011 << 4,
        Priority4 = 0b0100 << 4,
        Priority5 = 0b0101 << 4,
        Priority6 = 0b0110 << 4,
        Priority7 = 0b0111 << 4,
        Priority8 = 0b1000 << 4,
        Priority9 = 0b1001 << 4,
        Priority10 = 0b1010 << 4,
        Priority11 = 0b1011 << 4,
        Priority12 = 0b1100 << 4,
        Priority13 = 0b1101 << 4,
        Priority14 = 0b1110 << 4,
        Priority15 = 0b1111 << 4
    };

    // Interrupt Priority Registers.
    using Ipr = Util::BitsRegister<k_addr, 0x400 - 0x100, IrqNumber, 8, IprValue>;

} // namespace Stm32f407::Bitapi::Core::Nvic

namespace Stm32f407::Bitapi::Util
{
    template <>
    inline Core::Nvic::IrqNumber maxEnumValue<Core::Nvic::IrqNumber>()
    {
        return Core::Nvic::IrqNumber::Uart5;
    }
} // namespace Stm32f407::Bitapi::Util
