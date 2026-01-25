#pragma once

#include "stm32f407_apb2.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Bitapi::Apb2::details
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct SpiX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;
    };
} // namespace Stm32f407::Bitapi::Apb2::details

namespace Stm32f407::Bitapi::Apb2
{
    // SPI controller 1.
    using Spi1 = details::SpiX<k_addr + 0x3000U, k_addr + 0x33ffU>;
} // namespace Stm32f407::Bitapi::Apb2
