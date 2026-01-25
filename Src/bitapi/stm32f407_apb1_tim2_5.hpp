#pragma once

#include "stm32f407_apb1.hpp"
#include "stm32f407_utils.hpp"

namespace Stm32f407::Bitapi::Apb1::Tim2_5
{
    // Value to configure the update request source.
    enum class UrsValue : Common::Word
    {
        // Any of the following events generate an update interrupt (or DMA request) if enabled.
        // These events can be:
        // – Counter overflow/underflow
        // – Setting the UG bit
        // – Update generation through the slave mode controller
        AnyEvent = 0,
        // Only counter overflow/underflow generates an update interrupt
        // (or DMA request) if enabled.
        OverflowUnderflow = 1
    };

    // Value to configure the one-pulse mode.
    enum class OpmValue : Common::Word
    {
        // Counter is not stopped at update event.
        CounterNotStopped = 0,
        // Counter stops counting at the next update event (clearing the CEN bit).
        CounterStopped = 1
    };

    // Value to configure the counter direction.
    enum class DirValue : Common::Word
    {
        // Counter used as an upcounter.
        Upcounter = 0,
        // Counter used as a downcounter.
        Downcounter = 1
    };

    // Value to configure the center-aligned mode selection.
    enum class CmsValue : Common::Word
    {
        // Edge-aligned mode. The counter counts up or down depending on the DIR bit.
        EdgeAligned = 0b00,
        // Center-aligned mode 1. The counter counts up and down alternatively.
        // Output compare interrupt flags of channels configured in
        // output (CCxS=00 in TIMx_CCMRx register) are set
        // only when the counter is counting down.
        CenterAligned1 = 0b01,
        // Center-aligned mode 2. The counter counts up and down alternatively.
        // Output compare interrupt flags of channels configured in
        // output (CCxS=00 in TIMx_CCMRx register) are set
        // only when the counter is counting up.
        CenterAligned2 = 0b10,
        // Center-aligned mode 3. The counter counts up and down alternatively.
        // Output compare interrupt flags of channels configured in
        // output (CCxS=00 in TIMx_CCMRx register) are set
        // both when the counter is counting up and down.
        CenterAligned3 = 0b11
    };

    // Value to configure the auto-reload preload enable.
    enum class ArpeValue : Common::Word
    {
        // TIMx_ARR register is not buffered.
        NotBuffered = 0,
        // TIMx_ARR register is buffered.
        Buffered = 1
    };

    // Value to configure the clock division.
    enum class CkdValue : Common::Word
    {
        // tDTS = tCK_INT
        Div1 = 0b00,
        // tDTS = 2 * tCK_INT
        Div2 = 0b01,
        // tDTS = 4 * tCK_INT
        Div4 = 0b10
    };

    // Value to configure the capture/compare DMA selection.
    enum class CcdsValue : Common::Word
    {
        // CCx DMA request sent when CCx event occurs.
        OnCompareEvent = 0,
        // CCx DMA requests sent when update event occurs.
        OnUpdateEvent = 1
    };

    // Value to configure the master mode selection.
    enum class MmsValue : Common::Word
    {
        // The UG bit from the TIMx_EGR register is used as trigger output (TRGO).
        Reset = 0b000,
        // The counter enable signal (CNT_EN) is used as trigger output (TRGO).
        Enable = 0b001,
        // The update event is selected as trigger output (TRGO).
        Update = 0b010,
        // The trigger output send a positive pulse when the CC1IF flag is to be
        // set (even if it was already high), as soon as a capture
        // or a compare match occurred.
        ComparePulse = 0b011,
        // OC1REF signal is used as trigger output (TRGO).
        CompareOc1Ref = 0b100,
        // OC2REF signal is used as trigger output (TRGO).
        CompareOc2Ref = 0b101,
        // OC3REF signal is used as trigger output (TRGO).
        CompareOc3Ref = 0b110,
        // OC4REF signal is used as trigger output (TRGO).
        CompareOc4Ref = 0b111
    };

    // Value to configure the TI1 selection.
    enum class Ti1sValue : Common::Word
    {
        // The TIMx_CH1 pin is connected to TI1 input.
        Ch1 = 0,
        // The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination).
        Ch123 = 1
    };

