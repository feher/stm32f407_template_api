#pragma once

#include "common.hpp"

#include <stm32f407_bitapi/stm32f407_ahb1_gpio.hpp>
#include <stm32f407_bitapi/stm32f407_ahb1_rcc.hpp>
#include <stm32f407_bitapi/stm32f407_apb2_exti.hpp>
#include <stm32f407_bitapi/stm32f407_apb2_syscfg.hpp>
#include <stm32f407_bitapi/stm32f407_core_nvic.hpp>
#include <stm32f407_bitapi/stm32f407_utils.hpp>

#include <array>
#include <functional>
#include <utility>

namespace Stm32f407::Driver
{
    using GpioPort = Bitapi::Ahb1::Gpio::GpioPort;
    using GpioPin = Bitapi::Ahb1::Gpio::GpioPin;
    using GpioMode = Bitapi::Ahb1::Gpio::GpioMode;
    using GpioOutputType = Bitapi::Ahb1::Gpio::GpioOutputType;
    using GpioOutputSpeed = Bitapi::Ahb1::Gpio::GpioOutputSpeed;
    using GpioPupd = Bitapi::Ahb1::Gpio::GpioPupd;
    using GpioAltFunc = Bitapi::Ahb1::Gpio::GpioAltFunc;

    using GpioAltFuncA8 = Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPort::PortA, GpioPin::Pin8>::AltFunc;
    using GpioAltFuncB12 = Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPort::PortB, GpioPin::Pin12>::AltFunc;
    using GpioAltFuncB13 = Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPort::PortB, GpioPin::Pin13>::AltFunc;
    using GpioAltFuncB14 = Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPort::PortB, GpioPin::Pin14>::AltFunc;
    using GpioAltFuncB15 = Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPort::PortB, GpioPin::Pin15>::AltFunc;
    using GpioAltFuncC9 = Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPort::PortC, GpioPin::Pin9>::AltFunc;

    enum class GpioInterruptMode : Bitapi::Common::Word
    {
        RisingEdge,
        FallingEdge,
        RisingAndFallingEdge
    };

    namespace detail
    {
        extern std::array<IrqHandler, Bitapi::Apb2::Exti::k_lineCount> g_gpioIrqHandlers;

        template <GpioPort TVPort>
        struct GpioPortTraits
        {
        };

        template <>
        struct GpioPortTraits<GpioPort::PortA>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioA;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioAEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioARst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortB>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioB;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioBEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioBRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortC>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioC;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioCEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioCRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortD>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioD;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioDEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioDRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortE>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioE;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioEEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioERst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortF>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioF;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioFEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioFRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortG>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioG;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioGEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioGRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortH>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioH;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioHEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioHRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortI>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioI;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioIEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioIRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortJ>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioJ;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioJEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioJRst;
        };

        template <>
        struct GpioPortTraits<GpioPort::PortK>
        {
            using Type = Bitapi::Ahb1::Gpio::GpioK;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Ahb1Enr::GpioKEn;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioKRst;
        };

        template <GpioPin TVPin>
        struct GpioPinTraits
        {
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin0>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr1::Exit0;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin1>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr1::Exit1;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin2>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr1::Exit2;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin3>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr1::Exit3;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin4>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr2::Exit4;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin5>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr2::Exit5;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin6>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr2::Exit6;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin7>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr2::Exit7;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin8>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr3::Exit8;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin9>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr3::Exit9;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin10>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr3::Exit10;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin11>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr3::Exit11;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin12>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr4::Exit12;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin13>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr4::Exit13;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin14>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr4::Exit14;
        };

        template <>
        struct GpioPinTraits<GpioPin::Pin15>
        {
            using SyscfgExticrBits = Bitapi::Apb2::Syscfg::Exticr4::Exit15;
        };

