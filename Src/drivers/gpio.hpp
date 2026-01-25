#pragma once

#include "Src/bitapi/stm32f407_ahb1_gpio.hpp"
#include "Src/bitapi/stm32f407_ahb1_rcc.hpp"
#include "Src/bitapi/stm32f407_apb2_exti.hpp"
#include "Src/bitapi/stm32f407_apb2_syscfg.hpp"
#include "Src/bitapi/stm32f407_core_nvic.hpp"
#include "Src/bitapi/stm32f407_utils.hpp"

#include <array>
#include <functional>
#include <utility>

namespace Stm32f407::Driver
{
    using GpioPin = Bitapi::Ahb1::Gpio::GpioPin;
    using GpioMode = Bitapi::Ahb1::Gpio::GpioMode;
    using GpioOutputType = Bitapi::Ahb1::Gpio::GpioOutputType;
    using GpioOutputSpeed = Bitapi::Ahb1::Gpio::GpioOutputSpeed;
    using GpioPupd = Bitapi::Ahb1::Gpio::GpioPupd;
    using GpioAltFunc = Bitapi::Ahb1::Gpio::GpioAltFunc;
    using GpioIrqHandler = std::function<void()>;

    using IrqPriority = Bitapi::Core::Nvic::IprValue;

    enum class GpioInterruptMode : Bitapi::Common::Word
    {
        RisingEdge,
        FallingEdge,
        RisingAndFallingEdge
    };

    namespace detail
    {
        extern std::array<GpioIrqHandler, Bitapi::Apb2::Exti::k_lineCount> g_gpioIrqHandlers;

        template <typename TGpioPort, GpioPin TVPin, typename TSyscfgExticrBits>
        class GpioXPinY final
        {
        public:
            void setMode(GpioMode mode)
            {
                TGpioPort::Moder::Bits::set(TVPin, mode);
            }

            GpioMode getMode() const
            {
                return TGpioPort::Moder::Bits::get(TVPin);
            }

            void setOutputType(GpioOutputType outputType)
            {
                TGpioPort::Otyper::Bits::set(TVPin, outputType);
            }

            GpioOutputType getOutputType() const
            {
                return TGpioPort::Otyper::Bits::get(TVPin);
            }

            void setOutputSpeed(GpioOutputSpeed outputSpeed)
            {
                TGpioPort::Ospeedr::Bits::set(TVPin, outputSpeed);
            }

            GpioOutputSpeed getOutputSpeed() const
            {
                return TGpioPort::Ospeedr::Bits::get(TVPin);
            }

            void setPupd(GpioPupd pupd)
            {
                TGpioPort::Pupdr::Bits::set(TVPin, pupd);
            }

            GpioPupd getPupd() const
            {
                return TGpioPort::Pupdr::Bits::get(TVPin);
            }

            void setAltFunc(GpioAltFunc altFunc)
            {
                if (static_cast<int>(TVPin) < 16)
                {
                    TGpioPort::Afrl::Bits::set(TVPin, altFunc);
                }
                else
                {
                    TGpioPort::Afrh::Bits::set(TVPin, altFunc);
                }
            }

            GpioAltFunc getAltFunc() const
            {
                if (static_cast<int>(TVPin) < 16)
                {
                    return TGpioPort::Afrl::Bits::get(TVPin);
                }
                else
                {
                    return TGpioPort::Afrh::Bits::get(TVPin);
                }
            }

            void writeOutput(Bitapi::Common::PinState state)
            {
                TGpioPort::Odr::set(TVPin, state);
            }

            Bitapi::Common::PinState readOutput() const
            {
                return TGpioPort::Odr::get(TVPin);
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
                return TGpioPort::Idr::get(TVPin);
            }

            void configureInterrupt(
                    GpioInterruptMode mode, GpioPupd pupd, IrqPriority irqPriority, GpioIrqHandler irqHandler)
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
                TSyscfgExticrBits::set(
                        static_cast<typename TSyscfgExticrBits::WriteValue>(static_cast<int>(TGpioPort::k_portIndex)));

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
        template <typename TClockEnableBits, typename TPeripheralResetBits, typename TGpioPort>
        class GpioX final
        {
        public:
            using Pin0 = GpioXPinY<TGpioPort, GpioPin::Pin0, Bitapi::Apb2::Syscfg::Exticr1::Exit0>;
            using Pin1 = GpioXPinY<TGpioPort, GpioPin::Pin1, Bitapi::Apb2::Syscfg::Exticr1::Exit1>;
            using Pin2 = GpioXPinY<TGpioPort, GpioPin::Pin2, Bitapi::Apb2::Syscfg::Exticr1::Exit2>;
            using Pin3 = GpioXPinY<TGpioPort, GpioPin::Pin3, Bitapi::Apb2::Syscfg::Exticr1::Exit3>;
            using Pin4 = GpioXPinY<TGpioPort, GpioPin::Pin4, Bitapi::Apb2::Syscfg::Exticr2::Exit4>;
            using Pin5 = GpioXPinY<TGpioPort, GpioPin::Pin5, Bitapi::Apb2::Syscfg::Exticr2::Exit5>;
            using Pin6 = GpioXPinY<TGpioPort, GpioPin::Pin6, Bitapi::Apb2::Syscfg::Exticr2::Exit6>;
            using Pin7 = GpioXPinY<TGpioPort, GpioPin::Pin7, Bitapi::Apb2::Syscfg::Exticr2::Exit7>;
            using Pin8 = GpioXPinY<TGpioPort, GpioPin::Pin8, Bitapi::Apb2::Syscfg::Exticr3::Exit8>;
            using Pin9 = GpioXPinY<TGpioPort, GpioPin::Pin9, Bitapi::Apb2::Syscfg::Exticr3::Exit9>;
            using Pin10 = GpioXPinY<TGpioPort, GpioPin::Pin10, Bitapi::Apb2::Syscfg::Exticr3::Exit10>;
            using Pin11 = GpioXPinY<TGpioPort, GpioPin::Pin11, Bitapi::Apb2::Syscfg::Exticr3::Exit11>;
            using Pin12 = GpioXPinY<TGpioPort, GpioPin::Pin12, Bitapi::Apb2::Syscfg::Exticr4::Exit12>;
            using Pin13 = GpioXPinY<TGpioPort, GpioPin::Pin13, Bitapi::Apb2::Syscfg::Exticr4::Exit13>;
            using Pin14 = GpioXPinY<TGpioPort, GpioPin::Pin14, Bitapi::Apb2::Syscfg::Exticr4::Exit14>;
            using Pin15 = GpioXPinY<TGpioPort, GpioPin::Pin15, Bitapi::Apb2::Syscfg::Exticr4::Exit15>;

