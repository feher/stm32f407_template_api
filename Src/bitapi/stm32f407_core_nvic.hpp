#pragma once

#include "stm32f407_utils.hpp"

#include <cassert>
#include <type_traits>
#include <utility>

// Advanced High performance Bus 2.
namespace Stm32f407::Core::Nvic
{
    static constexpr Address k_baseAddr = 0xe000'e000U;
    static constexpr Address k_endAddr = 0xe000'ef00U;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;

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
        Spi1 = 35,
        Spi2 = 36,
        Usart1 = 37,
        Usart2 = 38,
        Usart3 = 39,
        Exti15_10 = 40,
        Uart4 = 52,
        Uart5 = 53
    };

} // namespace Stm32f407::Core::Nvic

namespace Core::Nvic
{
    enum class IserReadValue : Word
    {
        Disabled = 0,
        Enabled = 1
    };

    enum class IserWriteValue : Word
    {
        NoEffect = 0,
        Enable = 1
    };

    // Interrupt Set-Enable Registers.
    using Iser = BitsRegister<k_baseAddr, 0x100, IrqNumber, 1, IserReadValue, IserWriteValue>;

    enum class IcerReadValue : Word
    {
        Disabled = 0,
        Enabled = 1
    };

    enum class IcerWriteValue : Word
    {
        NoEffect = 0,
        Disable = 1
    };

    // Interrupt Clear-Enable Registers.
    using Icer = BitsRegister<k_baseAddr, 0x180, IrqNumber, 1, IcerReadValue, IcerWriteValue>;

    enum class IsprReadValue : Word
    {
        NotPending = 0,
        Pending = 1
    };

    enum class IsprWriteValue : Word
    {
        NoEffect = 0,
        SetPending = 1
    };

    // Interrupt Set-Pending Registers.
    using Ispr = BitsRegister<k_baseAddr, 0x200, IrqNumber, 1, IsprReadValue, IsprWriteValue>;

    enum class IcprReadValue : Word
    {
        NotPending = 0,
        Pending = 1
    };

    enum class IcprWriteValue : Word
    {
        NoEffect = 0,
        ClearPending = 1
    };

    // Interrupt Clear-Pending Registers.
    using Icpr = BitsRegister<k_baseAddr, 0x280, IrqNumber, 1, IcprReadValue, IcprWriteValue>;

    enum class IabrReadValue : Word
    {
        NotActive = 0,
        Active = 1
    };

    // Interrupt Active-Bit Registers.
    using Iabr = BitsRegister<k_baseAddr, 0x300, IrqNumber, 1, IabrReadValue, void>;

} // namespace Core::Nvic

template <>
inline Core::Nvic::IrqNumber maxEnumValue<Core::Nvic::IrqNumber>()
{
    return Core::Nvic::IrqNumber::Uart5;
}
