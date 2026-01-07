#pragma once

#include "stm32f407_ahb1.hpp"
#include "stm32f407_utils.hpp"

// Reset and Clock Control.
namespace Stm32f407::Ahb1::Rcc
{
    static constexpr Common::Address k_addr = Ahb1::k_addr + 0x3800U;

    // Control register.
    namespace Cr
    {
        static constexpr Common::Word k_offset = 0x00;
        static constexpr Common::Address k_addr = Rcc::k_addr + k_offset;
        using HseOn = Util::Bits<k_addr, 16, 1, Common::Word>;
        using HseRdy = Util::Bits<k_addr, 16, 1, Common::Word>;
    } // namespace Cr

    // Configuration register.
    namespace Cfgr
    {
        static constexpr Common::Word k_offset = 0x08;
        static constexpr Common::Address k_addr = Rcc::k_addr + k_offset;

        // Generic MCO prescaler (divider) value.
        enum class McoXPreValue : Common::Word
        {
            One = 0b000,
            Two = 0b100,
            Three = 0b101,
            Four = 0b110,
            Five = 0b111,
        };

        // MCO1 prescaler (divider) value.
        using Mco1PreValue = McoXPreValue;

        // MCO2 prescaler (divider) value.
        using Mco2PreValue = McoXPreValue;

        // Source value for the Microcontroller Clock Output 1.
        enum class Mco1Value : Common::Word
        {
            Hsi = 0b00,
            Lse = 0b01,
            Hse = 0b10,
            Pll = 0b11
        };

        // Microcontroller Clock Output 1.
        using Mco1 = Util::Bits<k_addr, 21, 2, Mco1Value>;

        // Prescaler (divider) for Microcontroller Clock Output 1.
        using Mco1Pre = Util::Bits<k_addr, 24, 3, Mco1PreValue>;

        // Source value for the Microcontroller Clock Output 2.
        enum class Mco2Value : Common::Word
        {
            SysClk = 0b00,
            PllI2s = 0b01,
            Hse = 0b10,
            Pll = 0b11
        };

        // Microcontroller Clock Output 2.
        using Mco2 = Util::Bits<k_addr, 30, 2, Mco2Value>;

        // Prescaler (divider) for Microcontroller Clock Output 2.
        using Mco2Pre = Util::Bits<k_addr, 27, 3, Mco2PreValue>;
    } // namespace Cfgr

    // Reset register for Advanced High speed Bus #1.
    namespace Ahb1Rstr
    {
        static constexpr Common::Word k_offset = 0x10;
        static constexpr Common::Address k_addr = Rcc::k_addr + k_offset;

        // Bit to reset GPIO port A.
        using GpioARst = Util::Bits<k_addr, 0, 1, Common::ResetBit>;

        // Bit to reset GPIO port B.
        using GpioBRst = Util::Bits<k_addr, 1, 1, Common::ResetBit>;

        // Bit to reset GPIO port C.
        using GpioCRst = Util::Bits<k_addr, 2, 1, Common::ResetBit>;

        // Bit to reset GPIO port D.
        using GpioDRst = Util::Bits<k_addr, 3, 1, Common::ResetBit>;

        // Bit to reset GPIO port E.
        using GpioERst = Util::Bits<k_addr, 4, 1, Common::ResetBit>;

        // Bit to reset GPIO port F.
        using GpioFRst = Util::Bits<k_addr, 5, 1, Common::ResetBit>;

        // Bit to reset GPIO port G.
        using GpioGRst = Util::Bits<k_addr, 6, 1, Common::ResetBit>;

        // Bit to reset GPIO port H.
        using GpioHRst = Util::Bits<k_addr, 7, 1, Common::ResetBit>;

        // Bit to reset GPIO port I.
        using GpioIRst = Util::Bits<k_addr, 8, 1, Common::ResetBit>;

        // Bit to reset GPIO port J.
        using GpioJRst = Util::Bits<k_addr, 9, 1, Common::ResetBit>;

        // Bit to reset GPIO port K.
        using GpioKRst = Util::Bits<k_addr, 10, 1, Common::ResetBit>;
    }; // namespace Ahb1Rstr

