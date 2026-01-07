#pragma once

#include "stm32f407_apb1.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb1::details
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct SpiX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
    };
} // namespace Stm32f407::Apb1::details

namespace Stm32f407::Apb1
{
    // SPI controller 2.
    using Spi2 = details::SpiX<k_addr + 0x3800U, k_addr + 0x3bffU>;

    // SPI controller 3.
    using Spi3 = details::SpiX<k_addr + 0x3c00U, k_addr + 0x3fffU>;
} // namespace Stm32f407::Apb1
