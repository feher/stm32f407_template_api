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

        template <unsigned int TVIndex, typename TClockEnableBits, typename TPeripheralResetBits, typename TTimer,
                Bitapi::Core::Nvic::IrqNumber TVIrqNum>
        class TimerX final
        {
        public:
            using ValueType = typename TTimer::ValueType;

            TimerX()
            {
                TClockEnableBits::set(Bitapi::Common::DiEn::Enabled);
                reset();
            }

            ~TimerX()
            {
                reset();
                TClockEnableBits::set(Bitapi::Common::DiEn::Disabled);
            }

            void reset()
            {
                TPeripheralResetBits::set(Bitapi::Common::ResetBit::Reset);
                TPeripheralResetBits::set(Bitapi::Common::ResetBit::NoReset);
            }

            void setDirection(TimerDirection direction)
            {
                TTimer::Cr1::Dir::set(direction);
            }

            TimerDirection getDirection() const
            {
                return TTimer::Cr1::Dir::get();
            }

            void setOneShot(bool oneShot)
            {
                TTimer::Cr1::Opm::set(oneShot ? Bitapi::Apb1::Tim2_5::OpmValue::CounterStopped
                                              : Bitapi::Apb1::Tim2_5::OpmValue::CounterNotStopped);
            }

            bool isOneShot() const
            {
                return TTimer::Cr1::Opm::get() == Bitapi::Apb1::Tim2_5::OpmValue::CounterStopped;
            }

            // Sets the upper limit for the counter of the timer.
            // The timer fires when the counter reaches this limit.
            void setCounterLimit(ValueType period)
            {
                TTimer::Arr::set(period);
            }

            ValueType getCounterLimit() const
            {
                return TTimer::Arr::get();
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
                const auto counterTicks = TTimer::Arr::get();
                return counterTicks / ticksPerMs;
            }

            // Divides the counter clock frequency by (prescaler + 1).
            // Essentially, slows down the timer.
            void setPrescaler(Bitapi::Common::HalfWord prescaler)
            {
                TTimer::Psc::set(prescaler);
            }

            Bitapi::Common::HalfWord getPrescaler() const
            {
                return TTimer::Psc::get();
            }

            // Manually set the timer's counter value.
            void setCounter(typename TTimer::ValueType value)
            {
                TTimer::Cnt::set(value);
            }

            // Get the timer's current counter value.
            typename TTimer::ValueType getCounter() const
            {
                return TTimer::Cnt::get();
            }

            // Start the timer.
            void start()
            {
                TTimer::Cr1::Cen::set(Bitapi::Common::DiEn::Enabled);
            }

            // Stop the timer.
            void stop()
            {
                TTimer::Cr1::Cen::set(Bitapi::Common::DiEn::Disabled);
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
                g_timerIrqHandlers[TVIndex] = std::move(irqHandler);

                // Enable NVIC interrupt for this timer.
                Bitapi::Core::Nvic::Iser::set(TVIrqNum, Bitapi::Core::Nvic::IserWriteValue::Enable);

                // Enable update interrupt.
                TTimer::Dier::Uie::set(Bitapi::Common::DiEn::Enabled);
            }

            void disableInterrupt()
            {
                // Disable update interrupt to avoid spurious interrupts.
                TTimer::Dier::Uie::set(Bitapi::Common::DiEn::Disabled);

                // Disable NVIC interrupt for this timer.
                Bitapi::Core::Nvic::Icer::set(TVIrqNum, Bitapi::Core::Nvic::IcerWriteValue::Disable);

                g_timerIrqHandlers[TVIndex] = nullptr;
            }

        private:
            static constexpr unsigned int getTicksPerMs()
            {
                constexpr auto clockHz = (2 <= (TVIndex + 1) && (TVIndex + 1) <= 5)
                                                 ? Stm32f407::Bitapi::Clocks::k_apb1Hz
                                                 : Stm32f407::Bitapi::Clocks::k_apb2Hz;
                constexpr auto tickPerMs = clockHz / 1000;
                return tickPerMs;
            }
        };
    } // namespace detail

    using Tim2 = detail::TimerX<1, Bitapi::Ahb1::Rcc::Apb1Enr::Tim2En, Bitapi::Ahb1::Rcc::Apb1Rstr::Tim2Rst,
            Bitapi::Apb1::Tim2_5::Tim2, Bitapi::Core::Nvic::IrqNumber::Tim2>;
    using Tim3 = detail::TimerX<2, Bitapi::Ahb1::Rcc::Apb1Enr::Tim3En, Bitapi::Ahb1::Rcc::Apb1Rstr::Tim3Rst,
            Bitapi::Apb1::Tim2_5::Tim3, Bitapi::Core::Nvic::IrqNumber::Tim3>;
    using Tim4 = detail::TimerX<3, Bitapi::Ahb1::Rcc::Apb1Enr::Tim4En, Bitapi::Ahb1::Rcc::Apb1Rstr::Tim4Rst,
            Bitapi::Apb1::Tim2_5::Tim4, Bitapi::Core::Nvic::IrqNumber::Tim4>;
    using Tim5 = detail::TimerX<4, Bitapi::Ahb1::Rcc::Apb1Enr::Tim5En, Bitapi::Ahb1::Rcc::Apb1Rstr::Tim5Rst,
            Bitapi::Apb1::Tim2_5::Tim5, Bitapi::Core::Nvic::IrqNumber::Tim5>;

} // namespace Stm32f407::Driver
