#pragma once

#include "stm32f407_utils.hpp"

template <Address TVBaseAddr, Address TVEndAddr> struct UsartX
{
    static constexpr Address k_baseAddr = TVBaseAddr;
    static constexpr Address k_endAddr = TVEndAddr;
    static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
};

namespace Apb1
{
    // USART controller 2.
    using Usart2 = UsartX<0x4000'4400U, 0x4000'47ffU>;

    // USART controller 3.
    using Usart3 = UsartX<0x4000'4800U, 0x4000'4bffU>;

    // UART controller 4.
    using Uart4 = UsartX<0x4000'4c00U, 0x4000'4fffU>;

    // UART controller 5.
    using Uart5 = UsartX<0x4000'5000U, 0x4000'53ffU>;
} // namespace Apb1
