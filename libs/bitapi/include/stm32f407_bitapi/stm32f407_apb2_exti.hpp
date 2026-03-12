#pragma once

#include "stm32f407_apb2.hpp"

#include <cassert>

// EXTernal Interrupt controller.
namespace Stm32f407::Bitapi::Apb2::Exti
{
    static constexpr Common::Address k_addr = Apb2::k_addr + 0x3C00U;

    static constexpr int k_lineCount = 23;

    // GPIO pin number.
    enum class LineNumber : unsigned int
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
    enum class MrValue : Common::Word
    {
        Masked = 0,
        NotMasked = 1
    };

    // Trigger selection value.
    enum class TrValue : Common::Word
    {
        TriggerDisabled = 0,
        TriggerEnabled = 1
    };
} // namespace Stm32f407::Bitapi::Apb2::Exti

// EXTI Interrupt Mask Register
namespace Stm32f407::Bitapi::Apb2::Exti::Imr
{
    using Bits = Util::BitsRegister<k_addr, 0x00, LineNumber, 1, MrValue>;

    using Mr0 = Util::Bits<Bits::k_addr, 0, 1, MrValue>;
    using Mr1 = Util::Bits<Bits::k_addr, 1, 1, MrValue>;
    using Mr2 = Util::Bits<Bits::k_addr, 2, 1, MrValue>;
    using Mr3 = Util::Bits<Bits::k_addr, 3, 1, MrValue>;
    using Mr4 = Util::Bits<Bits::k_addr, 4, 1, MrValue>;
    using Mr5 = Util::Bits<Bits::k_addr, 5, 1, MrValue>;
    using Mr6 = Util::Bits<Bits::k_addr, 6, 1, MrValue>;
    using Mr7 = Util::Bits<Bits::k_addr, 7, 1, MrValue>;
    using Mr8 = Util::Bits<Bits::k_addr, 8, 1, MrValue>;
    using Mr9 = Util::Bits<Bits::k_addr, 9, 1, MrValue>;
    using Mr10 = Util::Bits<Bits::k_addr, 10, 1, MrValue>;
    using Mr11 = Util::Bits<Bits::k_addr, 11, 1, MrValue>;
    using Mr12 = Util::Bits<Bits::k_addr, 12, 1, MrValue>;
    using Mr13 = Util::Bits<Bits::k_addr, 13, 1, MrValue>;
    using Mr14 = Util::Bits<Bits::k_addr, 14, 1, MrValue>;
    using Mr15 = Util::Bits<Bits::k_addr, 15, 1, MrValue>;
    using Mr16 = Util::Bits<Bits::k_addr, 16, 1, MrValue>;
    using Mr17 = Util::Bits<Bits::k_addr, 17, 1, MrValue>;
    using Mr18 = Util::Bits<Bits::k_addr, 18, 1, MrValue>;
    using Mr19 = Util::Bits<Bits::k_addr, 19, 1, MrValue>;
    using Mr20 = Util::Bits<Bits::k_addr, 20, 1, MrValue>;
    using Mr21 = Util::Bits<Bits::k_addr, 21, 1, MrValue>;
    using Mr22 = Util::Bits<Bits::k_addr, 22, 1, MrValue>;
} // namespace Stm32f407::Bitapi::Apb2::Exti::Imr

// EXTI Event Mask Register
namespace Stm32f407::Bitapi::Apb2::Exti::Emr
{
    using Bits = Util::BitsRegister<k_addr, 0x04, LineNumber, 1, MrValue>;

