#pragma once

#include "stm32f407_utils.hpp"

namespace Apb1
{
    template <Address TVBaseAddr, Address TVEndAddr> struct SpiX
    {
        static constexpr Address k_baseAddr = TVBaseAddr;
        static constexpr Address k_endAddr = TVEndAddr;
        static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
    };

    // SPI controller 2.
    using Spi2 = SpiX<0x4000'3800U, 0x4000'3bffU>;

    // SPI controller 3.
    using Spi3 = SpiX<0x4000'3c00U, 0x4000'3fffU>;
} // namespace Apb1