        template <GpioPort TVPort, GpioPin TVPin>
        class GpioXPinY final
        {
        private:
            using GpioPortType = GpioPortTraits<TVPort>::Type;
            using SyscfgExticrBits = GpioPinTraits<TVPin>::SyscfgExticrBits;

        public:
            void setMode(GpioMode mode)
            {
                GpioPortType::Moder::Bits::set(TVPin, mode);
            }

            GpioMode getMode() const
            {
                return GpioPortType::Moder::Bits::get(TVPin);
            }

            void setOutputType(GpioOutputType outputType)
            {
                GpioPortType::Otyper::Bits::set(TVPin, outputType);
            }

            GpioOutputType getOutputType() const
            {
                return GpioPortType::Otyper::Bits::get(TVPin);
            }

            void setOutputSpeed(GpioOutputSpeed outputSpeed)
            {
                GpioPortType::Ospeedr::Bits::set(TVPin, outputSpeed);
            }

            GpioOutputSpeed getOutputSpeed() const
            {
                return GpioPortType::Ospeedr::Bits::get(TVPin);
            }

            void setPupd(GpioPupd pupd)
            {
                GpioPortType::Pupdr::Bits::set(TVPin, pupd);
            }

            GpioPupd getPupd() const
            {
                return GpioPortType::Pupdr::Bits::get(TVPin);
            }

            void setAltFunc(Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPortType::k_port, TVPin>::AltFunc altFunc)
            {
                const auto genericAltFunc =
                        static_cast<Bitapi::Ahb1::Gpio::GpioAltFunc>(static_cast<unsigned int>(altFunc));
                if (static_cast<unsigned int>(TVPin) < 8)
                {
                    GpioPortType::Afrl::Bits::set(TVPin, genericAltFunc);
                }
                else
                {
                    const auto hpin = static_cast<GpioPin>(static_cast<unsigned int>(TVPin) - 8);
                    GpioPortType::Afrh::Bits::set(hpin, genericAltFunc);
                }
            }

            Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPortType::k_port, TVPin>::AltFunc getAltFunc() const
            {
                auto genericAltFunc = Bitapi::Ahb1::Gpio::GpioAltFunc::Af0;
                if (static_cast<unsigned int>(TVPin) < 8)
                {
                    genericAltFunc = GpioPortType::Afrl::Bits::get(TVPin);
                }
                else
                {
                    const auto hpin = static_cast<GpioPin>(static_cast<unsigned int>(TVPin) - 8);
                    genericAltFunc = GpioPortType::Afrh::Bits::get(hpin);
                }
                return static_cast<Bitapi::Ahb1::Gpio::GpioPinTraits<GpioPortType::k_port, TVPin>::AltFunc>(
                        static_cast<unsigned int>(genericAltFunc));
            }

            void writeOutput(Bitapi::Common::PinState state)
            {
                GpioPortType::Odr::set(TVPin, state);
            }

            Bitapi::Common::PinState readOutput() const
            {
                return GpioPortType::Odr::get(TVPin);
            }

            Bitapi::Common::PinState toggleOutput()
            {
                const Bitapi::Common::PinState v = readOutput();
                writeOutput((v == Bitapi::Common::PinState::High) ? Bitapi::Common::PinState::Low
                                                                  : Bitapi::Common::PinState::High);
                return readOutput();
            }

            Bitapi::Common::PinState readInput()
            {
                return GpioPortType::Idr::get(TVPin);
            }

