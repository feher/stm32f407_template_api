#pragma once

#include "Src/bitapi/stm32f407_apb1.hpp"
#include "stm32f407_mem.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Bitapi::Apb1::detail
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct I2cX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
    };
} // namespace Stm32f407::Bitapi::Apb1::detail

namespace Stm32f407::Bitapi::Apb1
{
    // I2C controller 1.
    using I2c1 = detail::I2cX<k_addr + 0x5400U, k_addr + 0x57ffU>;

    // I2C controller 2.
    using I2c2 = detail::I2cX<k_addr + 0x5800U, k_addr + 0x5bffU>;

    // I2C controller 3.
    using I2c3 = detail::I2cX<k_addr + 0x5c00U, k_addr + 0x5fffU>;
} // namespace Stm32f407::Bitapi::Apb1