    // Peripheral-enable register for Advanced High speed Bus #1.
    namespace Ahb1Enr
    {
        static constexpr Common::Word k_offset = 0x30;
        static constexpr Common::Address k_addr = Rcc::k_addr + k_offset;

        // Bit to enable GPIO port A.
        using GpioAEn = Util::Bits<k_addr, 0, 1, Common::EnDi>;

        // Bit to enable GPIO port B.
        using GpioBEn = Util::Bits<k_addr, 1, 1, Common::EnDi>;

        // Bit to enable GPIO port C.
        using GpioCEn = Util::Bits<k_addr, 2, 1, Common::EnDi>;

        // Bit to enable GPIO port D.
        using GpioDEn = Util::Bits<k_addr, 3, 1, Common::EnDi>;

        // Bit to enable GPIO port E.
        using GpioEEn = Util::Bits<k_addr, 4, 1, Common::EnDi>;

        // Bit to enable GPIO port F.
        using GpioFEn = Util::Bits<k_addr, 5, 1, Common::EnDi>;

        // Bit to enable GPIO port G.
        using GpioGEn = Util::Bits<k_addr, 6, 1, Common::EnDi>;

        // Bit to enable GPIO port H.
        using GpioHEn = Util::Bits<k_addr, 7, 1, Common::EnDi>;

        // Bit to enable GPIO port I.
        using GpioIEn = Util::Bits<k_addr, 8, 1, Common::EnDi>;

        // Bit to enable GPIO port J.
        using GpioJEn = Util::Bits<k_addr, 9, 1, Common::EnDi>;

        // Bit to enable GPIO port K.
        using GpioKEn = Util::Bits<k_addr, 10, 1, Common::EnDi>;
    } // namespace Ahb1Enr

    // Peripheral-enable register for Advanced Peripheral Bus #1.
    namespace Apb1Enr
    {
        static constexpr Common::Word k_offset = 0x40;
        static constexpr Common::Address k_addr = Rcc::k_addr + k_offset;

        // Bit to enable SPI controller #2.
        using Spi2En = Util::Bits<k_addr, 14, 1, Common::Word>;

        // Bit to enable SPI controller #3.
        using Spi3En = Util::Bits<k_addr, 15, 1, Common::Word>;

        // Bit to enable USART controller #2.
        using Usart2En = Util::Bits<k_addr, 17, 1, Common::Word>;

        // Bit to enable USART controller #3.
        using Usart3En = Util::Bits<k_addr, 18, 1, Common::Word>;

        // Bit to enable UART controller #4.
        using Uart4En = Util::Bits<k_addr, 19, 1, Common::Word>;

        // Bit to enable UART controller #5.
        using Uart5En = Util::Bits<k_addr, 20, 1, Common::Word>;

        // Bit to enable I2C controller #1.
        using I2c1En = Util::Bits<k_addr, 21, 1, Common::Word>;

        // Bit to enable I2C controller #2.
        using I2c2En = Util::Bits<k_addr, 22, 1, Common::Word>;

        // Bit to enable I2C controller #3.
        using I2c3En = Util::Bits<k_addr, 23, 1, Common::Word>;
    } // namespace Apb1Enr

    // Peripheral-enable register for Advanced Peripheral Bus #2.
    namespace Apb2Enr
    {
        static constexpr Common::Word k_offset = 0x44;
        static constexpr Common::Address k_addr = Rcc::k_addr + k_offset;

        // Bit to enable USART controller #1.
        using Usart1En = Util::Bits<k_addr, 4, 1, Common::Word>;

        // Bit to enable USART controller #6.
        using Usart6En = Util::Bits<k_addr, 5, 1, Common::Word>;

        // Bit to enable SPI controller #1.
        using Spi1En = Util::Bits<k_addr, 12, 1, Common::Word>;

        // Bit to enable System Configuration peripheral.
        using SysCfgEn = Util::Bits<k_addr, 14, 1, Common::Word>;
    } // namespace Apb2Enr
} // namespace Stm32f407::Ahb1::Rcc
