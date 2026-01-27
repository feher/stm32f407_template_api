#pragma once

#include "Src/bitapi/stm32f407_ahb1_rcc.hpp"
#include "Src/bitapi/stm32f407_apb1_tim2_5.hpp"
#include "Src/bitapi/stm32f407_clocks.hpp"
#include "Src/bitapi/stm32f407_core_nvic.hpp"
#include "Src/bitapi/stm32f407_utils.hpp"

#include <functional>

namespace Stm32f407::Driver
{
    using TimerDirection = Bitapi::Apb1::Tim2_5::DirValue;
    using TimerIrqHandler = std::function<void()>;

    namespace detail
    {
        extern std::array<TimerIrqHandler, 5> g_timerIrqHandlers;

        template <unsigned int TVTimerNumber>
        struct TimerTraits
        {
        };

        template <>
        struct TimerTraits<2>
        {
            static constexpr auto k_irqNum = Bitapi::Core::Nvic::IrqNumber::Tim2;
            using Type = Bitapi::Apb1::Tim2_5::Tim2;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Apb1Enr::Tim2En;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Apb1Rstr::Tim2Rst;
        };

        template <>
        struct TimerTraits<3>
        {
            static constexpr auto k_irqNum = Bitapi::Core::Nvic::IrqNumber::Tim3;
            using Type = Bitapi::Apb1::Tim2_5::Tim3;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Apb1Enr::Tim3En;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Apb1Rstr::Tim3Rst;
        };

        template <>
        struct TimerTraits<4>
        {
            static constexpr auto k_irqNum = Bitapi::Core::Nvic::IrqNumber::Tim4;
            using Type = Bitapi::Apb1::Tim2_5::Tim4;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Apb1Enr::Tim4En;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Apb1Rstr::Tim4Rst;
        };

        template <>
        struct TimerTraits<5>
        {
            static constexpr auto k_irqNum = Bitapi::Core::Nvic::IrqNumber::Tim5;
            using Type = Bitapi::Apb1::Tim2_5::Tim5;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Apb1Enr::Tim5En;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Apb1Rstr::Tim5Rst;
        };

        template <unsigned int TVTimerNumber>
        class TimerX final
        {
        private:
            using TimerType = TimerTraits<TVTimerNumber>::Type;
            using ClockEnableBits = TimerTraits<TVTimerNumber>::ClockEnableBits;
            using PeripheralResetBits = TimerTraits<TVTimerNumber>::PeripheralResetBits;

        public:
            using ValueType = typename TimerType::ValueType;

            TimerX()
            {
                ClockEnableBits::set(Bitapi::Common::DiEn::Enabled);
                reset();
            }

            ~TimerX()
            {
                reset();
                ClockEnableBits::set(Bitapi::Common::DiEn::Disabled);
            }

            void reset()
            {
                PeripheralResetBits::set(Bitapi::Common::ResetBit::Reset);
                PeripheralResetBits::set(Bitapi::Common::ResetBit::NoReset);
            }

            void setDirection(TimerDirection direction)
            {
                TimerType::Cr1::Dir::set(direction);
            }

            TimerDirection getDirection() const
            {
                return TimerType::Cr1::Dir::get();
            }

            void setOneShot(bool oneShot)
            {
                TimerType::Cr1::Opm::set(oneShot ? Bitapi::Apb1::Tim2_5::OpmValue::CounterStopped
                                                 : Bitapi::Apb1::Tim2_5::OpmValue::CounterNotStopped);
            }

            bool isOneShot() const
            {
                return TimerType::Cr1::Opm::get() == Bitapi::Apb1::Tim2_5::OpmValue::CounterStopped;
            }

            // Sets the upper limit for the counter of the timer.
            // The timer fires when the counter reaches this limit.
            void setCounterLimit(ValueType period)
            {
                TimerType::Arr::set(period);
            }

            ValueType getCounterLimit() const
            {
                return TimerType::Arr::get();
            }

            // Sets the timer period in milliseconds.
            // This eventually calls setCounterLimit() with a value calculated from milliSeconds.
            void setPeriod(unsigned int milliSeconds)
            {
                constexpr auto ticksPerMs = getTicksPerMs();
                unsigned int counterTicks = milliSeconds * ticksPerMs;
                setCounterLimit(counterTicks);
            }

            // Gets the timer period in milliseconds.
            unsigned int getPeriod() const
            {
                constexpr auto ticksPerMs = getTicksPerMs();
                const auto counterTicks = TimerType::Arr::get();
                return counterTicks / ticksPerMs;
            }

            // Divides the counter clock frequency by (prescaler + 1).
            // Essentially, slows down the timer.
            void setPrescaler(Bitapi::Common::HalfWord prescaler)
            {
                TimerType::Psc::set(prescaler);
            }

            Bitapi::Common::HalfWord getPrescaler() const
            {
                return TimerType::Psc::get();
            }

            // Manually set the timer's counter value.
            void setCounter(typename TimerType::ValueType value)
            {
                TimerType::Cnt::set(value);
            }

            // Get the timer's current counter value.
            typename TimerType::ValueType getCounter() const
            {
                return TimerType::Cnt::get();
            }

            // Start the timer.
            void start()
            {
                TimerType::Cr1::Cen::set(Bitapi::Common::DiEn::Enabled);
            }

            // Stop the timer.
            void stop()
            {
                TimerType::Cr1::Cen::set(Bitapi::Common::DiEn::Disabled);
            }

            // Restart the timer.
            // Also resets the counter value.
            void restart()
            {
                stop();
                if (getDirection() == TimerDirection::Downcounter)
                {
                    setCounter(getPeriod());
                }
                else
                {
                    setCounter(0);
                }
                start();
            }

            void enableInterrupt(TimerIrqHandler irqHandler)
            {
                g_timerIrqHandlers[TVTimerNumber - 1] = std::move(irqHandler);

                // Enable NVIC interrupt for this timer.
                constexpr auto irqNum = TimerTraits<TVTimerNumber>::k_irqNum;
                Bitapi::Core::Nvic::Iser::set(irqNum, Bitapi::Core::Nvic::IserWriteValue::Enable);

                // Enable update interrupt.
                TimerType::Dier::Uie::set(Bitapi::Common::DiEn::Enabled);
            }

            void disableInterrupt()
            {
                // Disable update interrupt to avoid spurious interrupts.
                TimerType::Dier::Uie::set(Bitapi::Common::DiEn::Disabled);

                // Disable NVIC interrupt for this timer.
                constexpr auto irqNum = TimerTraits<TVTimerNumber>::k_irqNum;
                Bitapi::Core::Nvic::Icer::set(irqNum, Bitapi::Core::Nvic::IcerWriteValue::Disable);

                g_timerIrqHandlers[TVTimerNumber - 1] = nullptr;
            }

        private:
            static constexpr unsigned int getTicksPerMs()
            {
                constexpr auto clockHz = (2 <= TVTimerNumber && TVTimerNumber <= 5) ? Bitapi::Clocks::k_apb1Hz
                                                                                    : Bitapi::Clocks::k_apb2Hz;
                constexpr auto tickPerMs = clockHz / 1000;
                return tickPerMs;
            }
        };
    } // namespace detail

    using Tim2 = detail::TimerX<2>;
    using Tim3 = detail::TimerX<3>;
    using Tim4 = detail::TimerX<4>;
    using Tim5 = detail::TimerX<5>;

} // namespace Stm32f407::Driver
