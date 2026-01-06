#pragma once

#include "stm32f407_utils.hpp"

namespace Apb2
{
    template <Address TVBaseAddr, Address TVEndAddr> struct SpiX
    {
        static constexpr Address k_baseAddr = TVBaseAddr;
        static constexpr Address k_endAddr = TVEndAddr;
        static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
    };

    // SPI controller 1.
    using Spi2 = SpiX<0x4001'3000U, 0x4001'33ffU>;
} // namespace Apb2
