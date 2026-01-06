#pragma once

#include "stm32f407_utils.hpp"

#include <cassert>

// EXTernal Interrupt controller.
namespace Apb2::Exti
{
    static constexpr Address k_baseAddr = 0x4001'3C00U;

    static constexpr int k_lineCount = 23;

    // GPIO pin number.
    enum class LineNumber : int
    {
        Line0 = 0,
        Line1 = 1,
        Line2 = 2,
        Line3 = 3,
        Line4 = 4,
        Line5 = 5,
        Line6 = 6,
        Line7 = 7,
        Line8 = 8,
        Line9 = 9,
        Line10 = 10,
        Line11 = 11,
        Line12 = 12,
        Line13 = 13,
        Line14 = 14,
        Line15 = 15,
        Line16 = 16,
        Line17 = 17,
        Line18 = 18,
        Line19 = 19,
        Line20 = 20,
        Line21 = 21,
        Line22 = k_lineCount - 1
    };

    // Mask register value.
    enum class MrValue : Word
    {
        Masked = 0,
        NotMasked = 1
    };

    // Trigger selection value.
    enum class TrValue : Word
    {
        TriggerDisabled = 0,
        TriggerEnabled = 1
    };
} // namespace Apb2::Exti

// EXTI Interrupt Mask Register
namespace Apb2::Exti::Imr
{
    static constexpr Word k_offset = 0x00;
    static constexpr Address k_addr = k_baseAddr + k_offset;

    // Set the interrupt masking on an EXTI line.
    static void set(LineNumber line, MrValue lineMask)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        *p = set_bits(*p, intLine, 1, lineMask);
    }

    // Get the interrupt masking on an EXTI line.
    static MrValue get(LineNumber line)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        return extract_bits_as<MrValue>(*p, intLine, 1);
    }

    using Mr0 = Bits<MrValue, k_addr, 0, 1>;
    using Mr1 = Bits<MrValue, k_addr, 1, 1>;
    using Mr2 = Bits<MrValue, k_addr, 2, 1>;
    using Mr3 = Bits<MrValue, k_addr, 3, 1>;
    using Mr4 = Bits<MrValue, k_addr, 4, 1>;
    using Mr5 = Bits<MrValue, k_addr, 5, 1>;
    using Mr6 = Bits<MrValue, k_addr, 6, 1>;
    using Mr7 = Bits<MrValue, k_addr, 7, 1>;
    using Mr8 = Bits<MrValue, k_addr, 8, 1>;
    using Mr9 = Bits<MrValue, k_addr, 9, 1>;
    using Mr10 = Bits<MrValue, k_addr, 10, 1>;
    using Mr11 = Bits<MrValue, k_addr, 11, 1>;
    using Mr12 = Bits<MrValue, k_addr, 12, 1>;
    using Mr13 = Bits<MrValue, k_addr, 13, 1>;
    using Mr14 = Bits<MrValue, k_addr, 14, 1>;
    using Mr15 = Bits<MrValue, k_addr, 15, 1>;
    using Mr16 = Bits<MrValue, k_addr, 16, 1>;
    using Mr17 = Bits<MrValue, k_addr, 17, 1>;
    using Mr18 = Bits<MrValue, k_addr, 18, 1>;
    using Mr19 = Bits<MrValue, k_addr, 19, 1>;
    using Mr20 = Bits<MrValue, k_addr, 20, 1>;
    using Mr21 = Bits<MrValue, k_addr, 21, 1>;
    using Mr22 = Bits<MrValue, k_addr, 22, 1>;
} // namespace Apb2::Exti::Imr

// EXTI Event Mask Register
namespace Apb2::Exti::Emr
{
    static constexpr Word k_offset = 0x04;
    static constexpr Address k_addr = k_baseAddr + k_offset;

