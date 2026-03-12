#pragma once

#include "stm32f407_apb1.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Bitapi::Apb1::Spi
{
    enum class CphaValue : Common::Word
    {
        // Data is captured at the first clock transition.
        FirstEdge = 0,
        // Data is captured at the second clock transition.
        SecondEdge = 1
    };

    enum class CpolValue : Common::Word
    {
        // Clock signal is low when idle.
        IdleLow = 0,
        // Clock signal is high when idle.
        IdleHigh = 1
    };

    enum class MstrValue : Common::Word
    {
        // Slave mode.
        Slave = 0,
        // Master mode.
        Master = 1
    };

    enum class BrValue : Common::Word
    {
        // f_PCLK / 2
        ClkDiv2 = 0b000,
        // f_PCLK / 4
        ClkDiv4 = 0b001,
        // f_PCLK / 8
        ClkDiv8 = 0b010,
        // f_PCLK / 16
        ClkDiv16 = 0b011,
        // f_PCLK / 32
        ClkDiv32 = 0b100,
        // f_PCLK / 64
        ClkDiv64 = 0b101,
        // f_PCLK / 128
        ClkDiv128 = 0b110,
        // f_PCLK / 256
        ClkDiv256 = 0b111
    };

    enum class DffValue : Common::Word
    {
        // 8-bit data frame format is selected for transmission/reception.
        Bits8 = 0,
        // 16-bit data frame format is selected for transmission/reception.
        Bits16 = 1
    };

    enum class BidiModeValue : Common::Word
    {
        // 2-line unidirectional data mode selected.
        TwoLineUnidirectional = 0,
        // 1-line bidirectional data mode selected.
        OneLineBidirectional = 1
    };

    enum class FrfValue : Common::Word
    {
        // SPI Motorola mode.
        MotorolaMode = 0,
        // SPI TI mode.
        TiMode = 1
    };
} // namespace Stm32f407::Bitapi::Apb1::Spi

