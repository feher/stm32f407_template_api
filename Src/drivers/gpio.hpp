#pragma once

#include <cassert>

#include "Src/bitapi/stm32f407_ahb1_gpio.hpp"
#include "Src/bitapi/stm32f407_ahb1_rcc.hpp"
#include "Src/bitapi/stm32f407_apb2_exti.hpp"
#include "Src/bitapi/stm32f407_utils.hpp"

namespace Driver
{
    using GpioPin = Ahb1::Gpio::GpioPin;
    using GpioMode = Ahb1::Gpio::GpioMode;
    using GpioOutputType = Ahb1::Gpio::GpioOutputType;
    using GpioOutputSpeed = Ahb1::Gpio::GpioOutputSpeed;
    using GpioPupd = Ahb1::Gpio::GpioPupd;
    using GpioAltFunc = Ahb1::Gpio::GpioAltFunc;

    enum class GpioInterruptMode : Word
    {
        RisingEdge,
        FallingEdge,
        RisingAndFallingEdge
    };

    template <typename TGpioPort, GpioPin TVPin>
    class GpioXPinY final
    {
    public:
        void setMode(GpioMode mode)
        {
            TGpioPort::Moder::set(TVPin, mode);
        }

        GpioMode getMode() const
        {
            return TGpioPort::Moder::get(TVPin);
        }

        void setOutputType(GpioOutputType outputType)
        {
            TGpioPort::Otyper::set(TVPin, outputType);
        }

        GpioOutputType getOutputType() const
        {
            return TGpioPort::Otyper::get(TVPin);
        }

        void setOutputSpeed(GpioOutputSpeed outputSpeed)
        {
            TGpioPort::Ospeedr::set(TVPin, outputSpeed);
        }

        GpioOutputSpeed getOutputSpeed() const
        {
            return TGpioPort::Ospeedr::get(TVPin);
        }

        void setPupd(GpioPupd pupd)
        {
            TGpioPort::Pupdr::set(TVPin, pupd);
        }

        GpioPupd getPupd() const
        {
            return TGpioPort::Pupdr::get(TVPin);
        }

        void setAltFunc(GpioAltFunc altFunc)
        {
            if (static_cast<int>(TVPin) < 16)
            {
                TGpioPort::Afrl::set(TVPin, altFunc);
            }
            else
            {
                TGpioPort::Afrh::set(TVPin, altFunc);
            }
        }

        GpioAltFunc getAltFunc() const
        {
            if (static_cast<int>(TVPin) < 16)
            {
                return TGpioPort::Afrl::get(TVPin);
            }
            else
            {
                return TGpioPort::Afrh::get(TVPin);
            }
        }

        void writeOutput(PinState state)
        {
            TGpioPort::Odr::set(TVPin, state);
        }

        PinState readOutput() const
        {
            return TGpioPort::Odr::get(TVPin);
        }

        PinState toggleOutput()
        {
            const PinState v = readOutput(TVPin);
            writeOutput(TVPin, (v == PinState::High) ? PinState::Low : PinState::High);
            return readOutput(TVPin);
        }

        PinState readInput()
        {
            return TGpioPort::Idr::get(TVPin);
        }

        void setupInterrupt(GpioInterruptMode mode)
        {
            if (mode == GpioInterruptMode::RisingEdge)
            {
                // TODO how to know which Tx to use?
                Apb2::Exti::Rtsr::Tr0::set(Apb2::Exti::TrValue::TriggerEnabled);
                Apb2::Exti::Ftsr::Tr0::set(Apb2::Exti::TrValue::TriggerDisabled);
            }
        }

    private:
        void configureExtiRtsr()
        {
            if constexpr (TVPin == GpioPin::Pin0)
            {
                ;
            }
        }
    };