            void configureInterrupt(
                    GpioInterruptMode mode, GpioPupd pupd, IrqPriority irqPriority, IrqHandler irqHandler)
            {
                constexpr auto line = extiLine();

                g_gpioIrqHandlers[std::to_underlying(line)] = std::move(irqHandler);

                // Set GPIO mode to input.
                setMode(GpioMode::Input);

                // Set pull-up/pull-down resistors.
                setPupd(pupd);

                // Configure the trigger of the interrupt.
                switch (mode)
                {
                case GpioInterruptMode::RisingEdge:
                    Bitapi::Apb2::Exti::Rtsr::Bits::set(line, Bitapi::Apb2::Exti::TrValue::TriggerEnabled);
                    Bitapi::Apb2::Exti::Ftsr::Bits::set(line, Bitapi::Apb2::Exti::TrValue::TriggerDisabled);
                    break;
                case GpioInterruptMode::FallingEdge:
                    Bitapi::Apb2::Exti::Rtsr::Bits::set(line, Bitapi::Apb2::Exti::TrValue::TriggerDisabled);
                    Bitapi::Apb2::Exti::Ftsr::Bits::set(line, Bitapi::Apb2::Exti::TrValue::TriggerEnabled);
                    break;
                case GpioInterruptMode::RisingAndFallingEdge:
                    Bitapi::Apb2::Exti::Rtsr::Bits::set(line, Bitapi::Apb2::Exti::TrValue::TriggerEnabled);
                    Bitapi::Apb2::Exti::Ftsr::Bits::set(line, Bitapi::Apb2::Exti::TrValue::TriggerEnabled);
                    break;
                }

                // Configure our GPIO port as the input for the EXTI line.
                SyscfgExticrBits::set(
                        static_cast<typename SyscfgExticrBits::WriteValue>(static_cast<int>(GpioPortType::k_port)));

                constexpr auto irqNumber = extiIrqNumber();

                // Set NVIC interrupt priority.
                Bitapi::Core::Nvic::Ipr::set(irqNumber, irqPriority);

                enableInterrupts();
            }

        private:
            // Get the EXTI line number for this GPIO pin.
            static constexpr Bitapi::Apb2::Exti::LineNumber extiLine()
            {
                static_assert(Bitapi::Apb2::Exti::k_lineCount >= Bitapi::Ahb1::Gpio::k_pinCount);
                return static_cast<Bitapi::Apb2::Exti::LineNumber>(static_cast<unsigned int>(TVPin));
            }

            // Get the NVIC IRQ number for the EXTI line.
            static constexpr Bitapi::Core::Nvic::IrqNumber extiIrqNumber()
            {
                static_assert(Bitapi::Apb2::Exti::k_lineCount >= Bitapi::Ahb1::Gpio::k_pinCount);
                const auto line = static_cast<unsigned int>(TVPin);
                if (line <= 4)
                {
                    return static_cast<Bitapi::Core::Nvic::IrqNumber>(
                            static_cast<unsigned int>(Bitapi::Core::Nvic::IrqNumber::Exti0) + line);
                }
                else if (line <= 9)
                {
                    return Bitapi::Core::Nvic::IrqNumber::Exti9_5;
                }
                else
                {
                    return Bitapi::Core::Nvic::IrqNumber::Exti15_10;
                }
            }

            static void enableInterrupts()
            {
                // Unmask the EXTI line (i.e. enable interrupts on it).
                constexpr auto line = extiLine();
                Bitapi::Apb2::Exti::Imr::Bits::set(line, Bitapi::Apb2::Exti::MrValue::NotMasked);

                // Enable NVIC interrupt for the EXTI line.
                constexpr auto irqNumber = extiIrqNumber();
                Bitapi::Core::Nvic::Iser::set(irqNumber, Bitapi::Core::Nvic::IserWriteValue::Enable);
            }

            static void disableInterrupts()
            {
                // Mask the EXTI line (i.e. disable interrupts on it).
                constexpr auto line = extiLine();
                Bitapi::Apb2::Exti::Imr::Bits::set(line, Bitapi::Apb2::Exti::MrValue::Masked);

                // Disable NVIC interrupt for the EXTI line.
                constexpr auto irqNumber = extiIrqNumber();
                Bitapi::Core::Nvic::Icer::set(irqNumber, Bitapi::Core::Nvic::IcerWriteValue::Disable);

                g_gpioIrqHandlers[std::to_underlying(line)] = nullptr;
            }
        };