            GpioX()
            {
                TClockEnableBits::set(Bitapi::Common::DiEn::Enabled);
            }

            ~GpioX()
            {
                reset();
                TClockEnableBits::set(Bitapi::Common::DiEn::Disabled);
            }

            void reset()
            {
                TPeripheralResetBits::set(Bitapi::Common::ResetBit::Reset);
                TPeripheralResetBits::set(Bitapi::Common::ResetBit::NoReset);
            }

            void setMode(GpioPin pin, GpioMode mode)
            {
                TGpioPort::Moder::set(pin, mode);
            }

            GpioMode getMode(GpioPin pin) const
            {
                return TGpioPort::Moder::get(pin);
            }

            void setOutputType(GpioPin pin, GpioOutputType outputType)
            {
                TGpioPort::Otyper::set(pin, outputType);
            }

            GpioOutputType getOutputType(GpioPin pin) const
            {
                return TGpioPort::Otyper::get(pin);
            }

            void setOutputSpeed(GpioPin pin, GpioOutputSpeed outputSpeed)
            {
                TGpioPort::Ospeedr::set(pin, outputSpeed);
            }

            GpioOutputSpeed getOutputSpeed(GpioPin pin) const
            {
                return TGpioPort::Ospeedr::get(pin);
            }

            void setPupd(GpioPin pin, GpioPupd pupd)
            {
                TGpioPort::Pupdr::set(pin, pupd);
            }

            GpioPupd getPupd(GpioPin pin) const
            {
                return TGpioPort::Pupdr::get(pin);
            }

            void setAltFunc(GpioPin pin, GpioAltFunc altFunc)
            {
                if (static_cast<int>(pin) < 16)
                {
                    TGpioPort::Afrl::set(pin, altFunc);
                }
                else
                {
                    TGpioPort::Afrh::set(pin, altFunc);
                }
            }

            GpioAltFunc getAltFunc(GpioPin pin) const
            {
                if (static_cast<int>(pin) < 16)
                {
                    return TGpioPort::Afrl::get(pin);
                }
                else
                {
                    return TGpioPort::Afrh::get(pin);
                }
            }

            void writeOutput(GpioPin pin, Bitapi::Common::PinState state)
            {
                TGpioPort::Odr::set(pin, state);
            }

            Bitapi::Common::PinState readOutput(GpioPin pin) const
            {
                return TGpioPort::Odr::get(pin);
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
                return TGpioPort::Idr::get(pin);
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

    using GpioA = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioAEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioARst,
            Bitapi::Ahb1::Gpio::GpioA>;
    using GpioB = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioBEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioBRst,
            Bitapi::Ahb1::Gpio::GpioB>;
    using GpioC = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioCEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioCRst,
            Bitapi::Ahb1::Gpio::GpioC>;
    using GpioD = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioDEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioDRst,
            Bitapi::Ahb1::Gpio::GpioD>;
    using GpioE = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioEEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioERst,
            Bitapi::Ahb1::Gpio::GpioE>;
    using GpioF = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioFEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioFRst,
            Bitapi::Ahb1::Gpio::GpioF>;
    using GpioG = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioGEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioGRst,
            Bitapi::Ahb1::Gpio::GpioG>;
    using GpioH = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioHEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioHRst,
            Bitapi::Ahb1::Gpio::GpioH>;
    using GpioI = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioIEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioIRst,
            Bitapi::Ahb1::Gpio::GpioI>;
    using GpioJ = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioJEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioJRst,
            Bitapi::Ahb1::Gpio::GpioJ>;
    using GpioK = detail::GpioX<Bitapi::Ahb1::Rcc::Ahb1Enr::GpioKEn, Bitapi::Ahb1::Rcc::Ahb1Rstr::GpioKRst,
            Bitapi::Ahb1::Gpio::GpioK>;

} // namespace Stm32f407::Driver