    // Value to configure the slave mode selection.
    enum class SmsValue : Common::Word
    {
        // Slave mode disabled - if CEN = '1 then the prescaler is clocked directly
        // by the internal clock.
        Disabled = 0b000,
        // Encoder mode 1 - Counter counts up/down on TI1FP1 edge depending on TI2FP2 level.
        EncoderMode1 = 0b001,
        // Encoder mode 2 - Counter counts up/down on TI2FP2 edge depending on TI1FP1 level.
        EncoderMode2 = 0b010,
        // Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges
        // depending on the level of the other input.
        EncoderMode3 = 0b011,
        // Reset mode - Rising edge of the selected trigger input (TRGI) reinitializes the
        // counter and generates an update of the registers.
        ResetMode = 0b100,
        // Gated mode - The counter clock is enabled when the trigger input (TRGI) is high.
        // The counter stops (but is not reset) as soon as the trigger becomes low.
        // Both start and stop of the counter are controlled.
        GatedMode = 0b101,
        // Trigger mode - The counter starts at a rising edge of the trigger TRGI
        // (but it is not reset). Only the start of the counter is controlled.
        TriggerMode = 0b110,
        // External Clock mode 1 - Rising edges of the selected trigger (TRGI) clock the counter.
        ExternalClockMode1 = 0b111
    };

    // Value to configure the trigger selection.
    enum class TsValue : Common::Word
    {
        // Internal trigger 0 (ITR0).
        Itr0 = 0b000,
        // Internal trigger 1 (ITR1).
        Itr1 = 0b001,
        // Internal trigger 2 (ITR2).
        Itr2 = 0b010,
        // Internal trigger 3 (ITR3).
        Itr3 = 0b011,
        // TI1 Edge Detector (TI1F_ED).
        Ti1fEd = 0b100,
        // Filtered Timer Input 1 (TI1FP1).
        Ti1fp1 = 0b101,
        // Filtered Timer Input 2 (TI2FP2).
        Ti2fp2 = 0b110,
        // External Trigger input (ETRF).
        Etrf = 0b110
    };

    // Value to configure the master/slave mode.
    enum class MsmValue : Common::Word
    {
        // No action.
        Disabled = 0,
        // The effect of an event on the trigger input (TRGI) is delayed to allow a perfect
        // synchronization between the current timer and its slaves (through TRGO).
        // It is useful if we want to synchronize several timers on a single external event.
        Enabled = 1
    };

    // Value to configure the external trigger filter.
    enum class EtfValue : Common::Word
    {
        // No filter, sampling is done at fDTS
        NoFilterFDts = 0b0000,
        // f_SAMPLING = f_CK_INT, N = 2
        FCkIntN2 = 0b0001,
        // f_SAMPLING = f_CK_INT, N = 4
        FCkIntN4 = 0b0010,
        // f_SAMPLING = f_CK_INT, N = 8
        FCkIntN8 = 0b0011,
        // f_SAMPLING = f_DTS / 2, N = 6
        FDts2N6 = 0b0100,
        // f_SAMPLING = f_DTS / 2, N = 8
        FDts2N8 = 0b0101,
        // f_SAMPLING = f_DTS / 4, N = 6
        FDts4N6 = 0b0110,
        // f_SAMPLING = f_DTS / 4, N = 8
        FDts4N8 = 0b0111,
        // f_SAMPLING = f_DTS / 8, N = 6
        FDts8N6 = 0b1000,
        // f_SAMPLING = f_DTS / 8, N = 8
        FDts8N8 = 0b1001,
        // f_SAMPLING = f_DTS / 16, N = 5
        FDts16N5 = 0b1010,
        // f_SAMPLING = f_DTS / 16, N = 6
        FDts16N6 = 0b1011,
        // f_SAMPLING = f_DTS / 16, N = 8
        FDts16N8 = 0b1100,
        // f_SAMPLING = f_DTS / 32, N = 5
        FDts32N5 = 0b1101,
        // f_SAMPLING = f_DTS / 32, N = 6
        FDts32N6 = 0b1110,
        // f_SAMPLING = f_DTS / 32, N = 8
        FDts32N8 = 0b1111
    };

    // Value to configure the external trigger prescaler.
    enum class EtpsValue : Common::Word
    {
        // Prescaler off.
        Div1 = 0b00,
        // ETRP frequency is divided by 2.
        Div2 = 0b01,
        // ETRP frequency is divided by 4.
        Div4 = 0b10,
        // ETRP frequency is divided by 8.
        Div8 = 0b11
    };

    // Value to configure the external trigger polarity.
    enum class EtpValue : Common::Word
    {
        // ETR is non-inverted, active at high level or rising edge.
        NonInverted = 0,
        // ETR is inverted, active at low level or falling edge.
        Inverted = 1
    };

    // Event (e.g. interrupt) flag value (read).
    enum class EventFlagRead : Common::Word
    {
        NotPending = 0,
        Pending = 1,
    };

    // Event (e.g. interrupt) flag value (read).
    enum class EventFlagWrite : Common::Word
    {
        Clear = 0,
    };

} // namespace Stm32f407::Bitapi::Apb1::Tim2_5