    // Set the event masking on an EXTI line.
    static void set(LineNumber line, MrValue lineMask)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        *p = set_bits(*p, intLine, 1, lineMask);
    }

    // Get the event masking on an EXTI line.
    static MrValue get(LineNumber line)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        return extract_bits_as<MrValue>(*p, intLine, 1);
    }

    using Mr0 = Bits<MrValue, k_addr, 0, 1>;
    using Mr1 = Bits<MrValue, k_addr, 1, 1>;
    using Mr2 = Bits<MrValue, k_addr, 2, 1>;
    using Mr3 = Bits<MrValue, k_addr, 3, 1>;
    using Mr4 = Bits<MrValue, k_addr, 4, 1>;
    using Mr5 = Bits<MrValue, k_addr, 5, 1>;
    using Mr6 = Bits<MrValue, k_addr, 6, 1>;
    using Mr7 = Bits<MrValue, k_addr, 7, 1>;
    using Mr8 = Bits<MrValue, k_addr, 8, 1>;
    using Mr9 = Bits<MrValue, k_addr, 9, 1>;
    using Mr10 = Bits<MrValue, k_addr, 10, 1>;
    using Mr11 = Bits<MrValue, k_addr, 11, 1>;
    using Mr12 = Bits<MrValue, k_addr, 12, 1>;
    using Mr13 = Bits<MrValue, k_addr, 13, 1>;
    using Mr14 = Bits<MrValue, k_addr, 14, 1>;
    using Mr15 = Bits<MrValue, k_addr, 15, 1>;
    using Mr16 = Bits<MrValue, k_addr, 16, 1>;
    using Mr17 = Bits<MrValue, k_addr, 17, 1>;
    using Mr18 = Bits<MrValue, k_addr, 18, 1>;
    using Mr19 = Bits<MrValue, k_addr, 19, 1>;
    using Mr20 = Bits<MrValue, k_addr, 20, 1>;
    using Mr21 = Bits<MrValue, k_addr, 21, 1>;
    using Mr22 = Bits<MrValue, k_addr, 22, 1>;
} // namespace Apb2::Exti::Emr

// EXTI Rising Trigger Selection Register
namespace Apb2::Exti::Rtsr
{
    static constexpr Word k_offset = 0x08;
    static constexpr Address k_addr = k_baseAddr + k_offset;

    // Set the Rising Trigger Selection on an EXTI line.
    static void set(LineNumber line, TrValue trigger)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        *p = set_bits(*p, intLine, 1, trigger);
    }

    // Get the Rising Trigger Selection on an EXTI line.
    static TrValue get(LineNumber line)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        return extract_bits_as<TrValue>(*p, intLine, 1);
    }

    using Tr0 = Bits<TrValue, k_addr, 0, 1>;
    using Tr1 = Bits<TrValue, k_addr, 1, 1>;
    using Tr2 = Bits<TrValue, k_addr, 2, 1>;
    using Tr3 = Bits<TrValue, k_addr, 3, 1>;
    using Tr4 = Bits<TrValue, k_addr, 4, 1>;
    using Tr5 = Bits<TrValue, k_addr, 5, 1>;
    using Tr6 = Bits<TrValue, k_addr, 6, 1>;
    using Tr7 = Bits<TrValue, k_addr, 7, 1>;
    using Tr8 = Bits<TrValue, k_addr, 8, 1>;
    using Tr9 = Bits<TrValue, k_addr, 9, 1>;
    using Tr10 = Bits<TrValue, k_addr, 10, 1>;
    using Tr11 = Bits<TrValue, k_addr, 11, 1>;
    using Tr12 = Bits<TrValue, k_addr, 12, 1>;
    using Tr13 = Bits<TrValue, k_addr, 13, 1>;
    using Tr14 = Bits<TrValue, k_addr, 14, 1>;
    using Tr15 = Bits<TrValue, k_addr, 15, 1>;
    using Tr16 = Bits<TrValue, k_addr, 16, 1>;
    using Tr17 = Bits<TrValue, k_addr, 17, 1>;
    using Tr18 = Bits<TrValue, k_addr, 18, 1>;
    using Tr19 = Bits<TrValue, k_addr, 19, 1>;
    using Tr20 = Bits<TrValue, k_addr, 20, 1>;
    using Tr21 = Bits<TrValue, k_addr, 21, 1>;
    using Tr22 = Bits<TrValue, k_addr, 22, 1>;
} // namespace Apb2::Exti::Rtsr

