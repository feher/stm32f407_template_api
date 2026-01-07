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
    // USART controller 1.
    using Usart1 = detail::UsartX<0x4001'1000U, 0x4001'13ffU>;

    // USART controller 6.
    using Usart6 = detail::UsartX<0x4001'1400U, 0x4001'17ffU>;
} // namespace Stm32f407::Apb1
