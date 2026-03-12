#pragma once

#include "stm32f407_ahb1.hpp"
#include "stm32f407_utils.hpp"

#include <cassert>

namespace Stm32f407::Bitapi::Ahb1::Gpio
{
    static constexpr int k_pinCount = 16;

    // GPIO port name.
    enum class GpioPort : unsigned int
    {
        PortA = 0,
        PortB = 1,
        PortC = 2,
        PortD = 3,
        PortE = 4,
        PortF = 5,
        PortG = 6,
        PortH = 7,
        PortI = 8,
        PortJ = 9,
        PortK = 10,
    };

    // GPIO pin number.
    enum class GpioPin : unsigned int
    {
        Pin0 = 0,
        Pin1 = 1,
        Pin2 = 2,
        Pin3 = 3,
        Pin4 = 4,
        Pin5 = 5,
        Pin6 = 6,
        Pin7 = 7,
        Pin8 = 8,
        Pin9 = 9,
        Pin10 = 10,
        Pin11 = 11,
        Pin12 = 12,
        Pin13 = 13,
        Pin14 = 14,
        Pin15 = k_pinCount - 1
    };

    // GPIO pin mode values.
    enum class GpioMode : Common::Word
    {
        Input = 0b00,
        Output = 0b01,
        AltFunc = 0b10,
        Analog = 0b11
    };

    // GPIO pin output type values.
    enum class GpioOutputType : Common::Word
    {
        PushPull = 0,
        OpenDrain = 1
    };

    // GPIO pin output speed values.
    enum class GpioOutputSpeed : Common::Word
    {
        Low = 0b00,
        Medium = 0b01,
        High = 0b10,
        VeryHigh = 0b11
    };

    // GPIO pin pull up/down values.
    enum class GpioPupd : Common::Word
    {
        NoPull = 0b00,
        PullUp = 0b01,
        PullDown = 0b10
    };

    // Generic alternate function values for GPIO port X pin Y.
    enum class GpioAltFunc : Common::Word
    {
        Af0 = 0b0000,
        Af1 = 0b0001,
        Af2 = 0b0010,
        Af3 = 0b0011,
        Af4 = 0b0100,
        Af5 = 0b0101,
        Af6 = 0b0110,
        Af7 = 0b0111,
        Af8 = 0b1000,
        Af9 = 0b1001,
        Af10 = 0b1010,
        Af11 = 0b1011,
        Af12 = 0b1100,
        Af13 = 0b1101,
        Af14 = 0b1110,
        Af15 = 0b1111
    };

