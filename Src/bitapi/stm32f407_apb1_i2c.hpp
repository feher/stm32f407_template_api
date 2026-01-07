#pragma once

#include "stm32f407_utils.hpp"

namespace Stm32f407::Apb1::detail
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct I2cX
    {
        static constexpr Common::Address k_baseAddr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_baseAddr + 1;
    };
} // namespace Stm32f407::Apb1::detail

namespace Stm32f407::Apb1
{
    // I2C controller 1.
    using I2c1 = detail::I2cX<0x4000'5400U, 0x4000'57ffU>;

    // I2C controller 2.
    using I2c2 = detail::I2cX<0x4000'5800U, 0x4000'5bffU>;

    // I2C controller 3.
    using I2c3 = detail::I2cX<0x4000'5c00U, 0x4000'5fffU>;
} // namespace Stm32f407::Apb1