    using Mr0 = Util::Bits<Bits::k_addr, 0, 1, MrValue>;
    using Mr1 = Util::Bits<Bits::k_addr, 1, 1, MrValue>;
    using Mr2 = Util::Bits<Bits::k_addr, 2, 1, MrValue>;
    using Mr3 = Util::Bits<Bits::k_addr, 3, 1, MrValue>;
    using Mr4 = Util::Bits<Bits::k_addr, 4, 1, MrValue>;
    using Mr5 = Util::Bits<Bits::k_addr, 5, 1, MrValue>;
    using Mr6 = Util::Bits<Bits::k_addr, 6, 1, MrValue>;
    using Mr7 = Util::Bits<Bits::k_addr, 7, 1, MrValue>;
    using Mr8 = Util::Bits<Bits::k_addr, 8, 1, MrValue>;
    using Mr9 = Util::Bits<Bits::k_addr, 9, 1, MrValue>;
    using Mr10 = Util::Bits<Bits::k_addr, 10, 1, MrValue>;
    using Mr11 = Util::Bits<Bits::k_addr, 11, 1, MrValue>;
    using Mr12 = Util::Bits<Bits::k_addr, 12, 1, MrValue>;
    using Mr13 = Util::Bits<Bits::k_addr, 13, 1, MrValue>;
    using Mr14 = Util::Bits<Bits::k_addr, 14, 1, MrValue>;
    using Mr15 = Util::Bits<Bits::k_addr, 15, 1, MrValue>;
    using Mr16 = Util::Bits<Bits::k_addr, 16, 1, MrValue>;
    using Mr17 = Util::Bits<Bits::k_addr, 17, 1, MrValue>;
    using Mr18 = Util::Bits<Bits::k_addr, 18, 1, MrValue>;
    using Mr19 = Util::Bits<Bits::k_addr, 19, 1, MrValue>;
    using Mr20 = Util::Bits<Bits::k_addr, 20, 1, MrValue>;
    using Mr21 = Util::Bits<Bits::k_addr, 21, 1, MrValue>;
    using Mr22 = Util::Bits<Bits::k_addr, 22, 1, MrValue>;
} // namespace Stm32f407::Bitapi::Apb2::Exti::Emr

// EXTI Rising Trigger Selection Register
namespace Stm32f407::Bitapi::Apb2::Exti::Rtsr
{
    using Bits = Util::BitsRegister<k_addr, 0x08, LineNumber, 1, TrValue>;

    using Tr0 = Util::Bits<Bits::k_addr, 0, 1, TrValue>;
    using Tr1 = Util::Bits<Bits::k_addr, 1, 1, TrValue>;
    using Tr2 = Util::Bits<Bits::k_addr, 2, 1, TrValue>;
    using Tr3 = Util::Bits<Bits::k_addr, 3, 1, TrValue>;
    using Tr4 = Util::Bits<Bits::k_addr, 4, 1, TrValue>;
    using Tr5 = Util::Bits<Bits::k_addr, 5, 1, TrValue>;
    using Tr6 = Util::Bits<Bits::k_addr, 6, 1, TrValue>;
    using Tr7 = Util::Bits<Bits::k_addr, 7, 1, TrValue>;
    using Tr8 = Util::Bits<Bits::k_addr, 8, 1, TrValue>;
    using Tr9 = Util::Bits<Bits::k_addr, 9, 1, TrValue>;
    using Tr10 = Util::Bits<Bits::k_addr, 10, 1, TrValue>;
    using Tr11 = Util::Bits<Bits::k_addr, 11, 1, TrValue>;
    using Tr12 = Util::Bits<Bits::k_addr, 12, 1, TrValue>;
    using Tr13 = Util::Bits<Bits::k_addr, 13, 1, TrValue>;
    using Tr14 = Util::Bits<Bits::k_addr, 14, 1, TrValue>;
    using Tr15 = Util::Bits<Bits::k_addr, 15, 1, TrValue>;
    using Tr16 = Util::Bits<Bits::k_addr, 16, 1, TrValue>;
    using Tr17 = Util::Bits<Bits::k_addr, 17, 1, TrValue>;
    using Tr18 = Util::Bits<Bits::k_addr, 18, 1, TrValue>;
    using Tr19 = Util::Bits<Bits::k_addr, 19, 1, TrValue>;
    using Tr20 = Util::Bits<Bits::k_addr, 20, 1, TrValue>;
    using Tr21 = Util::Bits<Bits::k_addr, 21, 1, TrValue>;
    using Tr22 = Util::Bits<Bits::k_addr, 22, 1, TrValue>;
} // namespace Stm32f407::Bitapi::Apb2::Exti::Rtsr

// EXTI Falling Trigger Selection Register
namespace Stm32f407::Bitapi::Apb2::Exti::Ftsr
{
    using Bits = Util::BitsRegister<k_addr, 0x0c, LineNumber, 1, TrValue>;

