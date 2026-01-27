#pragma once

#include "Src/bitapi/stm32f407_utils.hpp"
#include "common.hpp"
#include "util.hpp"

#include "Src/bitapi/stm32f407_ahb1_rcc.hpp"
#include "Src/bitapi/stm32f407_apb1_spi.hpp"
#include "Src/bitapi/stm32f407_common_spi.hpp"
#include "Src/bitapi/stm32f407_core_nvic.hpp"

#include <array>
#include <span>
#include <type_traits>

namespace Stm32f407::Driver
{
    using SpiMode = Bitapi::Apb1::Spi::MstrValue;
    using SpiClockPolarity = Bitapi::Apb1::Spi::CpolValue;
    using SpiClockPhase = Bitapi::Apb1::Spi::CphaValue;
    using SpiDataFrameFormat = Bitapi::Apb1::Spi::DffValue;
    using SpiBaudRateDiv = Bitapi::Apb1::Spi::BrValue;

    enum class SpiBusMode
    {
        // 2-lines, one for tx, one for rx.
        FullDuplex,

        // 1-line, tx.
        // If master: MOSI line is used.
        // If slave: MISO line is used.
        HalfDuplexTx,

        // 1-line, rx.
        // If master: MOSI line is used.
        // If slave: MISO line is used.
        HalfDuplexRx,

        // 1-line, tx only.
        // Same as FullDuplex, but the rx line is ignored.
        // If master: MOSI line is used. MISO is free for general purpose IO.
        // If slave: MISO line is used. MOSI is free for general purpose IO.
        SimplexTxOnly,

        // 1-line, rx only.
        // If master: MISO line is used. MOSI is free for general purpose IO.
        // If slave: MOSI line is used. MISO is free for general purpose IO.
        SimplexRxOnly
    };

    namespace detail
    {
        extern std::array<IrqHandler, Bitapi::Common::Spi::k_spiCount> g_spiIrqHandlers;

        template <unsigned int TVSpiNumber>
        struct SpiTraits
        {
        };

        template <>
        struct SpiTraits<2>
        {
            static constexpr auto k_irqNum = Bitapi::Core::Nvic::IrqNumber::Spi2;
            using Type = Bitapi::Apb1::Spi::Spi2;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Apb1Enr::Spi2En;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Apb1Rstr::Spi2Rst;
        };

        template <>
        struct SpiTraits<3>
        {
            static constexpr auto k_irqNum = Bitapi::Core::Nvic::IrqNumber::Spi3;
            using Type = Bitapi::Apb1::Spi::Spi3;
            using ClockEnableBits = Bitapi::Ahb1::Rcc::Apb1Enr::Spi3En;
            using PeripheralResetBits = Bitapi::Ahb1::Rcc::Apb1Rstr::Spi3Rst;
        };

        template <unsigned int TVSpiNumber>
        class SpiX
        {
        private:
            using SpiType = SpiTraits<TVSpiNumber>::Type;
            using ClockEnableBits = SpiTraits<TVSpiNumber>::ClockEnableBits;
            using PeripheralResetBits = SpiTraits<TVSpiNumber>::PeripheralResetBits;

        public:
            explicit SpiX()
            {
                ClockEnableBits::set(Bitapi::Common::DiEn::Enabled);
            }

            ~SpiX()
            {
                reset();
                ClockEnableBits::set(Bitapi::Common::DiEn::Disabled);
            }

            void reset()
            {
                PeripheralResetBits::set(Bitapi::Common::ResetBit::Reset);
                PeripheralResetBits::set(Bitapi::Common::ResetBit::NoReset);
            }

            void setMode(SpiMode mode)
            {
                SpiType::Cr1::Mstr::set(mode);
            }

            SpiMode getMode() const
            {
                return SpiType::Cr1::Mstr::get();
            }

