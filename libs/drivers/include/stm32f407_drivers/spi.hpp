#pragma once

#include "common.hpp"
#include "util.hpp"

#include <stm32f407_bitapi/stm32f407_ahb1_rcc.hpp>
#include <stm32f407_bitapi/stm32f407_apb1_spi.hpp>
#include <stm32f407_bitapi/stm32f407_common_spi.hpp>
#include <stm32f407_bitapi/stm32f407_core_nvic.hpp>
#include <stm32f407_bitapi/stm32f407_utils.hpp>

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
                reset();

                // Disable software slave management by default.
                // We want the NSS line to be active and managed by the SPI peripheral itself.
                SpiType::Cr1::Ssm::set(Bitapi::Common::DiEn::Disabled);
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

            void setEnabled(bool isEnabled)
            {
                SpiType::Cr1::Spe::set(isEnabled ? Bitapi::Common::DiEn::Enabled : Bitapi::Common::DiEn::Disabled);
            }

            bool isEnabled() const
            {
                return SpiType::Cr1::Spe::get() == Bitapi::Common::DiEn::Enabled;
            }

            void setMode(SpiMode mode)
            {
                if (isEnabled())
                {
                    return;
                }
                SpiType::Cr1::Mstr::set(mode);
                if (mode == SpiMode::Master)
                {
                    // Enable the NSS output. The NSS line will be managed by the hardware.
                    // The NSS signal is driven low when the master starts the communication and is kept
                    // low until the SPI is disabled.
                    SpiType::Cr2::Ssoe::set(Bitapi::Common::DiEn::Enabled);
                }
                else
                {
                    // The NSS pin acts as a classical NSS input: the
                    // slave is selected when NSS is low and deselected when NSS high.
                    SpiType::Cr2::Ssoe::set(Bitapi::Common::DiEn::Disabled);
                }
            }

            SpiMode getMode() const
            {
                return SpiType::Cr1::Mstr::get();
            }

            void setBusMode(SpiBusMode mode)
            {
                if (isEnabled())
                {
                    return;
                }
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
                if (isEnabled())
                {
                    return;
                }
                SpiType::Cr1::Cpol::set(polarity);
            }

            SpiClockPolarity getClockPolarity() const
            {
                return SpiType::Cr1::Cpol::get();
            }

            void setClockPhase(SpiClockPhase phase)
            {
                if (isEnabled())
                {
                    return;
                }
                SpiType::Cr1::Cpha::set(phase);
            }

            SpiClockPhase getClockPhase() const
            {
                return SpiType::Cr1::Cpha::get();
            }

            void setDataFrameFormat(SpiDataFrameFormat format)
            {
                if (isEnabled())
                {
                    return;
                }
                SpiType::Cr1::Dff::set(format);
            }

            SpiDataFrameFormat getDataFrameFormat() const
            {
                return SpiType::Cr1::Dff::get();
            }

            void setBaudRateDiv(SpiBaudRateDiv divider)
            {
                if (isEnabled())
                {
                    return;
                }
                SpiType::Cr1::Br::set(divider);
            }

            SpiBaudRateDiv getBaudRateDiv() const
            {
                return SpiType::Cr1::Br::get();
            }

            // Send data in blocking mode.
            template <typename TData>
                requires std::is_same_v<TData, Bitapi::Common::Byte> || std::is_same_v<TData, Bitapi::Common::HalfWord>
            void sendToSlave(std::span<const TData> data)
            {
                //setEnabled(true);

                for (const auto d : data)
                {
                    // Send one data frame to the slave.
                    sendOneToSlave(d);

                    // Receive one data frame from the slave.
                    // We don't use this data, we just want to empty our Rx buffer.
                    receiveOneFromSlave<TData>();
                }

                Util::busyWaitFor([]() { return SpiType::Sr::Bsy::get() == Bitapi::Common::NoYes::No; });
                //setEnabled(false);
            }

            // Receive data in blocking mode.
            template <typename TData>
                requires std::is_same_v<TData, Bitapi::Common::Byte> || std::is_same_v<TData, Bitapi::Common::HalfWord>
            void receiveFromSlave(std::span<TData> data)
            {
                //setEnabled(true);

                // Empty our current Rx buffer. It may contain some stale data.
                while (SpiType::Sr::Rxne::get() == Bitapi::Common::NotEmptyFlag::NotEmpty)
                {
                    SpiType::Dr::get();
                }

                // Start our fresh receive sequence.
                for (auto& d : data)
                {
                    // Send a dummy data frame. This is needed to trigger the slave to send the data from its Tx buffer.
                    sendOneToSlave(TData{});

                    // Read the received data frame from our Rx buffer.
                    d = receiveOneFromSlave<TData>();
                }

                Util::busyWaitFor([]() { return SpiType::Sr::Bsy::get() == Bitapi::Common::NoYes::No; });
                //setEnabled(false);
            }

            void configureInterrupt(IrqPriority irqPriority, IrqHandler irqHandler)
            {
                // TODO
            }

        private:
            template <typename TData>
                requires std::is_same_v<TData, Bitapi::Common::Byte> || std::is_same_v<TData, Bitapi::Common::HalfWord>
            void sendOneToSlave(TData data)
            {
                Util::busyWaitFor([]() { return SpiType::Sr::Txe::get() == Bitapi::Common::EmptyFlag::Empty; });
                SpiType::Dr::set(Bitapi::Common::HalfWord{data});
            }

            template <typename TData>
                requires std::is_same_v<TData, Bitapi::Common::Byte> || std::is_same_v<TData, Bitapi::Common::HalfWord>
            TData receiveOneFromSlave()
            {
                Util::busyWaitFor([]() { return SpiType::Sr::Rxne::get() == Bitapi::Common::NotEmptyFlag::NotEmpty; });
                return SpiType::Dr::get();
            }
        };
    } // namespace detail

    using Spi2 = detail::SpiX<2>;
    using Spi3 = detail::SpiX<3>;
} // namespace Stm32f407::Driver