    // GPIO driver
    template <typename TClockEnableBits, typename TPeripheralResetBits, typename TGpioPort>
    class GpioX final
    {
    public:
        using Pin0 = GpioXPinY<TGpioPort, GpioPin::Pin0>;
        using Pin1 = GpioXPinY<TGpioPort, GpioPin::Pin1>;
        using Pin2 = GpioXPinY<TGpioPort, GpioPin::Pin2>;
        using Pin3 = GpioXPinY<TGpioPort, GpioPin::Pin3>;
        using Pin4 = GpioXPinY<TGpioPort, GpioPin::Pin4>;
        using Pin5 = GpioXPinY<TGpioPort, GpioPin::Pin5>;
        using Pin6 = GpioXPinY<TGpioPort, GpioPin::Pin6>;
        using Pin7 = GpioXPinY<TGpioPort, GpioPin::Pin7>;
        using Pin8 = GpioXPinY<TGpioPort, GpioPin::Pin8>;
        using Pin9 = GpioXPinY<TGpioPort, GpioPin::Pin9>;
        using Pin10 = GpioXPinY<TGpioPort, GpioPin::Pin10>;
        using Pin11 = GpioXPinY<TGpioPort, GpioPin::Pin11>;
        using Pin12 = GpioXPinY<TGpioPort, GpioPin::Pin12>;
        using Pin13 = GpioXPinY<TGpioPort, GpioPin::Pin13>;
        using Pin14 = GpioXPinY<TGpioPort, GpioPin::Pin14>;
        using Pin15 = GpioXPinY<TGpioPort, GpioPin::Pin15>;

        GpioX()
        {
            TClockEnableBits::set(EnDi::Enabled);
        }

        ~GpioX()
        {
            reset();
            TClockEnableBits::set(EnDi::Disabled);
        }

        void reset()
        {
            TPeripheralResetBits::set(ResetBit::Reset);
            TPeripheralResetBits::set(ResetBit::NoReset);
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

        void writeOutput(GpioPin pin, PinState state)
        {
            TGpioPort::Odr::set(pin, state);
        }

        PinState readOutput(GpioPin pin) const
        {
            return TGpioPort::Odr::get(pin);
        }

        PinState toggleOutput(GpioPin pin)
        {
            const PinState v = readOutput(pin);
            writeOutput(pin, (v == PinState::High) ? PinState::Low : PinState::High);
            return readOutput(pin);
        }

        PinState readInput(GpioPin pin)
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

    using GpioA = GpioX<Ahb1::Rcc::Ahb1Enr::GpioAEn, Ahb1::Rcc::Ahb1Rstr::GpioARst, Ahb1::Gpio::GpioA>;
    using GpioB = GpioX<Ahb1::Rcc::Ahb1Enr::GpioBEn, Ahb1::Rcc::Ahb1Rstr::GpioBRst, Ahb1::Gpio::GpioB>;
    using GpioC = GpioX<Ahb1::Rcc::Ahb1Enr::GpioCEn, Ahb1::Rcc::Ahb1Rstr::GpioCRst, Ahb1::Gpio::GpioC>;
    using GpioD = GpioX<Ahb1::Rcc::Ahb1Enr::GpioDEn, Ahb1::Rcc::Ahb1Rstr::GpioDRst, Ahb1::Gpio::GpioD>;
    using GpioE = GpioX<Ahb1::Rcc::Ahb1Enr::GpioEEn, Ahb1::Rcc::Ahb1Rstr::GpioERst, Ahb1::Gpio::GpioE>;
    using GpioF = GpioX<Ahb1::Rcc::Ahb1Enr::GpioFEn, Ahb1::Rcc::Ahb1Rstr::GpioFRst, Ahb1::Gpio::GpioF>;
    using GpioG = GpioX<Ahb1::Rcc::Ahb1Enr::GpioGEn, Ahb1::Rcc::Ahb1Rstr::GpioGRst, Ahb1::Gpio::GpioG>;
    using GpioH = GpioX<Ahb1::Rcc::Ahb1Enr::GpioHEn, Ahb1::Rcc::Ahb1Rstr::GpioHRst, Ahb1::Gpio::GpioH>;
    using GpioI = GpioX<Ahb1::Rcc::Ahb1Enr::GpioIEn, Ahb1::Rcc::Ahb1Rstr::GpioIRst, Ahb1::Gpio::GpioI>;
    using GpioJ = GpioX<Ahb1::Rcc::Ahb1Enr::GpioJEn, Ahb1::Rcc::Ahb1Rstr::GpioJRst, Ahb1::Gpio::GpioJ>;
    using GpioK = GpioX<Ahb1::Rcc::Ahb1Enr::GpioKEn, Ahb1::Rcc::Ahb1Rstr::GpioKRst, Ahb1::Gpio::GpioK>;

} // namespace Driver