namespace Stm32f407::Bitapi::Apb1::Spi::details
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr>
    struct SpiX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;

        // Control register 1.
        struct Cr1
        {
            static constexpr Common::Address k_addr = SpiX::k_addr + 0x00U;

            // Clock phase.
            // This bit should not be changed when communication is ongoing.
            using Cpha = Util::Bits<k_addr, 0, 1, CphaValue>;

            // Clock polarity.
            // This bit should not be changed when communication is ongoing.
            using Cpol = Util::Bits<k_addr, 1, 1, CpolValue>;

            // Master selection.
            // This bit should not be changed when communication is ongoing.
            using Mstr = Util::Bits<k_addr, 2, 1, MstrValue>;

            // Baud rate control.
            // These bits should not be changed when communication is ongoing.
            using Br = Util::Bits<k_addr, 3, 3, BrValue>;

            // SPI enable.
            using Spe = Util::Bits<k_addr, 6, 1, Common::DiEn>;

            // Frame format.
            // No: Most significant bit transmitted first.
            // Yes: Least significant bit transmitted first.
            // - This bit should not be changed when communication is ongoing.
            using LsbFirst = Util::Bits<k_addr, 7, 1, Common::NoYes>;

            // Internal slave select.
            // - This bit has an effect only when the SSM bit is set.
            // - The value of this bit is forced onto the NSS pin and the IO value of the NSS pin is ignored.
            using Ssi = Util::Bits<k_addr, 8, 1, Common::PinState>;

            // Software slave management.
            // - When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
            using Ssm = Util::Bits<k_addr, 9, 1, Common::DiEn>;

            // Receive only.
            // No: Full duplex (Transmit and receive).
            // Yes: Output disabled (Receive-only mode).
            // - This bit, combined with the BIDImode bit, selects the direction of transfer in 2-line
            //   unidirectional mode.
            // - This bit is also useful in a multislave system in which this particular
            //   slave is not accessed, the output from the accessed slave is not corrupted.
            // - This bit is not used in I2S mode.
            using RxOnly = Util::Bits<k_addr, 10, 1, Common::NoYes>;

            // Data frame format.
            // This bit should be written only when SPI is disabled (SPE = ‘0’) for correct operation.
            using Dff = Util::Bits<k_addr, 11, 1, DffValue>;

            // CRC transfer next.
            // No: Data phase (no CRC phase).
            // Yes: Next transfer is CRC (CRC phase).
            // - When the SPI is configured in full duplex or transmitter only modes, CRCNEXT must be
            //   written as soon as the last data is written to the SPI_DR register.
            // - When the SPI is configured in receiver only mode, CRCNEXT must be set after the
            //   second last data reception.
            // - This bit should be kept cleared when the transfers are managed by DMA.
            // - It is not used in I2S mode.
            using CrcNext = Util::Bits<k_addr, 12, 1, Common::NoYes>;

            // Hardware CRC calculation enable.
            // - This bit should be written only when SPI is disabled (SPE = ‘0’) for correct operation.
            // - It is not used in I2S mode.
            using CrcEn = Util::Bits<k_addr, 13, 1, Common::DiEn>;

            // Output enable in bidirectional mode.
            // Disabled: Output disabled (receive-only mode).
            // Enabled: Output enabled (transmit-only mode).
            // - This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode.
            // - This bit is not used in I2S mode.
            // - In master mode, the MOSI pin is used while the MISO pin is used in slave mode.
            using Bidioe = Util::Bits<k_addr, 14, 1, Common::DiEn>;

            // Bidirectional data mode enable.
            // - This bit is not used in I2S mode.
            using BidiMode = Util::Bits<k_addr, 15, 1, BidiModeValue>;
        };

        // Control register 2.
        struct Cr2
        {
            static constexpr Common::Address k_addr = SpiX::k_addr + 0x04U;

            // Rx buffer DMA enable.
            // - When this bit is set, the DMA request is made whenever the RXNE flag is set.
            using RxDmaEn = Util::Bits<k_addr, 0, 1, Common::DiEn>;

            // Tx buffer DMA enable.
            // - When this bit is set, the DMA request is made whenever the TXE flag is set.
            using TxDmaEn = Util::Bits<k_addr, 1, 1, Common::DiEn>;

            // SS output enable.
            // Disabled: SS output is disabled in master mode and the cell can work in multimaster configuration.
            // Enabled: SS output is enabled in master mode and when the cell is enabled.
            //          The cell cannot work in a multimaster environment.
            // - This bit is not used in I2S mode and SPI TI mode.
            using Ssoe = Util::Bits<k_addr, 2, 1, Common::DiEn>;

            // Frame format.
            using Frf = Util::Bits<k_addr, 4, 1, FrfValue>;

            // Error interrupt enable.
            // - This bit controls the generation of an interrupt when an error condition occurs
            //   (CRCERR, OVR, MODF in SPI mode, FRE in TI mode and UDR, OVR, and FRE in I2S mode).
            using Errie = Util::Bits<k_addr, 5, 1, Common::DiEn>;

            // RX buffer not empty interrupt enable.
            // - Used to generate an interrupt request when the RXNE flag is set.
            using Rxneie = Util::Bits<k_addr, 6, 1, Common::DiEn>;

            // Tx buffer empty interrupt enable.
            // - Used to generate an interrupt request when the TXE flag is set.
            using Txeie = Util::Bits<k_addr, 7, 1, Common::DiEn>;
        };

        // Status register.
        struct Sr
        {
            static constexpr Common::Address k_addr = SpiX::k_addr + 0x08U;

            // Receive buffer not empty.
            using Rxne = Util::RoBits<k_addr, 0, 1, Common::NotEmptyFlag>;

            // Transmit buffer empty.
            using Txe = Util::RoBits<k_addr, 1, 1, Common::EmptyFlag>;

            // Channel side.
            // Left: Channel Left has to be transmitted or has been received.
            // Right: Channel Right has to be transmitted or has been received.
            // - This bit is not used for SPI mode and is meaningless in PCM mode.
            using ChSide = Util::RoBits<k_addr, 2, 1, Common::LeftRight>;

            // Underrun flag.
            // No: No underrun occurred.
            // Yes: Underrun occurred.
            // - This flag is set by hardware and reset by a software sequence.
            // - This bit is not used in SPI mode.
            using Udr = Util::RoBits<k_addr, 3, 1, Common::NoYes>;

            // CRC error flag.
            // No: CRC value received matches the SPI_RXCRCR value.
            // Yes: CRC value received does not match the SPI_RXCRCR value.
            // - This flag is set by hardware and cleared by software writing 0.
            // - This bit is not used in I2S mode.
            using CrcErr = Util::Bits<k_addr, 4, 1, Common::NoYes, Common::ZeroClear>;

            // Mode fault.
            // - This flag is set by hardware and reset by a software sequence.
            using Modf = Util::RoBits<k_addr, 5, 1, Common::NoYes>;

            // Overrun flag.
            // - This flag is set by hardware and reset by a software sequence.
            using Ovr = Util::RoBits<k_addr, 6, 1, Common::NoYes>;

            // Busy flag.
            // No: SPI (or I2S) not busy
            // Yes: SPI (or I2S) is busy in communication or Tx buffer is not empty.
            // - This flag is set and cleared by hardware.
            // - BSY flag must be used with caution.
            using Bsy = Util::RoBits<k_addr, 7, 1, Common::NoYes>;

            // Frame format error.
            // - This flag is set by hardware and cleared by software when the SPIx_SR register is read.
            // - This flag is used when the SPI operates in TI slave mode or I2S slave mode.
            using Fre = Util::RoBits<k_addr, 8, 1, Common::NoYes>;
        };

        // Data register.
        // Data received or to be transmitted.
        // The data register is split into 2 buffers. One for writing (Transmit Buffer) and another one for
        // reading (Receive buffer). A write to the data register writes into the Tx buffer and a read
        // from the data register returns the value held in the Rx buffer.
        // These notes apply to SPI mode:
        // - Depending on the data frame format selection bit (DFF in SPI_CR1 register), the data
        //   sent or received is either 8-bit or 16-bit. This selection has to be made before enabling
        //   the SPI to ensure correct operation.
        // - For an 8-bit data frame, the buffers are 8-bit and only the LSB of the register
        //   (SPI_DR[7:0]) is used for transmission/reception. When in reception mode, the MSB of
        //   the register (SPI_DR[15:8]) is forced to 0.
        // - For a 16-bit data frame, the buffers are 16-bit and the entire register, SPI_DR[15:0] is
        //   used for transmission/reception.
        using Dr = Util::Bits<SpiX::k_addr + 0x0CU, 0, 16, Common::HalfWord>;
    };
} // namespace Stm32f407::Bitapi::Apb1::Spi::details

namespace Stm32f407::Bitapi::Apb1::Spi
{
    // SPI controller 2.
    using Spi2 = details::SpiX<k_addr + 0x3800U, k_addr + 0x3bffU>;

    // SPI controller 3.
    using Spi3 = details::SpiX<k_addr + 0x3c00U, k_addr + 0x3fffU>;
} // namespace Stm32f407::Bitapi::Apb1::Spi
