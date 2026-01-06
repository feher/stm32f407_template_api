#pragma once

#include "stm32f407_utils.hpp"
#include <cassert>

namespace Ahb1::Gpio
{
    // GPIO pin number.
    enum class GpioPin : int
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
        Pin15 = 15
    };

    // Generic alternate function values for GPIO port X pin Y.
    enum class GpioAltFunc : Word
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

    // GPIO pin mode values.
    enum class GpioMode : Word
    {
        Input = 0b00,
        Output = 0b01,
        AltFunc = 0b10,
        Analog = 0b11
    };

    // GPIO pin output type values.
    enum class GpioOutputType : Word
    {
        PushPull = 0,
        OpenDrain = 1
    };

    // GPIO pin output speed values.
    enum class GpioOutputSpeed : Word
    {
        Low = 0b00,
        Medium = 0b01,
        High = 0b10,
        VeryHigh = 0b11
    };

    // GPIO pin pull up/down values.
    enum class GpioPupd : Word
    {
        NoPull = 0b00,
        PullUp = 0b01,
        PullDown = 0b10
    };

    namespace detail
    {
        template <Address baseAddr, typename TAfValues>
        struct GpioX
        {
            static constexpr Address k_baseAddr = baseAddr;

            // Mode Register.
            struct Moder
            {
                static constexpr Word k_offset = 0x00;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the mode of a pin.
                static void set(GpioPin pin, GpioMode mode)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, intPin << 1, 2, mode);
                }

                // Get the mode of a pin.
                static GpioMode get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<GpioMode>(*p, intPin << 1, 2);
                }

                // Mode register bits for pin 0.
                using Moder0 = Bits<k_addr, 0, 2, GpioMode>;
                // Mode register bits for pin 1.
                using Moder1 = Bits<k_addr, 2, 2, GpioMode>;
                // Mode register bits for pin 2.
                using Moder2 = Bits<k_addr, 4, 2, GpioMode>;
                // Mode register bits for pin 3.
                using Moder3 = Bits<k_addr, 6, 2, GpioMode>;
                // Mode register bits for pin 4.
                using Moder4 = Bits<k_addr, 8, 2, GpioMode>;
                // Mode register bits for pin 5.
                using Moder5 = Bits<k_addr, 10, 2, GpioMode>;
                // Mode register bits for pin 6.
                using Moder6 = Bits<k_addr, 12, 2, GpioMode>;
                // Mode register bits for pin 7.
                using Moder7 = Bits<k_addr, 14, 2, GpioMode>;
                // Mode register bits for pin 8.
                using Moder8 = Bits<k_addr, 16, 2, GpioMode>;
                // Mode register bits for pin 9.
                using Moder9 = Bits<k_addr, 18, 2, GpioMode>;
                // Mode register bits for pin 10.
                using Moder10 = Bits<k_addr, 20, 2, GpioMode>;
                // Mode register bits for pin 11.
                using Moder11 = Bits<k_addr, 22, 2, GpioMode>;
                // Mode register bits for pin 12.
                using Moder12 = Bits<k_addr, 24, 2, GpioMode>;
                // Mode register bits for pin 13.
                using Moder13 = Bits<k_addr, 26, 2, GpioMode>;
                // Mode register bits for pin 14.
                using Moder14 = Bits<k_addr, 28, 2, GpioMode>;
                // Mode register bits for pin 15.
                using Moder15 = Bits<k_addr, 30, 2, GpioMode>;
            };

            // Output Type Register.
            struct Otyper
            {
                static constexpr Word k_offset = 0x04;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the output type of a pin.
                static void set(GpioPin pin, GpioOutputType outputType)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, intPin, 1, outputType);
                }

                // Get the output type of a pin.
                static GpioOutputType get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<GpioOutputType>(*p, intPin, 1);
                }

                // Output type for pin 0.
                using Ot0 = Bits<GpioOutputType, k_addr, 0, 1>;
                // Output type for pin 1.
                using Ot1 = Bits<GpioOutputType, k_addr, 1, 1>;
                // Output type for pin 2.
                using Ot2 = Bits<GpioOutputType, k_addr, 2, 1>;
                // Output type for pin 3.
                using Ot3 = Bits<GpioOutputType, k_addr, 3, 1>;
                // Output type for pin 4.
                using Ot4 = Bits<GpioOutputType, k_addr, 4, 1>;
                // Output type for pin 5.
                using Ot5 = Bits<GpioOutputType, k_addr, 5, 1>;
                // Output type for pin 6.
                using Ot6 = Bits<GpioOutputType, k_addr, 6, 1>;
                // Output type for pin 7.
                using Ot7 = Bits<GpioOutputType, k_addr, 7, 1>;
                // Output type for pin 8.
                using Ot8 = Bits<GpioOutputType, k_addr, 8, 1>;
                // Output type for pin 9.
                using Ot9 = Bits<GpioOutputType, k_addr, 9, 1>;
                // Output type for pin 10.
                using Ot10 = Bits<GpioOutputType, k_addr, 10, 1>;
                // Output type for pin 11.
                using Ot11 = Bits<GpioOutputType, k_addr, 11, 1>;
                // Output type for pin 12.
                using Ot12 = Bits<GpioOutputType, k_addr, 12, 1>;
                // Output type for pin 13.
                using Ot13 = Bits<GpioOutputType, k_addr, 13, 1>;
                // Output type for pin 14.
                using Ot14 = Bits<GpioOutputType, k_addr, 14, 1>;
                // Output type for pin 15.
                using Ot15 = Bits<GpioOutputType, k_addr, 15, 1>;
            };

            // Output Speed Register.
            // The speed of the low-to-high (T-rise) and high-to-low (T-fall) transitions
            // (i.e. this is not the frequency of the signal).
            struct Ospeedr
            {
                static constexpr Word k_offset = 0x08;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the output speed of a pin.
                static void set(GpioPin pin, GpioOutputSpeed outputSpeed)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, intPin << 1, 2, outputSpeed);
                }

                // Get the output speed of a pin.
                static GpioOutputSpeed get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<GpioOutputSpeed>(*p, intPin << 1, 2);
                }

                // Output Speed Register bits for pin 0.
                using Ospeedr0 = Bits<GpioOutputSpeed, k_addr, 0, 2>;
                // Output Speed Register bits for pin 1.
                using Ospeedr1 = Bits<GpioOutputSpeed, k_addr, 2, 2>;
                // Output Speed Register bits for pin 2.
                using Ospeedr2 = Bits<GpioOutputSpeed, k_addr, 4, 2>;
                // Output Speed Register bits for pin 3.
                using Ospeedr3 = Bits<GpioOutputSpeed, k_addr, 6, 2>;
                // Output Speed Register bits for pin 4.
                using Ospeedr4 = Bits<GpioOutputSpeed, k_addr, 8, 2>;
                // Output Speed Register bits for pin 5.
                using Ospeedr5 = Bits<GpioOutputSpeed, k_addr, 10, 2>;
                // Output Speed Register bits for pin 6.
                using Ospeedr6 = Bits<GpioOutputSpeed, k_addr, 12, 2>;
                // Output Speed Register bits for pin 7.
                using Ospeedr7 = Bits<GpioOutputSpeed, k_addr, 14, 2>;
                // Output Speed Register bits for pin 8.
                using Ospeedr8 = Bits<GpioOutputSpeed, k_addr, 16, 2>;
                // Output Speed Register bits for pin 9.
                using Ospeedr9 = Bits<GpioOutputSpeed, k_addr, 18, 2>;
                // Output Speed Register bits for pin 10.
                using Ospeedr10 = Bits<GpioOutputSpeed, k_addr, 20, 2>;
                // Output Speed Register bits for pin 11.
                using Ospeedr11 = Bits<GpioOutputSpeed, k_addr, 22, 2>;
                // Output Speed Register bits for pin 12.
                using Ospeedr12 = Bits<GpioOutputSpeed, k_addr, 24, 2>;
                // Output Speed Register bits for pin 13.
                using Ospeedr13 = Bits<GpioOutputSpeed, k_addr, 26, 2>;
                // Output Speed Register bits for pin 14.
                using Ospeedr14 = Bits<GpioOutputSpeed, k_addr, 28, 2>;
                // Output Speed Register bits for pin 15.
                using Ospeedr15 = Bits<GpioOutputSpeed, k_addr, 30, 2>;
            };

            // Pull Up/Down Register.
            struct Pupdr
            {
                static constexpr Word k_offset = 0x0c;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the pull up/down configuration of a pin.
                static void set(GpioPin pin, GpioPupd pupd)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, intPin << 1, 2, pupd);
                }

                // Get the pull up/down configuration of a pin.
                static GpioPupd get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<GpioPupd>(*p, intPin << 1, 2);
                }

                // Pull Up/Down Register bits for pin 0.
                using Pupdr0 = Bits<GpioPupd, k_addr, 0, 2>;
                // Pull Up/Down Register bits for pin 1.
                using Pupdr1 = Bits<GpioPupd, k_addr, 2, 2>;
                // Pull Up/Down Register bits for pin 2.
                using Pupdr2 = Bits<GpioPupd, k_addr, 4, 2>;
                // Pull Up/Down Register bits for pin 3.
                using Pupdr3 = Bits<GpioPupd, k_addr, 6, 2>;
                // Pull Up/Down Register bits for pin 4.
                using Pupdr4 = Bits<GpioPupd, k_addr, 8, 2>;
                // Pull Up/Down Register bits for pin 5.
                using Pupdr5 = Bits<GpioPupd, k_addr, 10, 2>;
                // Pull Up/Down Register bits for pin 6.
                using Pupdr6 = Bits<GpioPupd, k_addr, 12, 2>;
                // Pull Up/Down Register bits for pin 7.
                using Pupdr7 = Bits<GpioPupd, k_addr, 14, 2>;
                // Pull Up/Down Register bits for pin 8.
                using Pupdr8 = Bits<GpioPupd, k_addr, 16, 2>;
                // Pull Up/Down Register bits for pin 9.
                using Pupdr9 = Bits<GpioPupd, k_addr, 18, 2>;
                // Pull Up/Down Register bits for pin 10.
                using Pupdr10 = Bits<GpioPupd, k_addr, 20, 2>;
                // Pull Up/Down Register bits for pin 11.
                using Pupdr11 = Bits<GpioPupd, k_addr, 22, 2>;
                // Pull Up/Down Register bits for pin 12.
                using Pupdr12 = Bits<GpioPupd, k_addr, 24, 2>;
                // Pull Up/Down Register bits for pin 13.
                using Pupdr13 = Bits<GpioPupd, k_addr, 26, 2>;
                // Pull Up/Down Register bits for pin 14.
                using Pupdr14 = Bits<GpioPupd, k_addr, 28, 2>;
                // Pull Up/Down Register bits for pin 15.
                using Pupdr15 = Bits<GpioPupd, k_addr, 30, 2>;
            };

            // Input Data Register.
            struct Idr
            {
                static constexpr Word k_offset = 0x10;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Get the input state of a pin.
                static PinState get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<PinState>(*p, intPin, 1);
                }
            };

            // Output Data Register.
            // using Odr = Bits<Word, k_baseAddr + 0x14, 0, 16>;
            struct Odr
            {
                static constexpr Word k_offset = 0x14;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the output state of a pin.
                static void set(GpioPin pin, PinState state)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, intPin, 1, state);
                }

                // Get the output state of a pin.
                static PinState get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<PinState>(*p, intPin, 1);
                }
            };

            // Bit Set/Reset Register.
            struct Bsrr
            {
                static constexpr Word k_offset = 0x18;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set values.
                enum class SValue : Word
                {
                    NoAction = 0b0,
                    Set = 0b1
                };

                // Reset values.
                enum class RValue : Word
                {
                    NoAction = 0b0,
                    Reset = 0b1
                };

                // Bit Set for pins 0-15.
                using Bs = WoBits<Word, k_addr, 0, 16>;

                // Bit Reset for pins 0-15.
                using Br = WoBits<Word, k_addr, 16, 16>;

                // Bit Set for pin 0.
                using Bs0 = WoBits<SValue, k_addr, 0, 1>;
                // Bit Set for pin 1.
                using Bs1 = WoBits<SValue, k_addr, 1, 1>;
                // Bit Set for pin 2.
                using Bs2 = WoBits<SValue, k_addr, 2, 1>;
                // Bit Set for pin 3.
                using Bs3 = WoBits<SValue, k_addr, 3, 1>;
                // Bit Set for pin 4.
                using Bs4 = WoBits<SValue, k_addr, 4, 1>;
                // Bit Set for pin 5.
                using Bs5 = WoBits<SValue, k_addr, 5, 1>;
                // Bit Set for pin 6.
                using Bs6 = WoBits<SValue, k_addr, 6, 1>;
                // Bit Set for pin 7.
                using Bs7 = WoBits<SValue, k_addr, 7, 1>;
                // Bit Set for pin 8.
                using Bs8 = WoBits<SValue, k_addr, 8, 1>;
                // Bit Set for pin 9.
                using Bs9 = WoBits<SValue, k_addr, 9, 1>;
                // Bit Set for pin 10.
                using Bs10 = WoBits<SValue, k_addr, 10, 1>;
                // Bit Set for pin 11.
                using Bs11 = WoBits<SValue, k_addr, 11, 1>;
                // Bit Set for pin 12.
                using Bs12 = WoBits<SValue, k_addr, 12, 1>;
                // Bit Set for pin 13.
                using Bs13 = WoBits<SValue, k_addr, 13, 1>;
                // Bit Set for pin 14.
                using Bs14 = WoBits<SValue, k_addr, 14, 1>;
                // Bit Set for pin 15.
                using Bs15 = WoBits<SValue, k_addr, 15, 1>;

                // Bit Reset for pin 0.
                using Br0 = WoBits<RValue, k_addr, 16, 1>;
                // Bit Reset for pin 1.
                using Br1 = WoBits<RValue, k_addr, 17, 1>;
                // Bit Reset for pin 2.
                using Br2 = WoBits<RValue, k_addr, 18, 1>;
                // Bit Reset for pin 3.
                using Br3 = WoBits<RValue, k_addr, 19, 1>;
                // Bit Reset for pin 4.
                using Br4 = WoBits<RValue, k_addr, 20, 1>;
                // Bit Reset for pin 5.
                using Br5 = WoBits<RValue, k_addr, 21, 1>;
                // Bit Reset for pin 6.
                using Br6 = WoBits<RValue, k_addr, 22, 1>;
                // Bit Reset for pin 7.
                using Br7 = WoBits<RValue, k_addr, 23, 1>;
                // Bit Reset for pin 8.
                using Br8 = WoBits<RValue, k_addr, 24, 1>;
                // Bit Reset for pin 9.
                using Br9 = WoBits<RValue, k_addr, 25, 1>;
                // Bit Reset for pin 10.
                using Br10 = WoBits<RValue, k_addr, 26, 1>;
                // Bit Reset for pin 11.
                using Br11 = WoBits<RValue, k_addr, 27, 1>;
                // Bit Reset for pin 12.
                using Br12 = WoBits<RValue, k_addr, 28, 1>;
                // Bit Reset for pin 13.
                using Br13 = WoBits<RValue, k_addr, 29, 1>;
                // Bit Reset for pin 14.
                using Br14 = WoBits<RValue, k_addr, 30, 1>;
                // Bit Reset for pin 15.
                using Br15 = WoBits<RValue, k_addr, 31, 1>;
            };

            // Configuration Lock Register.
            struct Lckr
            {
                static constexpr Word k_offset = 0x1c;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Lock Key.
                using Lckk = RoBits<Word, k_addr, 16, 1>;

                // Port 0 lock bit.
                using Lck0 = RoBits<Word, k_addr, 0, 1>;
                // Port 1 lock bit.
                using Lck1 = RoBits<Word, k_addr, 1, 1>;
                // Port 2 lock bit.
                using Lck2 = RoBits<Word, k_addr, 2, 1>;
                // Port 3 lock bit.
                using Lck3 = RoBits<Word, k_addr, 3, 1>;
                // Port 4 lock bit.
                using Lck4 = RoBits<Word, k_addr, 4, 1>;
                // Port 5 lock bit.
                using Lck5 = RoBits<Word, k_addr, 5, 1>;
                // Port 6 lock bit.
                using Lck6 = RoBits<Word, k_addr, 6, 1>;
                // Port 7 lock bit.
                using Lck7 = RoBits<Word, k_addr, 7, 1>;
                // Port 8 lock bit.
                using Lck8 = RoBits<Word, k_addr, 8, 1>;
                // Port 9 lock bit.
                using Lck9 = RoBits<Word, k_addr, 9, 1>;
                // Port 10 lock bit.
                using Lck10 = RoBits<Word, k_addr, 10, 1>;
                // Port 11 lock bit.
                using Lck11 = RoBits<Word, k_addr, 11, 1>;
                // Port 12 lock bit.
                using Lck12 = RoBits<Word, k_addr, 12, 1>;
                // Port 13 lock bit.
                using Lck13 = RoBits<Word, k_addr, 13, 1>;
                // Port 14 lock bit.
                using Lck14 = RoBits<Word, k_addr, 14, 1>;
                // Port 15 lock bit.
                using Lck15 = RoBits<Word, k_addr, 15, 1>;
            };

            // Pin0 alternate function values.
            using Pin0AfValues = typename TAfValues::Pin0;
            // Pin1 alternate function values.
            using Pin1AfValues = typename TAfValues::Pin1;
            using Pin2AfValues = typename TAfValues::Pin2;
            using Pin3AfValues = typename TAfValues::Pin3;
            using Pin4AfValues = typename TAfValues::Pin4;
            using Pin5AfValues = typename TAfValues::Pin5;
            using Pin6AfValues = typename TAfValues::Pin6;
            using Pin7AfValues = typename TAfValues::Pin7;
            using Pin8AfValues = typename TAfValues::Pin8;
            using Pin9AfValues = typename TAfValues::Pin9;
            using Pin10AfValues = typename TAfValues::Pin10;
            using Pin11AfValues = typename TAfValues::Pin11;
            using Pin12AfValues = typename TAfValues::Pin12;
            using Pin13AfValues = typename TAfValues::Pin13;
            using Pin14AfValues = typename TAfValues::Pin14;
            using Pin15AfValues = typename TAfValues::Pin15;

            // Alternate function register, low word.
            struct Afrl
            {
                static constexpr Word k_offset = 0x20;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the alternate function of pins 0-7.
                static void set(GpioPin pin, GpioAltFunc altFunction)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 7);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, intPin << 2, 4, altFunction);
                }

                // Get the alternate function of pins 0-7.
                static GpioAltFunc get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(0 <= intPin && intPin <= 7);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<GpioAltFunc>(*p, intPin << 2, 4);
                }

                using Afrl0 = Bits<Pin0AfValues, k_addr, 0, 4>;
                using Afrl1 = Bits<Pin1AfValues, k_addr, 4, 4>;
                using Afrl2 = Bits<Pin2AfValues, k_addr, 8, 4>;
                using Afrl3 = Bits<Pin3AfValues, k_addr, 12, 4>;
                using Afrl4 = Bits<Pin4AfValues, k_addr, 16, 4>;
                using Afrl5 = Bits<Pin5AfValues, k_addr, 20, 4>;
                using Afrl6 = Bits<Pin6AfValues, k_addr, 24, 4>;
                using Afrl7 = Bits<Pin7AfValues, k_addr, 28, 4>;
            };

            // Alternate function register, high word.
            struct Afrh
            {
                static constexpr Word k_offset = 0x24;
                static constexpr Address k_addr = k_baseAddr + k_offset;

                // Set the alternate function of pins 8-15.
                static void set(GpioPin pin, GpioAltFunc altFunction)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(8 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    *p = set_bits(*p, (intPin - 8) << 2, 4, altFunction);
                }

                // Get the alternate function of pins 8-15.
                static GpioAltFunc get(GpioPin pin)
                {
                    const auto intPin = static_cast<int>(pin);
                    assert(8 <= intPin && intPin <= 15);
                    volatile Word* p = reinterpret_cast<Word*>(k_addr);
                    return extract_bits_as<GpioAltFunc>(*p, (intPin - 8) << 2, 4);
                }

                using Afrh8 = Bits<Pin8AfValues, k_addr, 0, 4>;
                using Afrh9 = Bits<Pin9AfValues, k_addr, 4, 4>;
                using Afrh10 = Bits<Pin10AfValues, k_addr, 8, 4>;
                using Afrh11 = Bits<Pin11AfValues, k_addr, 12, 4>;
                using Afrh12 = Bits<Pin12AfValues, k_addr, 16, 4>;
                using Afrh13 = Bits<Pin13AfValues, k_addr, 20, 4>;
                using Afrh14 = Bits<Pin14AfValues, k_addr, 24, 4>;
                using Afrh15 = Bits<Pin15AfValues, k_addr, 28, 4>;
            };
        };

        // Alternate function values for GPIO port A pin 0.
        enum class GpioA0AltFunc : Word
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
        enum class GpioA8AltFunc : Word
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

        // Alternate function values for GPIO port C pin 6.
        enum class GpioC6AltFunc : Word
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
        enum class GpioC9AltFunc : Word
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

        template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
                  typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13,
                  typename T14, typename T15>
        struct GpioAfValues
        {
            using Pin0 = T0;
            using Pin1 = T1;
            using Pin2 = T2;
            using Pin3 = T3;
            using Pin4 = T4;
            using Pin5 = T5;
            using Pin6 = T6;
            using Pin7 = T7;
            using Pin8 = T8;
            using Pin9 = T9;
            using Pin10 = T10;
            using Pin11 = T11;
            using Pin12 = T12;
            using Pin13 = T13;
            using Pin14 = T14;
            using Pin15 = T15;
        };

        // Generic alternate function values for GPIO ports.
        using GpioXAfValues = GpioAfValues<GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc,
                                           GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc,
                                           GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc>;

        // Alternate function values for GPIO port A.
        using GpioAAfValues =
            GpioAfValues<GpioA0AltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc,
                         GpioAltFunc, GpioA8AltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc,
                         GpioAltFunc, GpioAltFunc>;

        // Alternate function values for GPIO port C.
        using GpioCAfValues = GpioAfValues<GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc,
                                           GpioC6AltFunc, GpioAltFunc, GpioAltFunc, GpioC9AltFunc, GpioAltFunc,
                                           GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc, GpioAltFunc>;
    } // namespace detail

    // GPIO port A.
    using GpioA = detail::GpioX<0x4002'0000U, detail::GpioAAfValues>;

    // GPIO port B.
    using GpioB = detail::GpioX<0x4002'0400U, detail::GpioXAfValues>;

    // GPIO port C.
    using GpioC = detail::GpioX<0x4002'0800U, detail::GpioCAfValues>;

    // GPIO port D.
    using GpioD = detail::GpioX<0x4002'0c00U, detail::GpioXAfValues>;

    // GPIO port E.
    using GpioE = detail::GpioX<0x4002'1000U, detail::GpioXAfValues>;

    // GPIO port F.
    using GpioF = detail::GpioX<0x4002'1400U, detail::GpioXAfValues>;

    // GPIO port G.
    using GpioG = detail::GpioX<0x4002'1800U, detail::GpioXAfValues>;

    // GPIO port H.
    using GpioH = detail::GpioX<0x4002'1c00U, detail::GpioXAfValues>;

    // GPIO port I.
    using GpioI = detail::GpioX<0x4002'2000U, detail::GpioXAfValues>;

    // GPIO port J.
    using GpioJ = detail::GpioX<0x4002'2400U, detail::GpioXAfValues>;

    // GPIO port K.
    using GpioK = detail::GpioX<0x4002'2800U, detail::GpioXAfValues>;
} // namespace Ahb1::Gpio