        // GPIO driver
        template <GpioPort TVPort>
        class GpioX final
        {
        private:
            using GpioPortType = GpioPortTraits<TVPort>::Type;
            using ClockEnableBits = GpioPortTraits<TVPort>::ClockEnableBits;
            using PeripheralResetBits = GpioPortTraits<TVPort>::PeripheralResetBits;

        public:
            using Pin0 = GpioXPinY<TVPort, GpioPin::Pin0>;
            using Pin1 = GpioXPinY<TVPort, GpioPin::Pin1>;
            using Pin2 = GpioXPinY<TVPort, GpioPin::Pin2>;
            using Pin3 = GpioXPinY<TVPort, GpioPin::Pin3>;
            using Pin4 = GpioXPinY<TVPort, GpioPin::Pin4>;
            using Pin5 = GpioXPinY<TVPort, GpioPin::Pin5>;
            using Pin6 = GpioXPinY<TVPort, GpioPin::Pin6>;
            using Pin7 = GpioXPinY<TVPort, GpioPin::Pin7>;
            using Pin8 = GpioXPinY<TVPort, GpioPin::Pin8>;
            using Pin9 = GpioXPinY<TVPort, GpioPin::Pin9>;
            using Pin10 = GpioXPinY<TVPort, GpioPin::Pin10>;
            using Pin11 = GpioXPinY<TVPort, GpioPin::Pin11>;
            using Pin12 = GpioXPinY<TVPort, GpioPin::Pin12>;
            using Pin13 = GpioXPinY<TVPort, GpioPin::Pin13>;
            using Pin14 = GpioXPinY<TVPort, GpioPin::Pin14>;
            using Pin15 = GpioXPinY<TVPort, GpioPin::Pin15>;

            GpioX()
            {
                ClockEnableBits::set(Bitapi::Common::DiEn::Enabled);
            }

            ~GpioX()
            {
                reset();
                ClockEnableBits::set(Bitapi::Common::DiEn::Disabled);
            }

            void reset()
            {
                PeripheralResetBits::set(Bitapi::Common::ResetBit::Reset);
                PeripheralResetBits::set(Bitapi::Common::ResetBit::NoReset);
            }

            void setMode(GpioPin pin, GpioMode mode)
            {
                GpioPortType::Moder::set(pin, mode);
            }

            GpioMode getMode(GpioPin pin) const
            {
                return GpioPortType::Moder::get(pin);
            }

            void setOutputType(GpioPin pin, GpioOutputType outputType)
            {
                GpioPortType::Otyper::set(pin, outputType);
            }

            GpioOutputType getOutputType(GpioPin pin) const
            {
                return GpioPortType::Otyper::get(pin);
            }

            void setOutputSpeed(GpioPin pin, GpioOutputSpeed outputSpeed)
            {
                GpioPortType::Ospeedr::set(pin, outputSpeed);
            }

            GpioOutputSpeed getOutputSpeed(GpioPin pin) const
            {
                return GpioPortType::Ospeedr::get(pin);
            }

            void setPupd(GpioPin pin, GpioPupd pupd)
            {
                GpioPortType::Pupdr::set(pin, pupd);
            }

            GpioPupd getPupd(GpioPin pin) const
            {
                return GpioPortType::Pupdr::get(pin);
            }

            void setAltFunc(GpioPin pin, GpioAltFunc altFunc)
            {
                if (static_cast<unsigned int>(pin) < 8)
                {
                    GpioPortType::Afrl::Bits::set(pin, altFunc);
                }
                else
                {
                    const auto hpin = static_cast<GpioPin>(static_cast<unsigned int>(pin) - 8);
                    GpioPortType::Afrh::Bits::set(hpin, altFunc);
                }
            }

