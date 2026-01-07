#pragma once

#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb1::detail
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct UsartX
    {
        static constexpr Common::Address k_baseAddr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_baseAddr + 1;
    };
} // namespace Stm32f407::Apb1::detail

namespace Stm32f407::Apb1
{
    // USART controller 2.
    using Usart2 = detail::UsartX<0x4000'4400U, 0x4000'47ffU>;

    // USART controller 3.
    using Usart3 = detail::UsartX<0x4000'4800U, 0x4000'4bffU>;

    // UART controller 4.
    using Uart4 = detail::UsartX<0x4000'4c00U, 0x4000'4fffU>;

    // UART controller 5.
    using Uart5 = detail::UsartX<0x4000'5000U, 0x4000'53ffU>;
} // namespace Stm32f407::Apb1
