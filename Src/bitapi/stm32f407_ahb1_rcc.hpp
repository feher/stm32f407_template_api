#pragma once

#include "stm32f407_utils.hpp"

// Reset and Clock Control.
namespace Stm32f407::Ahb1::Rcc
{
    static constexpr Address k_baseAddr = 0x4002'3800U;

    // Control register.
    namespace Cr
    {
        static constexpr Word k_offset = 0x00;
        static constexpr Address k_addr = k_baseAddr + k_offset;
        using HseOn = Bits<k_addr, 16, 1, Word>;
        using HseRdy = Bits<k_addr, 16, 1, Word>;
    } // namespace Cr

    // Configuration register.
    namespace Cfgr
    {
        static constexpr Word k_offset = 0x08;
        static constexpr Address k_addr = k_baseAddr + k_offset;

        // Generic MCO prescaler (divider) value.
        enum class McoXPreValue : Word
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
        enum class Mco1Value : Word
        {
            Hsi = 0b00,
            Lse = 0b01,
            Hse = 0b10,
            Pll = 0b11
        };

        // Microcontroller Clock Output 1.
        using Mco1 = Bits<k_addr, 21, 2, Mco1Value>;

        // Prescaler (divider) for Microcontroller Clock Output 1.
        using Mco1Pre = Bits<k_addr, 24, 3, Mco1PreValue>;

        // Source value for the Microcontroller Clock Output 2.
        enum class Mco2Value : Word
        {
            SysClk = 0b00,
            PllI2s = 0b01,
            Hse = 0b10,
            Pll = 0b11
        };

        // Microcontroller Clock Output 2.
        using Mco2 = Bits<k_addr, 30, 2, Mco2Value>;

        // Prescaler (divider) for Microcontroller Clock Output 2.
        using Mco2Pre = Bits<k_addr, 27, 3, Mco2PreValue>;
    } // namespace Cfgr

    // Reset register for Advanced High speed Bus #1.
    namespace Ahb1Rstr
    {
        static constexpr Word k_offset = 0x10;
        static constexpr Address k_addr = k_baseAddr + k_offset;

        // Bit to reset GPIO port A.
        using GpioARst = Bits<k_addr, 0, 1, ResetBit>;

        // Bit to reset GPIO port B.
        using GpioBRst = Bits<k_addr, 1, 1, ResetBit>;

        // Bit to reset GPIO port C.
        using GpioCRst = Bits<k_addr, 2, 1, ResetBit>;

        // Bit to reset GPIO port D.
        using GpioDRst = Bits<k_addr, 3, 1, ResetBit>;

        // Bit to reset GPIO port E.
        using GpioERst = Bits<k_addr, 4, 1, ResetBit>;

        // Bit to reset GPIO port F.
        using GpioFRst = Bits<k_addr, 5, 1, ResetBit>;

        // Bit to reset GPIO port G.
        using GpioGRst = Bits<k_addr, 6, 1, ResetBit>;

        // Bit to reset GPIO port H.
        using GpioHRst = Bits<k_addr, 7, 1, ResetBit>;

        // Bit to reset GPIO port I.
        using GpioIRst = Bits<k_addr, 8, 1, ResetBit>;

        // Bit to reset GPIO port J.
        using GpioJRst = Bits<k_addr, 9, 1, ResetBit>;

        // Bit to reset GPIO port K.
        using GpioKRst = Bits<k_addr, 10, 1, ResetBit>;
    }; // namespace Ahb1Rstr

    // Peripheral-enable register for Advanced High speed Bus #1.
    namespace Ahb1Enr
    {
        static constexpr Word k_offset = 0x30;
        static constexpr Address k_addr = k_baseAddr + k_offset;

        // Bit to enable GPIO port A.
        using GpioAEn = Bits<k_addr, 0, 1, EnDi>;

        // Bit to enable GPIO port B.
        using GpioBEn = Bits<k_addr, 1, 1, EnDi>;

        // Bit to enable GPIO port C.
        using GpioCEn = Bits<k_addr, 2, 1, EnDi>;

        // Bit to enable GPIO port D.
        using GpioDEn = Bits<k_addr, 3, 1, EnDi>;

        // Bit to enable GPIO port E.
        using GpioEEn = Bits<k_addr, 4, 1, EnDi>;

        // Bit to enable GPIO port F.
        using GpioFEn = Bits<k_addr, 5, 1, EnDi>;

        // Bit to enable GPIO port G.
        using GpioGEn = Bits<k_addr, 6, 1, EnDi>;

        // Bit to enable GPIO port H.
        using GpioHEn = Bits<k_addr, 7, 1, EnDi>;

        // Bit to enable GPIO port I.
        using GpioIEn = Bits<k_addr, 8, 1, EnDi>;

        // Bit to enable GPIO port J.
        using GpioJEn = Bits<k_addr, 9, 1, EnDi>;

        // Bit to enable GPIO port K.
        using GpioKEn = Bits<k_addr, 10, 1, EnDi>;
    } // namespace Ahb1Enr

    // Peripheral-enable register for Advanced Peripheral Bus #1.
    namespace Apb1Enr
    {
        static constexpr Word k_offset = 0x40;
        static constexpr Address k_addr = k_baseAddr + k_offset;

        // Bit to enable SPI controller #2.
        using Spi2En = Bits<k_addr, 14, 1, Word>;

        // Bit to enable SPI controller #3.
        using Spi3En = Bits<k_addr, 15, 1, Word>;

        // Bit to enable USART controller #2.
        using Usart2En = Bits<k_addr, 17, 1, Word>;

        // Bit to enable USART controller #3.
        using Usart3En = Bits<k_addr, 18, 1, Word>;

        // Bit to enable UART controller #4.
        using Uart4En = Bits<k_addr, 19, 1, Word>;

        // Bit to enable UART controller #5.
        using Uart5En = Bits<k_addr, 20, 1, Word>;

        // Bit to enable I2C controller #1.
        using I2c1En = Bits<k_addr, 21, 1, Word>;

        // Bit to enable I2C controller #2.
        using I2c2En = Bits<k_addr, 22, 1, Word>;

        // Bit to enable I2C controller #3.
        using I2c3En = Bits<k_addr, 23, 1, Word>;
    } // namespace Apb1Enr

    // Peripheral-enable register for Advanced Peripheral Bus #2.
    namespace Apb2Enr
    {
        static constexpr Word k_offset = 0x44;
        static constexpr Address k_addr = k_baseAddr + k_offset;

        // Bit to enable USART controller #1.
        using Usart1En = Bits<k_addr, 4, 1, Word>;

        // Bit to enable USART controller #6.
        using Usart6En = Bits<k_addr, 5, 1, Word>;

        // Bit to enable SPI controller #1.
        using Spi1En = Bits<k_addr, 12, 1, Word>;

        // Bit to enable System Configuration peripheral.
        using SysCfgEn = Bits<k_addr, 14, 1, Word>;
    } // namespace Apb2Enr
} // namespace Stm32f407::Ahb1::Rcc
