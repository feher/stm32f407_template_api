#pragma once

#include "stm32f407_apb1.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb1::detail
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct UsartX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
    };
} // namespace Stm32f407::Apb1::detail

namespace Stm32f407::Apb1
{
    // USART controller 2.
    using Usart2 = detail::UsartX<k_addr + 0x4400U, k_addr + 0x47ffU>;

    // USART controller 3.
    using Usart3 = detail::UsartX<k_addr + 0x4800U, k_addr + 0x4bffU>;

    // UART controller 4.
    using Uart4 = detail::UsartX<k_addr + 0x4c00U, k_addr + 0x4fffU>;

    // UART controller 5.
    using Uart5 = detail::UsartX<k_addr + 0x5000U, k_addr + 0x53ffU>;
} // namespace Stm32f407::Apb1