// EXTI Falling Trigger Selection Register
namespace Apb2::Exti::Ftsr
{
    static constexpr Word k_offset = 0x0c;
    static constexpr Address k_addr = k_baseAddr + k_offset;

    // Set the Falling Trigger Selection on an EXTI line.
    static void set(LineNumber line, TrValue trigger)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        *p = set_bits(*p, intLine, 1, trigger);
    }

    // Get the Falling Trigger Selection on an EXTI line.
    static TrValue get(LineNumber line)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        return extract_bits_as<TrValue>(*p, intLine, 1);
    }

    using Tr0 = Bits<TrValue, k_addr, 0, 1>;
    using Tr1 = Bits<TrValue, k_addr, 1, 1>;
    using Tr2 = Bits<TrValue, k_addr, 2, 1>;
    using Tr3 = Bits<TrValue, k_addr, 3, 1>;
    using Tr4 = Bits<TrValue, k_addr, 4, 1>;
    using Tr5 = Bits<TrValue, k_addr, 5, 1>;
    using Tr6 = Bits<TrValue, k_addr, 6, 1>;
    using Tr7 = Bits<TrValue, k_addr, 7, 1>;
    using Tr8 = Bits<TrValue, k_addr, 8, 1>;
    using Tr9 = Bits<TrValue, k_addr, 9, 1>;
    using Tr10 = Bits<TrValue, k_addr, 10, 1>;
    using Tr11 = Bits<TrValue, k_addr, 11, 1>;
    using Tr12 = Bits<TrValue, k_addr, 12, 1>;
    using Tr13 = Bits<TrValue, k_addr, 13, 1>;
    using Tr14 = Bits<TrValue, k_addr, 14, 1>;
    using Tr15 = Bits<TrValue, k_addr, 15, 1>;
    using Tr16 = Bits<TrValue, k_addr, 16, 1>;
    using Tr17 = Bits<TrValue, k_addr, 17, 1>;
    using Tr18 = Bits<TrValue, k_addr, 18, 1>;
    using Tr19 = Bits<TrValue, k_addr, 19, 1>;
    using Tr20 = Bits<TrValue, k_addr, 20, 1>;
    using Tr21 = Bits<TrValue, k_addr, 21, 1>;
    using Tr22 = Bits<TrValue, k_addr, 22, 1>;
} // namespace Apb2::Exti::Ftsr

// EXTI Software Interrupt Event Register
//
// If interrupts are enabled on line x in the EXTI_IMR register, writing '1' to SWIERx bit when it is
// set at '0' sets the corresponding pending bit in the EXTI_PR register, thus resulting in an
// interrupt request generation.
// This bit is cleared by clearing the corresponding bit in EXTI_PR (by writing a 1 to the bit).
namespace Apb2::Exti::Swier
{
    static constexpr Word k_offset = 0x10;
    static constexpr Address k_addr = k_baseAddr + k_offset;

    // Software Interrupt Event Register value.
    enum class SwierValue : Word
    {
        TriggerInterrupt = 1
    };