    using Tr0 = Util::Bits<Bits::k_addr, 0, 1, TrValue>;
    using Tr1 = Util::Bits<Bits::k_addr, 1, 1, TrValue>;
    using Tr2 = Util::Bits<Bits::k_addr, 2, 1, TrValue>;
    using Tr3 = Util::Bits<Bits::k_addr, 3, 1, TrValue>;
    using Tr4 = Util::Bits<Bits::k_addr, 4, 1, TrValue>;
    using Tr5 = Util::Bits<Bits::k_addr, 5, 1, TrValue>;
    using Tr6 = Util::Bits<Bits::k_addr, 6, 1, TrValue>;
    using Tr7 = Util::Bits<Bits::k_addr, 7, 1, TrValue>;
    using Tr8 = Util::Bits<Bits::k_addr, 8, 1, TrValue>;
    using Tr9 = Util::Bits<Bits::k_addr, 9, 1, TrValue>;
    using Tr10 = Util::Bits<Bits::k_addr, 10, 1, TrValue>;
    using Tr11 = Util::Bits<Bits::k_addr, 11, 1, TrValue>;
    using Tr12 = Util::Bits<Bits::k_addr, 12, 1, TrValue>;
    using Tr13 = Util::Bits<Bits::k_addr, 13, 1, TrValue>;
    using Tr14 = Util::Bits<Bits::k_addr, 14, 1, TrValue>;
    using Tr15 = Util::Bits<Bits::k_addr, 15, 1, TrValue>;
    using Tr16 = Util::Bits<Bits::k_addr, 16, 1, TrValue>;
    using Tr17 = Util::Bits<Bits::k_addr, 17, 1, TrValue>;
    using Tr18 = Util::Bits<Bits::k_addr, 18, 1, TrValue>;
    using Tr19 = Util::Bits<Bits::k_addr, 19, 1, TrValue>;
    using Tr20 = Util::Bits<Bits::k_addr, 20, 1, TrValue>;
    using Tr21 = Util::Bits<Bits::k_addr, 21, 1, TrValue>;
    using Tr22 = Util::Bits<Bits::k_addr, 22, 1, TrValue>;
} // namespace Stm32f407::Bitapi::Apb2::Exti::Ftsr

// EXTI Software Interrupt Event Register
//
// If interrupts are enabled on line x in the EXTI_IMR register, writing '1' to SWIERx bit when it is
// set at '0' sets the corresponding pending bit in the EXTI_PR register, thus resulting in an
// interrupt request generation.
// This bit is cleared by clearing the corresponding bit in EXTI_PR (by writing a 1 to the bit).
namespace Stm32f407::Bitapi::Apb2::Exti::Swier
{
    // Software Interrupt Event Register value.
    enum class SwierValue : Common::Word
    {
        TriggerInterrupt = 1
    };

    using Bits = Util::BitsRegister<k_addr, 0x10, LineNumber, 1, SwierValue>;

    using Swier0 = Util::Bits<Bits::k_addr, 0, 1, SwierValue>;
    using Swier1 = Util::Bits<Bits::k_addr, 1, 1, SwierValue>;
    using Swier2 = Util::Bits<Bits::k_addr, 2, 1, SwierValue>;
    using Swier3 = Util::Bits<Bits::k_addr, 3, 1, SwierValue>;
    using Swier4 = Util::Bits<Bits::k_addr, 4, 1, SwierValue>;
    using Swier5 = Util::Bits<Bits::k_addr, 5, 1, SwierValue>;
    using Swier6 = Util::Bits<Bits::k_addr, 6, 1, SwierValue>;
    using Swier7 = Util::Bits<Bits::k_addr, 7, 1, SwierValue>;
    using Swier8 = Util::Bits<Bits::k_addr, 8, 1, SwierValue>;
    using Swier9 = Util::Bits<Bits::k_addr, 9, 1, SwierValue>;
    using Swier10 = Util::Bits<Bits::k_addr, 10, 1, SwierValue>;
    using Swier11 = Util::Bits<Bits::k_addr, 11, 1, SwierValue>;
    using Swier12 = Util::Bits<Bits::k_addr, 12, 1, SwierValue>;
    using Swier13 = Util::Bits<Bits::k_addr, 13, 1, SwierValue>;
    using Swier14 = Util::Bits<Bits::k_addr, 14, 1, SwierValue>;
    using Swier15 = Util::Bits<Bits::k_addr, 15, 1, SwierValue>;
    using Swier16 = Util::Bits<Bits::k_addr, 16, 1, SwierValue>;
    using Swier17 = Util::Bits<Bits::k_addr, 17, 1, SwierValue>;
    using Swier18 = Util::Bits<Bits::k_addr, 18, 1, SwierValue>;
    using Swier19 = Util::Bits<Bits::k_addr, 19, 1, SwierValue>;
    using Swier20 = Util::Bits<Bits::k_addr, 20, 1, SwierValue>;
    using Swier21 = Util::Bits<Bits::k_addr, 21, 1, SwierValue>;
    using Swier22 = Util::Bits<Bits::k_addr, 22, 1, SwierValue>;
} // namespace Stm32f407::Bitapi::Apb2::Exti::Swier

