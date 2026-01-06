#pragma once

#include "stm32f407_utils.hpp"

namespace Apb1
{
    template <Address TVBaseAddr, Address TVEndAddr> struct UsartX
    {
        static constexpr Address k_baseAddr = TVBaseAddr;
        static constexpr Address k_endAddr = TVEndAddr;
        static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
    };

    // USART controller 1.
    using Usart1 = UsartX<0x4001'1000U, 0x4001'13ffU>;

    // USART controller 6.
    using Usart6 = UsartX<0x4001'1400U, 0x4001'17ffU>;
} // namespace Apb1