    static void set(LineNumber line, SwierValue value)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        *p = set_bits(*p, intLine, 1, value);
    }

    static SwierValue get(LineNumber line)
    {
        const auto intLine = static_cast<int>(line);
        assert(0 <= intLine && intLine <= k_lineCount);
        volatile Word* p = reinterpret_cast<Word*>(k_addr);
        return extract_bits_as<SwierValue>(*p, intLine, 1);
    }

    using Swier0 = Bits<SwierValue, k_addr, 0, 1>;
    using Swier1 = Bits<SwierValue, k_addr, 1, 1>;
    using Swier2 = Bits<SwierValue, k_addr, 2, 1>;
    using Swier3 = Bits<SwierValue, k_addr, 3, 1>;
    using Swier4 = Bits<SwierValue, k_addr, 4, 1>;
    using Swier5 = Bits<SwierValue, k_addr, 5, 1>;
    using Swier6 = Bits<SwierValue, k_addr, 6, 1>;
    using Swier7 = Bits<SwierValue, k_addr, 7, 1>;
    using Swier8 = Bits<SwierValue, k_addr, 8, 1>;
    using Swier9 = Bits<SwierValue, k_addr, 9, 1>;
    using Swier10 = Bits<SwierValue, k_addr, 10, 1>;
    using Swier11 = Bits<SwierValue, k_addr, 11, 1>;
    using Swier12 = Bits<SwierValue, k_addr, 12, 1>;
    using Swier13 = Bits<SwierValue, k_addr, 13, 1>;
    using Swier14 = Bits<SwierValue, k_addr, 14, 1>;
    using Swier15 = Bits<SwierValue, k_addr, 15, 1>;
    using Swier16 = Bits<SwierValue, k_addr, 16, 1>;
    using Swier17 = Bits<SwierValue, k_addr, 17, 1>;
    using Swier18 = Bits<SwierValue, k_addr, 18, 1>;
    using Swier19 = Bits<SwierValue, k_addr, 19, 1>;
    using Swier20 = Bits<SwierValue, k_addr, 20, 1>;
    using Swier21 = Bits<SwierValue, k_addr, 21, 1>;
    using Swier22 = Bits<SwierValue, k_addr, 22, 1>;
} // namespace Apb2::Exti::Swier

// EXTI Pending Register
//
// 0: No trigger request occurred
// 1: selected trigger request occurred
// This bit is set when the selected edge event arrives on the external interrupt line.
// This bit is cleared by programming it to ‘1’.
namespace Apb2::Exti::Pr
{
    static constexpr Word k_offset = 0x14;
    static constexpr Address k_addr = k_baseAddr + k_offset;

    // Pending Register value.
    enum class PrValue : Word
    {
        NotPending = 0,
        Pending = 1,
    };

    // Pending Register value.
    enum class PrClearValue : Word
    {
        Clear = 1,
    };

    using Pr0 = Bits<PrValue, k_addr, 0, 1>;
    using Pr1 = Bits<PrValue, k_addr, 1, 1>;
    using Pr2 = Bits<PrValue, k_addr, 2, 1>;
    using Pr3 = Bits<PrValue, k_addr, 3, 1>;
    using Pr4 = Bits<PrValue, k_addr, 4, 1>;
    using Pr5 = Bits<PrValue, k_addr, 5, 1>;
    using Pr6 = Bits<PrValue, k_addr, 6, 1>;
    using Pr7 = Bits<PrValue, k_addr, 7, 1>;
    using Pr8 = Bits<PrValue, k_addr, 8, 1>;
    using Pr9 = Bits<PrValue, k_addr, 9, 1>;
    using Pr10 = Bits<PrValue, k_addr, 10, 1>;
    using Pr11 = Bits<PrValue, k_addr, 11, 1>;
    using Pr12 = Bits<PrValue, k_addr, 12, 1>;
    using Pr13 = Bits<PrValue, k_addr, 13, 1>;
    using Pr14 = Bits<PrValue, k_addr, 14, 1>;
    using Pr15 = Bits<PrValue, k_addr, 15, 1>;
    using Pr16 = Bits<PrValue, k_addr, 16, 1>;
    using Pr17 = Bits<PrValue, k_addr, 17, 1>;
    using Pr18 = Bits<PrValue, k_addr, 18, 1>;
    using Pr19 = Bits<PrValue, k_addr, 19, 1>;
    using Pr20 = Bits<PrValue, k_addr, 20, 1>;
    using Pr21 = Bits<PrValue, k_addr, 21, 1>;
    using Pr22 = Bits<PrValue, k_addr, 22, 1>;
} // namespace Apb2::Exti::Pr
