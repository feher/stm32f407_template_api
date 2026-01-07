#pragma once

#include "stm32f407_apb2.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb2::detail
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct UsartX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
    };
} // namespace Stm32f407::Apb2::detail

namespace Stm32f407::Apb2
{
    // USART controller 1.
    using Usart1 = detail::UsartX<k_addr + 0x1000U, k_addr + 0x13ffU>;

    // USART controller 6.
    using Usart6 = detail::UsartX<k_addr + 0x1400U, k_addr + 0x17ffU>;
} // namespace Stm32f407::Apb2