namespace Stm32f407::Bitapi::Apb1::Tim2_5::details
{
    template <Common::Address TVBaseAddr, Common::Address TVEndAddr, typename TValue>
    struct TimX
    {
        static constexpr Common::Address k_addr = TVBaseAddr;
        static constexpr Common::Address k_endAddr = TVEndAddr;
        static constexpr Common::Word k_memSize = k_endAddr - k_addr + 1;

        using ValueType = TValue;

        // Control register 1.
        struct Cr1
        {
            static constexpr Common::Address k_addr = TimX::k_addr + 0x00U;
            static constexpr Common::Word k_resetValue = 0x0000U;

            // The value of the entire register.
            using Value = Util::Bits<k_addr, 0, 16, Common::Word>;

            // Counter enable.
            // CEN is cleared automatically in one-pulse mode, when an update event occurs.
            using Cen = Util::Bits<k_addr, 0, 1, Common::DiEn>;

            // Update disable.
            //
            // This bit is set and cleared by software to enable/disable UEV event generation.
            //
            // The Update (UEV) event is generated by one of the following events:
            // – Counter overflow/underflow
            // – Setting the UG bit
            // – Update generation through the slave mode controller
            //
            // When disabled, the Update event is not generated, shadow registers keep their value
            // (ARR, PSC, CCRx). However the counter and the prescaler are reinitialized if the UG bit is
            // set or if a hardware reset is received from the slave mode controller.
            using Udis = Util::Bits<k_addr, 1, 1, Common::EnDi>;

            // Update request source.
            // This bit is set and cleared by software to select the UEV event sources.
            using Urs = Util::Bits<k_addr, 2, 1, UrsValue>;

            // One-pulse mode.
            using Opm = Util::Bits<k_addr, 3, 1, OpmValue>;

            // Direction.
            using Dir = Util::Bits<k_addr, 4, 1, DirValue>;

            // Center-aligned mode selection.
            using Cms = Util::Bits<k_addr, 5, 2, CmsValue>;

            // Auto-reload preload enable.
            using Arpe = Util::Bits<k_addr, 7, 1, ArpeValue>;

            // Clock division.
            // This bit-field indicates the division ratio between the timer clock (CK_INT) frequency
            // and sampling clock used by the digital filters (ETR, TIx).
            using Ckd = Util::Bits<k_addr, 8, 2, CkdValue>;
        };

        // Control register 2.
        struct Cr2
        {
            static constexpr Common::Address k_addr = TimX::k_addr + 0x04U;

            // Capture/compare DMA selection.
            using Ccds = Util::Bits<k_addr, 3, 1, Common::EnDi>;

            // Master mode selection.
            using Mms = Util::Bits<k_addr, 4, 3, MmsValue>;

            // TI1 selection.
            using Ti1s = Util::Bits<k_addr, 7, 1, Ti1sValue>;
        };

        struct Smcr
        {
            static constexpr Common::Address k_addr = TimX::k_addr + 0x08U;

            // Slave mode selection.
            using Sms = Util::Bits<k_addr, 0, 3, SmsValue>;

            // This bit-field selects the trigger input to be used to synchronize the counter.
            using Ts = Util::Bits<k_addr, 4, 3, TsValue>;

            // Master/slave mode.
            using Msm = Util::Bits<k_addr, 7, 1, MsmValue>;

            // External trigger filter.
            // This bit-field defines the frequency used to sample ETRP signal
            // and the length of the digital filter applied to ETRP.
            // The digital filter is made of an event counter in which N consecutive
            // events are needed to validate a transition on the output.
            using Etf = Util::Bits<k_addr, 8, 4, EtfValue>;

            // External trigger prescaler.
            // External trigger signal ETRP frequency must be at most 1/4 of CK_INT frequency.
            // A prescaler can be enabled to reduce ETRP frequency.
            // It is useful when inputting fast external clocks.
            using Etps = Util::Bits<k_addr, 12, 2, EtpsValue>;

            // External clock enable.
            using Ece = Util::Bits<k_addr, 14, 1, Common::DiEn>;

            // External trigger polarity.
            // This bit selects whether ETR or not-ETR is used for trigger operations.
            using Etp = Util::Bits<k_addr, 15, 1, EtpValue>;
        };

        // DMA/Interrupt enable register.
        struct Dier
        {
            static constexpr Common::Address k_addr = TimX::k_addr + 0x0CU;

            // Update interrupt enable.
            using Uie = Util::Bits<k_addr, 0, 1, Common::DiEn>;

