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

    using Mr0 = Bits<k_addr, 0, 1, MrValue>;
    using Mr1 = Bits<k_addr, 1, 1, MrValue>;
    using Mr2 = Bits<k_addr, 2, 1, MrValue>;
    using Mr3 = Bits<k_addr, 3, 1, MrValue>;
    using Mr4 = Bits<k_addr, 4, 1, MrValue>;
    using Mr5 = Bits<k_addr, 5, 1, MrValue>;
    using Mr6 = Bits<k_addr, 6, 1, MrValue>;
    using Mr7 = Bits<k_addr, 7, 1, MrValue>;
    using Mr8 = Bits<k_addr, 8, 1, MrValue>;
    using Mr9 = Bits<k_addr, 9, 1, MrValue>;
    using Mr10 = Bits<k_addr, 10, 1, MrValue>;
    using Mr11 = Bits<k_addr, 11, 1, MrValue>;
    using Mr12 = Bits<k_addr, 12, 1, MrValue>;
    using Mr13 = Bits<k_addr, 13, 1, MrValue>;
    using Mr14 = Bits<k_addr, 14, 1, MrValue>;
    using Mr15 = Bits<k_addr, 15, 1, MrValue>;
    using Mr16 = Bits<k_addr, 16, 1, MrValue>;
    using Mr17 = Bits<k_addr, 17, 1, MrValue>;
    using Mr18 = Bits<k_addr, 18, 1, MrValue>;
    using Mr19 = Bits<k_addr, 19, 1, MrValue>;
    using Mr20 = Bits<k_addr, 20, 1, MrValue>;
    using Mr21 = Bits<k_addr, 21, 1, MrValue>;
    using Mr22 = Bits<k_addr, 22, 1, MrValue>;
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

    using Mr0 = Bits<k_addr, 0, 1, MrValue>;
    using Mr1 = Bits<k_addr, 1, 1, MrValue>;
    using Mr2 = Bits<k_addr, 2, 1, MrValue>;
    using Mr3 = Bits<k_addr, 3, 1, MrValue>;
    using Mr4 = Bits<k_addr, 4, 1, MrValue>;
    using Mr5 = Bits<k_addr, 5, 1, MrValue>;
    using Mr6 = Bits<k_addr, 6, 1, MrValue>;
    using Mr7 = Bits<k_addr, 7, 1, MrValue>;
    using Mr8 = Bits<k_addr, 8, 1, MrValue>;
    using Mr9 = Bits<k_addr, 9, 1, MrValue>;
    using Mr10 = Bits<k_addr, 10, 1, MrValue>;
    using Mr11 = Bits<k_addr, 11, 1, MrValue>;
    using Mr12 = Bits<k_addr, 12, 1, MrValue>;
    using Mr13 = Bits<k_addr, 13, 1, MrValue>;
    using Mr14 = Bits<k_addr, 14, 1, MrValue>;
    using Mr15 = Bits<k_addr, 15, 1, MrValue>;
    using Mr16 = Bits<k_addr, 16, 1, MrValue>;
    using Mr17 = Bits<k_addr, 17, 1, MrValue>;
    using Mr18 = Bits<k_addr, 18, 1, MrValue>;
    using Mr19 = Bits<k_addr, 19, 1, MrValue>;
    using Mr20 = Bits<k_addr, 20, 1, MrValue>;
    using Mr21 = Bits<k_addr, 21, 1, MrValue>;
    using Mr22 = Bits<k_addr, 22, 1, MrValue>;
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

    using Tr0 = Bits<k_addr, 0, 1, TrValue>;
    using Tr1 = Bits<k_addr, 1, 1, TrValue>;
    using Tr2 = Bits<k_addr, 2, 1, TrValue>;
    using Tr3 = Bits<k_addr, 3, 1, TrValue>;
    using Tr4 = Bits<k_addr, 4, 1, TrValue>;
    using Tr5 = Bits<k_addr, 5, 1, TrValue>;
    using Tr6 = Bits<k_addr, 6, 1, TrValue>;
    using Tr7 = Bits<k_addr, 7, 1, TrValue>;
    using Tr8 = Bits<k_addr, 8, 1, TrValue>;
    using Tr9 = Bits<k_addr, 9, 1, TrValue>;
    using Tr10 = Bits<k_addr, 10, 1, TrValue>;
    using Tr11 = Bits<k_addr, 11, 1, TrValue>;
    using Tr12 = Bits<k_addr, 12, 1, TrValue>;
    using Tr13 = Bits<k_addr, 13, 1, TrValue>;
    using Tr14 = Bits<k_addr, 14, 1, TrValue>;
    using Tr15 = Bits<k_addr, 15, 1, TrValue>;
    using Tr16 = Bits<k_addr, 16, 1, TrValue>;
    using Tr17 = Bits<k_addr, 17, 1, TrValue>;
    using Tr18 = Bits<k_addr, 18, 1, TrValue>;
    using Tr19 = Bits<k_addr, 19, 1, TrValue>;
    using Tr20 = Bits<k_addr, 20, 1, TrValue>;
    using Tr21 = Bits<k_addr, 21, 1, TrValue>;
    using Tr22 = Bits<k_addr, 22, 1, TrValue>;
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

    using Tr0 = Bits<k_addr, 0, 1, TrValue>;
    using Tr1 = Bits<k_addr, 1, 1, TrValue>;
    using Tr2 = Bits<k_addr, 2, 1, TrValue>;
    using Tr3 = Bits<k_addr, 3, 1, TrValue>;
    using Tr4 = Bits<k_addr, 4, 1, TrValue>;
    using Tr5 = Bits<k_addr, 5, 1, TrValue>;
    using Tr6 = Bits<k_addr, 6, 1, TrValue>;
    using Tr7 = Bits<k_addr, 7, 1, TrValue>;
    using Tr8 = Bits<k_addr, 8, 1, TrValue>;
    using Tr9 = Bits<k_addr, 9, 1, TrValue>;
    using Tr10 = Bits<k_addr, 10, 1, TrValue>;
    using Tr11 = Bits<k_addr, 11, 1, TrValue>;
    using Tr12 = Bits<k_addr, 12, 1, TrValue>;
    using Tr13 = Bits<k_addr, 13, 1, TrValue>;
    using Tr14 = Bits<k_addr, 14, 1, TrValue>;
    using Tr15 = Bits<k_addr, 15, 1, TrValue>;
    using Tr16 = Bits<k_addr, 16, 1, TrValue>;
    using Tr17 = Bits<k_addr, 17, 1, TrValue>;
    using Tr18 = Bits<k_addr, 18, 1, TrValue>;
    using Tr19 = Bits<k_addr, 19, 1, TrValue>;
    using Tr20 = Bits<k_addr, 20, 1, TrValue>;
    using Tr21 = Bits<k_addr, 21, 1, TrValue>;
    using Tr22 = Bits<k_addr, 22, 1, TrValue>;
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

    using Swier0 = Bits<k_addr, 0, 1, SwierValue>;
    using Swier1 = Bits<k_addr, 1, 1, SwierValue>;
    using Swier2 = Bits<k_addr, 2, 1, SwierValue>;
    using Swier3 = Bits<k_addr, 3, 1, SwierValue>;
    using Swier4 = Bits<k_addr, 4, 1, SwierValue>;
    using Swier5 = Bits<k_addr, 5, 1, SwierValue>;
    using Swier6 = Bits<k_addr, 6, 1, SwierValue>;
    using Swier7 = Bits<k_addr, 7, 1, SwierValue>;
    using Swier8 = Bits<k_addr, 8, 1, SwierValue>;
    using Swier9 = Bits<k_addr, 9, 1, SwierValue>;
    using Swier10 = Bits<k_addr, 10, 1, SwierValue>;
    using Swier11 = Bits<k_addr, 11, 1, SwierValue>;
    using Swier12 = Bits<k_addr, 12, 1, SwierValue>;
    using Swier13 = Bits<k_addr, 13, 1, SwierValue>;
    using Swier14 = Bits<k_addr, 14, 1, SwierValue>;
    using Swier15 = Bits<k_addr, 15, 1, SwierValue>;
    using Swier16 = Bits<k_addr, 16, 1, SwierValue>;
    using Swier17 = Bits<k_addr, 17, 1, SwierValue>;
    using Swier18 = Bits<k_addr, 18, 1, SwierValue>;
    using Swier19 = Bits<k_addr, 19, 1, SwierValue>;
    using Swier20 = Bits<k_addr, 20, 1, SwierValue>;
    using Swier21 = Bits<k_addr, 21, 1, SwierValue>;
    using Swier22 = Bits<k_addr, 22, 1, SwierValue>;
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

    using Pr0 = Bits<k_addr, 0, 1, PrValue>;
    using Pr1 = Bits<k_addr, 1, 1, PrValue>;
    using Pr2 = Bits<k_addr, 2, 1, PrValue>;
    using Pr3 = Bits<k_addr, 3, 1, PrValue>;
    using Pr4 = Bits<k_addr, 4, 1, PrValue>;
    using Pr5 = Bits<k_addr, 5, 1, PrValue>;
    using Pr6 = Bits<k_addr, 6, 1, PrValue>;
    using Pr7 = Bits<k_addr, 7, 1, PrValue>;
    using Pr8 = Bits<k_addr, 8, 1, PrValue>;
    using Pr9 = Bits<k_addr, 9, 1, PrValue>;
    using Pr10 = Bits<k_addr, 10, 1, PrValue>;
    using Pr11 = Bits<k_addr, 11, 1, PrValue>;
    using Pr12 = Bits<k_addr, 12, 1, PrValue>;
    using Pr13 = Bits<k_addr, 13, 1, PrValue>;
    using Pr14 = Bits<k_addr, 14, 1, PrValue>;
    using Pr15 = Bits<k_addr, 15, 1, PrValue>;
    using Pr16 = Bits<k_addr, 16, 1, PrValue>;
    using Pr17 = Bits<k_addr, 17, 1, PrValue>;
    using Pr18 = Bits<k_addr, 18, 1, PrValue>;
    using Pr19 = Bits<k_addr, 19, 1, PrValue>;
    using Pr20 = Bits<k_addr, 20, 1, PrValue>;
    using Pr21 = Bits<k_addr, 21, 1, PrValue>;
    using Pr22 = Bits<k_addr, 22, 1, PrValue>;
} // namespace Apb2::Exti::Pr