    namespace detail
    {
        // Alternate function values for GPIO port A pin 0.
        enum class GpioA0AltFunc : Common::Word
        {
            Af0_Na = 0,
            Af1_Tim2_Ch1_Etr = 1,
            Af2_Tim5_Ch1 = 2,
            Af3_Tim8_Etr = 3,
            Af4_Na = 4,
            Af5_Na = 5,
            Af6_Na = 6,
            Af7_Usart2_Cts = 7,
            Af8_Usart4_Tx = 8,
            Af9_Na = 9,
            Af10_Na = 10,
            Af11_Eth_Mii_Crs = 11,
            Af12_Na = 12,
            Af13_Na = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port A pin 8.
        enum class GpioA8AltFunc : Common::Word
        {
            Af0_Mco1 = 0,
            Af1_Tim1_Ch1 = 1,
            Af2_Na = 2,
            Af3_Na = 3,
            Af4_I2c3_Scl = 4,
            Af5_Na = 5,
            Af6_Na = 6,
            Af7_Usart1_Ck = 7,
            Af8_Na = 8,
            Af9_Na = 9,
            Af10_Otg_Fs_Sof = 10,
            Af11_Na = 11,
            Af12_Na = 12,
            Af13_Na = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port B pin 12.
        enum class GpioB12AltFunc : Common::Word
        {
            Af0_Na = 0,
            Af1_Tim1_Bkin = 1,
            Af2_Na = 2,
            Af3_Na = 3,
            Af4_I2c2_Smba = 4,
            Af5_Spi2_Nss_I2s2_Ws = 5,
            Af6_Na = 6,
            Af7_Usart3_Ck = 7,
            Af8_Na = 8,
            Af9_Can2_Rx = 9,
            Af10_Otg_Hs_Ulpi_D5 = 10,
            Af11_Eth_Mii_Txd0_Eth_Rmii_Txd0 = 11,
            Af12_Otg_Hs_Id = 12,
            Af13_Na = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port B pin 13.
        enum class GpioB13AltFunc : Common::Word
        {
            Af0_Na = 0,
            Af1_Tim2_Ch1n = 1,
            Af2_Na = 2,
            Af3_Na = 3,
            Af4_Na = 4,
            Af5_Spi2_Sck_I2s2_Ck = 5,
            Af6_Na = 6,
            Af7_Usart3_Cts = 7,
            Af8_Na = 8,
            Af9_Can2_Tx = 9,
            Af10_Otg_Hs_Ulpi_D6 = 10,
            Af11_Eth_Mii_Txd1_Eth_Rmii_Txd1 = 11,
            Af12_Na = 12,
            Af13_Na = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port B pin 14.
        enum class GpioB14AltFunc : Common::Word
        {
            Af0_Na = 0,
            Af1_Tim1_Ch2n = 1,
            Af2_Na = 2,
            Af3_Tim8_Ch2n = 3,
            Af4_Na = 4,
            Af5_Spi2_Miso = 5,
            Af6_I2s2ext_Sd = 6,
            Af7_Usart3_Rts = 7,
            Af8_Na = 8,
            Af9_Tim12_Ch1 = 9,
            Af10_Na = 10,
            Af11_Na = 11,
            Af12_Otg_Hs_Dm = 12,
            Af13_Na = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port B pin 15.
        enum class GpioB15AltFunc : Common::Word
        {
            Af0_Rtc_RefIn = 0,
            Af1_Tim1_Ch3n = 1,
            Af2_Na = 2,
            Af3_Tim8_Ch3n = 3,
            Af4_Na = 4,
            Af5_Spi2_Mosi_I2s2_Sd = 5,
            Af6_Na = 6,
            Af7_Na = 7,
            Af8_Na = 8,
            Af9_Tim12_Ch2 = 9,
            Af10_Na = 10,
            Af11_Na = 11,
            Af12_Otg_Hs_Dp = 12,
            Af13_Na = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port C pin 6.
        enum class GpioC6AltFunc : Common::Word
        {
            Af0_Na = 0,
            Af1_Na = 1,
            Af2_Tim3_Ch1 = 2,
            Af3_Tim8_Ch1 = 3,
            Af4_Na = 4,
            Af5_I2s2_Mck = 5,
            Af6_Na = 6,
            Af7_Na = 7,
            Af8_Usart6_Tx = 8,
            Af9_Na = 9,
            Af10_Na = 10,
            Af11_Na = 11,
            Af12_Sdio_D6 = 12,
            Af13_Dcmi_D0 = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };

        // Alternate function values for GPIO port C pin 9.
        enum class GpioC9AltFunc : Common::Word
        {
            Af0_Mco2 = 0,
            Af1_Na = 1,
            Af2_Tim3_Ch4 = 2,
            Af3_Tim8_Ch4 = 3,
            Af4_I2c3_Sda = 4,
            Af5_I2s_Ckin = 5,
            Af6_Na = 6,
            Af7_Na = 7,
            Af8_Na = 8,
            Af9_Na = 9,
            Af10_Na = 10,
            Af11_Na = 11,
            Af12_Sdio_D1 = 12,
            Af13_Dcmi_D3 = 13,
            Af14_Na = 14,
            Af15_EventOut = 15
        };
    } // namespace detail