// EXTI Pending Register
//
// 0: No trigger request occurred
// 1: selected trigger request occurred
// This bit is set when the selected edge event arrives on the external interrupt line.
// This bit is cleared by programming it to ‘1’.
namespace Stm32f407::Bitapi::Apb2::Exti::Pr
{
    // Pending Register value.
    enum class PrRead : Common::Word
    {
        NotPending = 0,
        Pending = 1,
    };

    // Pending Register value.
    enum class PrWrite : Common::Word
    {
        Clear = 1,
    };

    using Bits = Util::BitsRegister<k_addr, 0x14, LineNumber, 1, PrRead, PrWrite>;

    using Pr0 = Util::Bits<Bits::k_addr, 0, 1, PrRead, PrWrite>;
    using Pr1 = Util::Bits<Bits::k_addr, 1, 1, PrRead, PrWrite>;
    using Pr2 = Util::Bits<Bits::k_addr, 2, 1, PrRead, PrWrite>;
    using Pr3 = Util::Bits<Bits::k_addr, 3, 1, PrRead, PrWrite>;
    using Pr4 = Util::Bits<Bits::k_addr, 4, 1, PrRead, PrWrite>;
    using Pr5 = Util::Bits<Bits::k_addr, 5, 1, PrRead, PrWrite>;
    using Pr6 = Util::Bits<Bits::k_addr, 6, 1, PrRead, PrWrite>;
    using Pr7 = Util::Bits<Bits::k_addr, 7, 1, PrRead, PrWrite>;
    using Pr8 = Util::Bits<Bits::k_addr, 8, 1, PrRead, PrWrite>;
    using Pr9 = Util::Bits<Bits::k_addr, 9, 1, PrRead, PrWrite>;
    using Pr10 = Util::Bits<Bits::k_addr, 10, 1, PrRead, PrWrite>;
    using Pr11 = Util::Bits<Bits::k_addr, 11, 1, PrRead, PrWrite>;
    using Pr12 = Util::Bits<Bits::k_addr, 12, 1, PrRead, PrWrite>;
    using Pr13 = Util::Bits<Bits::k_addr, 13, 1, PrRead, PrWrite>;
    using Pr14 = Util::Bits<Bits::k_addr, 14, 1, PrRead, PrWrite>;
    using Pr15 = Util::Bits<Bits::k_addr, 15, 1, PrRead, PrWrite>;
    using Pr16 = Util::Bits<Bits::k_addr, 16, 1, PrRead, PrWrite>;
    using Pr17 = Util::Bits<Bits::k_addr, 17, 1, PrRead, PrWrite>;
    using Pr18 = Util::Bits<Bits::k_addr, 18, 1, PrRead, PrWrite>;
    using Pr19 = Util::Bits<Bits::k_addr, 19, 1, PrRead, PrWrite>;
    using Pr20 = Util::Bits<Bits::k_addr, 20, 1, PrRead, PrWrite>;
    using Pr21 = Util::Bits<Bits::k_addr, 21, 1, PrRead, PrWrite>;
    using Pr22 = Util::Bits<Bits::k_addr, 22, 1, PrRead, PrWrite>;
} // namespace Stm32f407::Bitapi::Apb2::Exti::Pr