            GpioAltFunc getAltFunc(GpioPin pin) const
            {
                if (static_cast<unsigned int>(pin) < 8)
                {
                    return GpioPortType::Afrl::Bits::get(pin);
                }
                else
                {
                    const auto hpin = static_cast<GpioPin>(static_cast<unsigned int>(pin) - 8);
                    return GpioPortType::Afrh::Bits::get(hpin);
                }
            }

            void writeOutput(GpioPin pin, Bitapi::Common::PinState state)
            {
                GpioPortType::Odr::set(pin, state);
            }

            Bitapi::Common::PinState readOutput(GpioPin pin) const
            {
                return GpioPortType::Odr::get(pin);
            }

            Bitapi::Common::PinState toggleOutput(GpioPin pin)
            {
                const Bitapi::Common::PinState v = readOutput(pin);
                writeOutput(pin, (v == Bitapi::Common::PinState::High) ? Bitapi::Common::PinState::Low
                                                                       : Bitapi::Common::PinState::High);
                return readOutput(pin);
            }

            Bitapi::Common::PinState readInput(GpioPin pin)
            {
                return GpioPortType::Idr::get(pin);
            }

            Pin0& pin0()
            {
                return m_pin0;
            }

            Pin1& pin1()
            {
                return m_pin1;
            }

            Pin2& pin2()
            {
                return m_pin2;
            }

            Pin3& pin3()
            {
                return m_pin3;
            }

            Pin4& pin4()
            {
                return m_pin4;
            }

            Pin5& pin5()
            {
                return m_pin5;
            }

            Pin6& pin6()
            {
                return m_pin6;
            }

            Pin7& pin7()
            {
                return m_pin7;
            }

            Pin8& pin8()
            {
                return m_pin8;
            }

            Pin9& pin9()
            {
                return m_pin9;
            }

            Pin10& pin10()
            {
                return m_pin10;
            }

            Pin11& pin11()
            {
                return m_pin11;
            }

            Pin12& pin12()
            {
                return m_pin12;
            }

            Pin13& pin13()
            {
                return m_pin13;
            }

            Pin14& pin14()
            {
                return m_pin14;
            }

            Pin15& pin15()
            {
                return m_pin15;
            }

        private:
            [[no_unique_address]] Pin0 m_pin0;
            [[no_unique_address]] Pin1 m_pin1;
            [[no_unique_address]] Pin2 m_pin2;
            [[no_unique_address]] Pin3 m_pin3;
            [[no_unique_address]] Pin4 m_pin4;
            [[no_unique_address]] Pin5 m_pin5;
            [[no_unique_address]] Pin6 m_pin6;
            [[no_unique_address]] Pin7 m_pin7;
            [[no_unique_address]] Pin8 m_pin8;
            [[no_unique_address]] Pin9 m_pin9;
            [[no_unique_address]] Pin10 m_pin10;
            [[no_unique_address]] Pin11 m_pin11;
            [[no_unique_address]] Pin12 m_pin12;
            [[no_unique_address]] Pin13 m_pin13;
            [[no_unique_address]] Pin14 m_pin14;
            [[no_unique_address]] Pin15 m_pin15;
        };
    } // namespace detail

    using GpioA = detail::GpioX<GpioPort::PortA>;
    using GpioB = detail::GpioX<GpioPort::PortB>;
    using GpioC = detail::GpioX<GpioPort::PortC>;
    using GpioD = detail::GpioX<GpioPort::PortD>;
    using GpioE = detail::GpioX<GpioPort::PortE>;
    using GpioF = detail::GpioX<GpioPort::PortF>;
    using GpioG = detail::GpioX<GpioPort::PortG>;
    using GpioH = detail::GpioX<GpioPort::PortH>;
    using GpioI = detail::GpioX<GpioPort::PortI>;
    using GpioJ = detail::GpioX<GpioPort::PortJ>;
    using GpioK = detail::GpioX<GpioPort::PortK>;

} // namespace Stm32f407::Driver