    template <GpioPort TVPort, GpioPin TVPin>
    struct GpioPinTraits
    {
        using AltFunc = GpioAltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortA, GpioPin::Pin0>
    {
        using AltFunc = detail::GpioA0AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortA, GpioPin::Pin8>
    {
        using AltFunc = detail::GpioA8AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortB, GpioPin::Pin12>
    {
        using AltFunc = detail::GpioB12AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortB, GpioPin::Pin13>
    {
        using AltFunc = detail::GpioB13AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortB, GpioPin::Pin14>
    {
        using AltFunc = detail::GpioB14AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortB, GpioPin::Pin15>
    {
        using AltFunc = detail::GpioB15AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortC, GpioPin::Pin6>
    {
        using AltFunc = detail::GpioC6AltFunc;
    };

    template <>
    struct GpioPinTraits<GpioPort::PortC, GpioPin::Pin9>
    {
        using AltFunc = detail::GpioC9AltFunc;
    };

    namespace detail
    {
        template <GpioPort TVPort, Common::Address baseAddr>
        struct GpioX
        {
            static constexpr GpioPort k_port = TVPort;
            static constexpr Common::Address k_baseAddr = baseAddr;

            // Mode Register.
            struct Moder
            {
                using Bits = Util::BitsRegister<k_baseAddr, 0x00, GpioPin, 2, GpioMode>;

                // Mode register bits for pin 0.
                using Moder0 = Util::Bits<Bits::k_addr, 0, 2, GpioMode>;
                // Mode register bits for pin 1.
                using Moder1 = Util::Bits<Bits::k_addr, 2, 2, GpioMode>;
                // Mode register bits for pin 2.
                using Moder2 = Util::Bits<Bits::k_addr, 4, 2, GpioMode>;
                // Mode register bits for pin 3.
                using Moder3 = Util::Bits<Bits::k_addr, 6, 2, GpioMode>;
                // Mode register bits for pin 4.
                using Moder4 = Util::Bits<Bits::k_addr, 8, 2, GpioMode>;
                // Mode register bits for pin 5.
                using Moder5 = Util::Bits<Bits::k_addr, 10, 2, GpioMode>;
                // Mode register bits for pin 6.
                using Moder6 = Util::Bits<Bits::k_addr, 12, 2, GpioMode>;
                // Mode register bits for pin 7.
                using Moder7 = Util::Bits<Bits::k_addr, 14, 2, GpioMode>;
                // Mode register bits for pin 8.
                using Moder8 = Util::Bits<Bits::k_addr, 16, 2, GpioMode>;
                // Mode register bits for pin 9.
                using Moder9 = Util::Bits<Bits::k_addr, 18, 2, GpioMode>;
                // Mode register bits for pin 10.
                using Moder10 = Util::Bits<Bits::k_addr, 20, 2, GpioMode>;
                // Mode register bits for pin 11.
                using Moder11 = Util::Bits<Bits::k_addr, 22, 2, GpioMode>;
                // Mode register bits for pin 12.
                using Moder12 = Util::Bits<Bits::k_addr, 24, 2, GpioMode>;
                // Mode register bits for pin 13.
                using Moder13 = Util::Bits<Bits::k_addr, 26, 2, GpioMode>;
                // Mode register bits for pin 14.
                using Moder14 = Util::Bits<Bits::k_addr, 28, 2, GpioMode>;
                // Mode register bits for pin 15.
                using Moder15 = Util::Bits<Bits::k_addr, 30, 2, GpioMode>;
            };

            // Output Type Register.
            struct Otyper
            {
                using Bits = Util::BitsRegister<k_baseAddr, 0x04, GpioPin, 1, GpioOutputType>;

                // Output type for pin 0.
                using Ot0 = Util::Bits<Bits::k_addr, 0, 1, GpioOutputType>;
                // Output type for pin 1.
                using Ot1 = Util::Bits<Bits::k_addr, 1, 1, GpioOutputType>;
                // Output type for pin 2.
                using Ot2 = Util::Bits<Bits::k_addr, 2, 1, GpioOutputType>;
                // Output type for pin 3.
                using Ot3 = Util::Bits<Bits::k_addr, 3, 1, GpioOutputType>;
                // Output type for pin 4.
                using Ot4 = Util::Bits<Bits::k_addr, 4, 1, GpioOutputType>;
                // Output type for pin 5.
                using Ot5 = Util::Bits<Bits::k_addr, 5, 1, GpioOutputType>;
                // Output type for pin 6.
                using Ot6 = Util::Bits<Bits::k_addr, 6, 1, GpioOutputType>;
                // Output type for pin 7.
                using Ot7 = Util::Bits<Bits::k_addr, 7, 1, GpioOutputType>;
                // Output type for pin 8.
                using Ot8 = Util::Bits<Bits::k_addr, 8, 1, GpioOutputType>;
                // Output type for pin 9.
                using Ot9 = Util::Bits<Bits::k_addr, 9, 1, GpioOutputType>;
                // Output type for pin 10.
                using Ot10 = Util::Bits<Bits::k_addr, 10, 1, GpioOutputType>;
                // Output type for pin 11.
                using Ot11 = Util::Bits<Bits::k_addr, 11, 1, GpioOutputType>;
                // Output type for pin 12.
                using Ot12 = Util::Bits<Bits::k_addr, 12, 1, GpioOutputType>;
                // Output type for pin 13.
                using Ot13 = Util::Bits<Bits::k_addr, 13, 1, GpioOutputType>;
                // Output type for pin 14.
                using Ot14 = Util::Bits<Bits::k_addr, 14, 1, GpioOutputType>;
                // Output type for pin 15.
                using Ot15 = Util::Bits<Bits::k_addr, 15, 1, GpioOutputType>;
            };

            // Output Speed Register.
            // The speed of the low-to-high (T-rise) and high-to-low (T-fall) transitions
            // (i.e. this is not the frequency of the signal).
            struct Ospeedr
            {
                using Bits = Util::BitsRegister<k_baseAddr, 0x08, GpioPin, 2, GpioOutputSpeed>;

                // Output Speed Register bits for pin 0.
                using Ospeedr0 = Util::Bits<Bits::k_addr, 0, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 1.
                using Ospeedr1 = Util::Bits<Bits::k_addr, 2, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 2.
                using Ospeedr2 = Util::Bits<Bits::k_addr, 4, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 3.
                using Ospeedr3 = Util::Bits<Bits::k_addr, 6, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 4.
                using Ospeedr4 = Util::Bits<Bits::k_addr, 8, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 5.
                using Ospeedr5 = Util::Bits<Bits::k_addr, 10, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 6.
                using Ospeedr6 = Util::Bits<Bits::k_addr, 12, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 7.
                using Ospeedr7 = Util::Bits<Bits::k_addr, 14, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 8.
                using Ospeedr8 = Util::Bits<Bits::k_addr, 16, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 9.
                using Ospeedr9 = Util::Bits<Bits::k_addr, 18, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 10.
                using Ospeedr10 = Util::Bits<Bits::k_addr, 20, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 11.
                using Ospeedr11 = Util::Bits<Bits::k_addr, 22, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 12.
                using Ospeedr12 = Util::Bits<Bits::k_addr, 24, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 13.
                using Ospeedr13 = Util::Bits<Bits::k_addr, 26, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 14.
                using Ospeedr14 = Util::Bits<Bits::k_addr, 28, 2, GpioOutputSpeed>;
                // Output Speed Register bits for pin 15.
                using Ospeedr15 = Util::Bits<Bits::k_addr, 30, 2, GpioOutputSpeed>;
            };

            // Pull Up/Down Register.
            struct Pupdr
            {
                using Bits = Util::BitsRegister<k_baseAddr, 0x0c, GpioPin, 2, GpioPupd>;

                // Pull Up/Down Register bits for pin 0.
                using Pupdr0 = Util::Bits<Bits::k_addr, 0, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 1.
                using Pupdr1 = Util::Bits<Bits::k_addr, 2, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 2.
                using Pupdr2 = Util::Bits<Bits::k_addr, 4, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 3.
                using Pupdr3 = Util::Bits<Bits::k_addr, 6, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 4.
                using Pupdr4 = Util::Bits<Bits::k_addr, 8, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 5.
                using Pupdr5 = Util::Bits<Bits::k_addr, 10, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 6.
                using Pupdr6 = Util::Bits<Bits::k_addr, 12, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 7.
                using Pupdr7 = Util::Bits<Bits::k_addr, 14, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 8.
                using Pupdr8 = Util::Bits<Bits::k_addr, 16, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 9.
                using Pupdr9 = Util::Bits<Bits::k_addr, 18, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 10.
                using Pupdr10 = Util::Bits<Bits::k_addr, 20, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 11.
                using Pupdr11 = Util::Bits<Bits::k_addr, 22, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 12.
                using Pupdr12 = Util::Bits<Bits::k_addr, 24, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 13.
                using Pupdr13 = Util::Bits<Bits::k_addr, 26, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 14.
                using Pupdr14 = Util::Bits<Bits::k_addr, 28, 2, GpioPupd>;
                // Pull Up/Down Register bits for pin 15.
                using Pupdr15 = Util::Bits<Bits::k_addr, 30, 2, GpioPupd>;
            };

            // Input Data Register.
            using Idr = Util::BitsRegister<k_baseAddr, 0x10, GpioPin, 1, Common::PinState, void>;

            // Output Data Register.
            using Odr = Util::BitsRegister<k_baseAddr, 0x14, GpioPin, 1, Common::PinState>;

            // Bit Set/Reset Register.
            struct Bsrr
            {
                static constexpr Common::Word k_offset = 0x18;
                static constexpr Common::Address k_addr = k_baseAddr + k_offset;

                // Set values.
                enum class SValue : Common::Word
                {
                    NoAction = 0b0,
                    Set = 0b1
                };

                // Reset values.
                enum class RValue : Common::Word
                {
                    NoAction = 0b0,
                    Reset = 0b1
                };

                // Bit Set for pins 0-15.
                using Bs = Util::WoBits<k_addr, 0, 16, Common::Word>;

                // Bit Reset for pins 0-15.
                using Br = Util::WoBits<k_addr, 16, 16, Common::Word>;

                // Bit Set for pin 0.
                using Bs0 = Util::WoBits<k_addr, 0, 1, SValue>;
                // Bit Set for pin 1.
                using Bs1 = Util::WoBits<k_addr, 1, 1, SValue>;
                // Bit Set for pin 2.
                using Bs2 = Util::WoBits<k_addr, 2, 1, SValue>;
                // Bit Set for pin 3.
                using Bs3 = Util::WoBits<k_addr, 3, 1, SValue>;
                // Bit Set for pin 4.
                using Bs4 = Util::WoBits<k_addr, 4, 1, SValue>;
                // Bit Set for pin 5.
                using Bs5 = Util::WoBits<k_addr, 5, 1, SValue>;
                // Bit Set for pin 6.
                using Bs6 = Util::WoBits<k_addr, 6, 1, SValue>;
                // Bit Set for pin 7.
                using Bs7 = Util::WoBits<k_addr, 7, 1, SValue>;
                // Bit Set for pin 8.
                using Bs8 = Util::WoBits<k_addr, 8, 1, SValue>;
                // Bit Set for pin 9.
                using Bs9 = Util::WoBits<k_addr, 9, 1, SValue>;
                // Bit Set for pin 10.
                using Bs10 = Util::WoBits<k_addr, 10, 1, SValue>;
                // Bit Set for pin 11.
                using Bs11 = Util::WoBits<k_addr, 11, 1, SValue>;
                // Bit Set for pin 12.
                using Bs12 = Util::WoBits<k_addr, 12, 1, SValue>;
                // Bit Set for pin 13.
                using Bs13 = Util::WoBits<k_addr, 13, 1, SValue>;
                // Bit Set for pin 14.
                using Bs14 = Util::WoBits<k_addr, 14, 1, SValue>;
                // Bit Set for pin 15.
                using Bs15 = Util::WoBits<k_addr, 15, 1, SValue>;

                // Bit Reset for pin 0.
                using Br0 = Util::WoBits<k_addr, 16, 1, RValue>;
                // Bit Reset for pin 1.
                using Br1 = Util::WoBits<k_addr, 17, 1, RValue>;
                // Bit Reset for pin 2.
                using Br2 = Util::WoBits<k_addr, 18, 1, RValue>;
                // Bit Reset for pin 3.
                using Br3 = Util::WoBits<k_addr, 19, 1, RValue>;
                // Bit Reset for pin 4.
                using Br4 = Util::WoBits<k_addr, 20, 1, RValue>;
                // Bit Reset for pin 5.
                using Br5 = Util::WoBits<k_addr, 21, 1, RValue>;
                // Bit Reset for pin 6.
                using Br6 = Util::WoBits<k_addr, 22, 1, RValue>;
                // Bit Reset for pin 7.
                using Br7 = Util::WoBits<k_addr, 23, 1, RValue>;
                // Bit Reset for pin 8.
                using Br8 = Util::WoBits<k_addr, 24, 1, RValue>;
                // Bit Reset for pin 9.
                using Br9 = Util::WoBits<k_addr, 25, 1, RValue>;
                // Bit Reset for pin 10.
                using Br10 = Util::WoBits<k_addr, 26, 1, RValue>;
                // Bit Reset for pin 11.
                using Br11 = Util::WoBits<k_addr, 27, 1, RValue>;
                // Bit Reset for pin 12.
                using Br12 = Util::WoBits<k_addr, 28, 1, RValue>;
                // Bit Reset for pin 13.
                using Br13 = Util::WoBits<k_addr, 29, 1, RValue>;
                // Bit Reset for pin 14.
                using Br14 = Util::WoBits<k_addr, 30, 1, RValue>;
                // Bit Reset for pin 15.
                using Br15 = Util::WoBits<k_addr, 31, 1, RValue>;
            };

            // Configuration Lock Register.
            struct Lckr
            {
                static constexpr Common::Word k_offset = 0x1c;
                static constexpr Common::Address k_addr = k_baseAddr + k_offset;

                // Lock Key.
                using Lckk = Util::RoBits<k_addr, 16, 1, Common::Word>;

                // Port 0 lock bit.
                using Lck0 = Util::RoBits<k_addr, 0, 1, Common::Word>;
                // Port 1 lock bit.
                using Lck1 = Util::RoBits<k_addr, 1, 1, Common::Word>;
                // Port 2 lock bit.
                using Lck2 = Util::RoBits<k_addr, 2, 1, Common::Word>;
                // Port 3 lock bit.
                using Lck3 = Util::RoBits<k_addr, 3, 1, Common::Word>;
                // Port 4 lock bit.
                using Lck4 = Util::RoBits<k_addr, 4, 1, Common::Word>;
                // Port 5 lock bit.
                using Lck5 = Util::RoBits<k_addr, 5, 1, Common::Word>;
                // Port 6 lock bit.
                using Lck6 = Util::RoBits<k_addr, 6, 1, Common::Word>;
                // Port 7 lock bit.
                using Lck7 = Util::RoBits<k_addr, 7, 1, Common::Word>;
                // Port 8 lock bit.
                using Lck8 = Util::RoBits<k_addr, 8, 1, Common::Word>;
                // Port 9 lock bit.
                using Lck9 = Util::RoBits<k_addr, 9, 1, Common::Word>;
                // Port 10 lock bit.
                using Lck10 = Util::RoBits<k_addr, 10, 1, Common::Word>;
                // Port 11 lock bit.
                using Lck11 = Util::RoBits<k_addr, 11, 1, Common::Word>;
                // Port 12 lock bit.
                using Lck12 = Util::RoBits<k_addr, 12, 1, Common::Word>;
                // Port 13 lock bit.
                using Lck13 = Util::RoBits<k_addr, 13, 1, Common::Word>;
                // Port 14 lock bit.
                using Lck14 = Util::RoBits<k_addr, 14, 1, Common::Word>;
                // Port 15 lock bit.
                using Lck15 = Util::RoBits<k_addr, 15, 1, Common::Word>;
            };

            // Alternate function register, low word.
            struct Afrl
            {
                using Bits = Util::BitsRegister<k_baseAddr, 0x20, GpioPin, 4, GpioAltFunc>;

                using Afrl0 = Util::Bits<Bits::k_addr, 0, 4, typename GpioPinTraits<TVPort, GpioPin::Pin0>::AltFunc>;
                using Afrl1 = Util::Bits<Bits::k_addr, 4, 4, typename GpioPinTraits<TVPort, GpioPin::Pin1>::AltFunc>;
                using Afrl2 = Util::Bits<Bits::k_addr, 8, 4, typename GpioPinTraits<TVPort, GpioPin::Pin2>::AltFunc>;
                using Afrl3 = Util::Bits<Bits::k_addr, 12, 4, typename GpioPinTraits<TVPort, GpioPin::Pin3>::AltFunc>;
                using Afrl4 = Util::Bits<Bits::k_addr, 16, 4, typename GpioPinTraits<TVPort, GpioPin::Pin4>::AltFunc>;
                using Afrl5 = Util::Bits<Bits::k_addr, 20, 4, typename GpioPinTraits<TVPort, GpioPin::Pin5>::AltFunc>;
                using Afrl6 = Util::Bits<Bits::k_addr, 24, 4, typename GpioPinTraits<TVPort, GpioPin::Pin6>::AltFunc>;
                using Afrl7 = Util::Bits<Bits::k_addr, 28, 4, typename GpioPinTraits<TVPort, GpioPin::Pin7>::AltFunc>;
            };

            // Alternate function register, high word.
            struct Afrh
            {
                using Bits = Util::BitsRegister<k_baseAddr, 0x24, GpioPin, 4, GpioAltFunc>;

                using Afrh8 = Util::Bits<Bits::k_addr, 0, 4, typename GpioPinTraits<TVPort, GpioPin::Pin8>::AltFunc>;
                using Afrh9 = Util::Bits<Bits::k_addr, 4, 4, typename GpioPinTraits<TVPort, GpioPin::Pin9>::AltFunc>;
                using Afrh10 = Util::Bits<Bits::k_addr, 8, 4, typename GpioPinTraits<TVPort, GpioPin::Pin10>::AltFunc>;
                using Afrh11 = Util::Bits<Bits::k_addr, 12, 4, typename GpioPinTraits<TVPort, GpioPin::Pin11>::AltFunc>;
                using Afrh12 = Util::Bits<Bits::k_addr, 16, 4, typename GpioPinTraits<TVPort, GpioPin::Pin12>::AltFunc>;
                using Afrh13 = Util::Bits<Bits::k_addr, 20, 4, typename GpioPinTraits<TVPort, GpioPin::Pin13>::AltFunc>;
                using Afrh14 = Util::Bits<Bits::k_addr, 24, 4, typename GpioPinTraits<TVPort, GpioPin::Pin14>::AltFunc>;
                using Afrh15 = Util::Bits<Bits::k_addr, 28, 4, typename GpioPinTraits<TVPort, GpioPin::Pin15>::AltFunc>;
            };
        };
    } // namespace detail

    // GPIO port A.
    using GpioA = detail::GpioX<GpioPort::PortA, k_addr + 0x0000U>;

    // GPIO port B.
    using GpioB = detail::GpioX<GpioPort::PortB, k_addr + 0x0400U>;

    // GPIO port C.
    using GpioC = detail::GpioX<GpioPort::PortC, k_addr + 0x0800U>;

    // GPIO port D.
    using GpioD = detail::GpioX<GpioPort::PortD, k_addr + 0x0c00U>;

    // GPIO port E.
    using GpioE = detail::GpioX<GpioPort::PortE, k_addr + 0x1000U>;

    // GPIO port F.
    using GpioF = detail::GpioX<GpioPort::PortF, k_addr + 0x1400U>;

    // GPIO port G.
    using GpioG = detail::GpioX<GpioPort::PortG, k_addr + 0x1800U>;

    // GPIO port H.
    using GpioH = detail::GpioX<GpioPort::PortH, k_addr + 0x1c00U>;

    // GPIO port I.
    using GpioI = detail::GpioX<GpioPort::PortI, k_addr + 0x2000U>;

    // GPIO port J.
    using GpioJ = detail::GpioX<GpioPort::PortJ, k_addr + 0x2400U>;

    // GPIO port K.
    using GpioK = detail::GpioX<GpioPort::PortK, k_addr + 0x2800U>;
} // namespace Stm32f407::Bitapi::Ahb1::Gpio