            void setBusMode(SpiBusMode mode)
            {
                switch (mode)
                {
                case SpiBusMode::FullDuplex:
                    SpiType::Cr1::BidiMode::set(Bitapi::Apb1::Spi::BidiModeValue::TwoLineUnidirectional);
                    SpiType::Cr1::RxOnly::set(Bitapi::Common::NoYes::No);
                    break;
                case SpiBusMode::HalfDuplexRx:
                    SpiType::Cr1::BidiMode::set(Bitapi::Apb1::Spi::BidiModeValue::OneLineBidirectional);
                    SpiType::Cr1::Bidioe::set(Bitapi::Common::DiEn::Disabled);
                    break;
                case SpiBusMode::HalfDuplexTx:
                    SpiType::Cr1::BidiMode::set(Bitapi::Apb1::Spi::BidiModeValue::OneLineBidirectional);
                    SpiType::Cr1::Bidioe::set(Bitapi::Common::DiEn::Enabled);
                    break;
                case SpiBusMode::SimplexTxOnly:
                    // Same as FullDuplex. The rx line is just ignored.
                    SpiType::Cr1::BidiMode::set(Bitapi::Apb1::Spi::BidiModeValue::TwoLineUnidirectional);
                    SpiType::Cr1::RxOnly::set(Bitapi::Common::NoYes::No);
                    break;
                case SpiBusMode::SimplexRxOnly:
                    SpiType::Cr1::BidiMode::set(Bitapi::Apb1::Spi::BidiModeValue::TwoLineUnidirectional);
                    SpiType::Cr1::RxOnly::set(Bitapi::Common::NoYes::Yes);
                    break;
                }
            }

            void setClockPolarity(SpiClockPolarity polarity)
            {
                SpiType::Cr1::Cpol::set(polarity);
            }

            SpiClockPolarity getClockPolarity() const
            {
                return SpiType::Cr1::Cpol::get();
            }

            void setClockPhase(SpiClockPhase phase)
            {
                SpiType::Cr1::Cpha::set(phase);
            }

            SpiClockPhase getClockPhase() const
            {
                return SpiType::Cr1::Cpha::get();
            }

            void setDataFrameFormat(SpiDataFrameFormat format)
            {
                SpiType::Cr1::Dff::set(format);
            }

            SpiDataFrameFormat getDataFrameFormat() const
            {
                return SpiType::Cr1::Dff::get();
            }

            void setBaudRateDiv(SpiBaudRateDiv divider)
            {
                SpiType::Cr1::Br::set(divider);
            }

            SpiBaudRateDiv getBaudRateDiv() const
            {
                return SpiType::Cr1::Br::get();
            }

            // Send data in blocking mode.
            template <typename TData>
                requires std::is_same_v<TData, Bitapi::Common::Byte> || std::is_same_v<TData, Bitapi::Common::HalfWord>
            void send(std::span<const TData> data)
            {
                for (const auto d : data)
                {
                    Util::busyWaitFor([]() { return SpiType::Sr::Txe::get() == Bitapi::Common::EmptyFlag::Empty; });
                    SpiType::Dr::set(static_cast<Bitapi::Common::HalfWord>(d));
                }
                Util::busyWaitFor([]() { return SpiType::Sr::Txe::get() == Bitapi::Common::EmptyFlag::Empty; });
            }

            // Receive data in blocking mode.
            template <typename TData>
                requires std::is_same_v<TData, Bitapi::Common::Byte> || std::is_same_v<TData, Bitapi::Common::HalfWord>
            void receive(std::span<TData> data)
            {
                for (const auto& d : data)
                {
                    Util::busyWaitFor(
                            []() { return SpiType::Sr::Rxne::get() == Bitapi::Common::NotEmptyFlag::NotEmpty; });
                    d = SpiType::Dr::get();
                }
            }

            void configureInterrupt(IrqPriority irqPriority, IrqHandler irqHandler)
            {
                // TODO
            }
        };
    } // namespace detail

    using Spi2 = detail::SpiX<2>;
    using Spi3 = detail::SpiX<3>;
} // namespace Stm32f407::Driver
