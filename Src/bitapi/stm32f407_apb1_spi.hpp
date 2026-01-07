#pragma once

#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb1
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct SpiX
    {
        static constexpr Common::Address k_baseAddr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_baseAddr + 1;
    };

    // SPI controller 2.
    using Spi2 = SpiX<0x4000'3800U, 0x4000'3bffU>;

    // SPI controller 3.
    using Spi3 = SpiX<0x4000'3c00U, 0x4000'3fffU>;
} // namespace Stm32f407::Apb1
