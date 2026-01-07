#pragma once

#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb1
{
    template <Address TVBaseAddr, Address TVEndAddr>
    struct I2cX
    {
        static constexpr Address k_baseAddr = TVBaseAddr;
        static constexpr Address k_endAddr = TVEndAddr;
        static constexpr Word k_memSize = k_endAddr - k_baseAddr + 1;
    };

    // I2C controller 1.
    using I2c1 = I2cX<0x4000'5400U, 0x4000'57ffU>;

    // I2C controller 2.
    using I2c2 = I2cX<0x4000'5800U, 0x4000'5bffU>;

    // I2C controller 3.
    using I2c3 = I2cX<0x4000'5c00U, 0x4000'5fffU>;
} // namespace Stm32f407::Apb1