            // Capture/compare 1 interrupt enable.
            using Cc1ie = Util::Bits<k_addr, 1, 1, Common::DiEn>;

            // Capture/compare 2 interrupt enable.
            using Cc2ie = Util::Bits<k_addr, 2, 1, Common::DiEn>;

            // Capture/compare 3 interrupt enable.
            using Cc3ie = Util::Bits<k_addr, 3, 1, Common::DiEn>;

            // Capture/compare 4 interrupt enable.
            using Cc4ie = Util::Bits<k_addr, 4, 1, Common::DiEn>;

            // Trigger interrupt enable.
            using Tie = Util::Bits<k_addr, 6, 1, Common::DiEn>;

            // Update DMA request enable.
            using Ude = Util::Bits<k_addr, 8, 1, Common::DiEn>;

            // Capture/compare 1 DMA request enable.
            using Cc1de = Util::Bits<k_addr, 9, 1, Common::DiEn>;

            // Capture/compare 2 DMA request enable.
            using Cc2de = Util::Bits<k_addr, 10, 1, Common::DiEn>;

            // Capture/compare 3 DMA request enable.
            using Cc3de = Util::Bits<k_addr, 11, 1, Common::DiEn>;

            // Capture/compare 4 DMA request enable.
            using Cc4de = Util::Bits<k_addr, 12, 1, Common::DiEn>;

            // Trigger DMA request enable.
            using Tde = Util::Bits<k_addr, 14, 1, Common::DiEn>;
        };

        // Status register.
        struct Sr
        {
            static constexpr Common::Address k_addr = TimX::k_addr + 0x10U;

            // Update interrupt flag.
            using Uif = Util::Bits<k_addr, 0, 1, EventFlagRead, EventFlagWrite>;

            // Capture/compare 1 interrupt flag.
            using Cc1if = Util::Bits<k_addr, 1, 1, EventFlagRead, EventFlagWrite>;

            // Capture/compare 2 interrupt flag.
            using Cc2if = Util::Bits<k_addr, 2, 1, EventFlagRead, EventFlagWrite>;

            // Capture/compare 3 interrupt flag.
            using Cc3if = Util::Bits<k_addr, 3, 1, EventFlagRead, EventFlagWrite>;

            // Capture/compare 4 interrupt flag.
            using Cc4if = Util::Bits<k_addr, 4, 1, EventFlagRead, EventFlagWrite>;

            // Trigger interrupt flag.
            using Tif = Util::Bits<k_addr, 6, 1, EventFlagRead, EventFlagWrite>;

            // Capture/Compare 1 overcapture flag.
            using Cc1of = Util::Bits<k_addr, 9, 1, EventFlagRead, EventFlagWrite>;

            // Capture/Compare 2 overcapture flag.
            using Cc2of = Util::Bits<k_addr, 10, 1, EventFlagRead, EventFlagWrite>;

            // Capture/Compare 3 overcapture flag.
            using Cc3of = Util::Bits<k_addr, 11, 1, EventFlagRead, EventFlagWrite>;

            // Capture/Compare 4 overcapture flag.
            using Cc4of = Util::Bits<k_addr, 12, 1, EventFlagRead, EventFlagWrite>;
        };

        // Counter.
        using Cnt = Util::Bits<k_addr + 0x24U, 0, sizeof(TValue) * 8, TValue>;

        // Prescaler.
        // The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
        // PSC contains the value to be loaded in the active prescaler register at each update event
        // (including when the counter is cleared through UG bit of TIMx_EGR register or through
        // trigger controller when configured in “reset mode”).
        using Psc = Util::Bits<k_addr + 0x28U, 0, sizeof(Common::HalfWord) * 8, Common::HalfWord>;

        // Auto-reload register.
        using Arr = Util::Bits<k_addr + 0x2CU, 0, sizeof(TValue) * 8, TValue>;
    };
} // namespace Stm32f407::Bitapi::Apb1::Tim2_5::details

namespace Stm32f407::Bitapi::Apb1::Tim2_5
{
    // General-purpose timer #2.
    using Tim2 = details::TimX<k_addr + 0x0U, k_addr + 0x3ffU, Common::Word>;

    // General-purpose timer #3.
    using Tim3 = details::TimX<k_addr + 0x400U, k_addr + 0x7ffU, Common::HalfWord>;

    // General-purpose timer #4.
    using Tim4 = details::TimX<k_addr + 0x800U, k_addr + 0xbffU, Common::HalfWord>;

    // General-purpose timer #5.
    using Tim5 = details::TimX<k_addr + 0xc00U, k_addr + 0xfffU, Common::Word>;
} // namespace Stm32f407::Bitapi::Apb1::Tim2_5
