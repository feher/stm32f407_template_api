#pragma once

#include <cstdint>
#include <type_traits>
#include <utility> // to_underlying

namespace Stm32f407::Bitapi::Common
{
    using Byte = std::uint8_t;
    using HalfWord = std::uint16_t;
    using Word = std::uint32_t;
    using Address = std::uint32_t;

    static constexpr unsigned int k_halfWordBits = 32;
    static constexpr unsigned int k_wordBits = 32;
    static constexpr unsigned int k_addressBits = 32;

    enum class NoYes : Word
    {
        No = 0,
        Yes = 1
    };

    enum class OffOn : Word
    {
        Off = 0,
        On = 1
    };

    enum class DiEn : Word
    {
        Disabled = 0,
        Enabled = 1
    };

    enum class EnDi : Word
    {
        Enabled = 0,
        Disabled = 1
    };

    enum class LeftRight : Word
    {
        Left = 0,
        Right = 1
    };

    enum class ResetBit : Word
    {
        NoReset = 0,
        Reset = 1
    };

    enum class ReadyFlag : Word
    {
        NotReady = 0,
        Ready = 1
    };

    enum class EmptyFlag : Word
    {
        NotEmpty = 0,
        Empty = 1
    };

    enum class NotEmptyFlag : Word
    {
        Empty = 0,
        NotEmpty = 1
    };

    enum class PinState : Word
    {
        Low = 0,
        High = 1
    };

    enum class ZeroClear : Word
    {
        Clear = 0
    };
} // namespace Stm32f407::Bitapi::Common

namespace Stm32f407::Bitapi::Util
{
    static inline Common::Word extract_bits(Common::Word bits, int bitPos, int bitCount)
    {
        const Common::Word valueMask = (Common::Word{1} << bitCount) - Common::Word{1};
        const Common::Word bitsMask = (valueMask << bitPos);
        return (bits & bitsMask) >> bitPos;
    }

    template <typename T>
    constexpr T extract_bits_as(Common::Word value, int bitPos, int bitCount)
    {
        const auto bits = extract_bits(value, bitPos, bitCount);
        return static_cast<T>(bits);
    }

    static inline Common::Word set_bits(Common::Word bits, int bitPos, int bitCount, Common::Word value)
    {
        const Common::Word valueMask = (Common::Word{1} << bitCount) - Common::Word{1};
        const Common::Word maskedValue = value & valueMask;
        const Common::Word bitsMask = ~(valueMask << bitPos);
        return (bits & bitsMask) | (maskedValue << bitPos);
    }

    template <typename T>
    Common::Word set_bits(Common::Word value, int bitPos, int bitCount, T bits)
    {
        return set_bits(value, bitPos, bitCount, static_cast<Common::Word>(bits));
    }

    // Read/Write Bits.
    template <Common::Address TVRegAddr, int TVBitPos, int TVBitCount, typename TRValue, typename TWValue = TRValue>
    struct Bits
    {
        static constexpr Common::Word k_regAddr = TVRegAddr;
        static constexpr int k_bitPos = TVBitPos;
        static constexpr int k_bitCount = TVBitCount;

        using ReadValue = TRValue;
        using WriteValue = TWValue;

        // Get the value of the bits.
        static TRValue get()
            requires(!std::is_void_v<TRValue>)
        {
            volatile Common::Word* ptr = reinterpret_cast<Common::Word*>(k_regAddr);
            return extract_bits_as<TRValue>(*ptr, k_bitPos, k_bitCount);
        }

        // Set the value of the bits.
        template <typename T, std::enable_if_t<!std::is_void_v<TWValue> && std::is_same_v<T, TWValue>, bool> = true>
        static void set(T value)
        {
            volatile Common::Word* ptr = reinterpret_cast<Common::Word*>(k_regAddr);
            *ptr = set_bits(*ptr, k_bitPos, k_bitCount, value);
        }
    };

    // Read-Only Bits.
    template <Common::Address TVRegAddr, int TVBitPos, int TVBitCount, typename TValue>
    struct RoBits : public Bits<TVRegAddr, TVBitPos, TVBitCount, TValue, void>
    {
    };

    // Write-Only Bits.
    template <Common::Address TVRegAddr, int TVBitPos, int TVBitCount, typename TValue>
    struct WoBits : public Bits<TVRegAddr, TVBitPos, TVBitCount, void, TValue>
    {
    };

    // Must be specialized for every enum type.
    template <typename TEnum>
    TEnum maxEnumValue()
    {
        static_assert(false, "maxEnumValue must be specialized for the enum type");
        return TEnum{};
    }

    // An array (block) of bit ranges indexed by an enum (TBitsEnum).
    // Every item in the array represents a bit range of TVBitCount bits.
    template <Common::Address TVBaseAddr, Common::Word TVOffset, typename TBitsEnum, Common::Word TVBitCount,
            typename TReadValue, typename TWriteValue = TReadValue>
    struct BitsRegister
    {
        static constexpr Common::Word k_offset = TVOffset;
        static constexpr Common::Address k_addr = TVBaseAddr + k_offset;

        template <typename T,
                std::enable_if_t<!std::is_void_v<TWriteValue> && std::is_same_v<T, TWriteValue>, bool> = true>
        static void set(TBitsEnum bitsNum, T value)
        {
            // We don't use to_underlying() because we want to support unsigned int as well, not just enums.
            const auto intBitsNum = static_cast<unsigned int>(bitsNum);
            // assert(intIrq < k_irqCount);
            const auto bitPos = intBitsNum * TVBitCount;
            const auto wordIndex = bitPos & ~(Common::k_wordBits - 1); // div by 32 bits
            const auto bitOffset = bitPos & (Common::k_wordBits - 1); // mod by 32 bits
            const auto wordOffset = wordIndex * sizeof(Common::Word); // mul by 4 bytes
            const auto addr = k_addr + wordOffset;
            volatile Common::Word* p = reinterpret_cast<Common::Word*>(addr);
            *p = set_bits(*p, bitOffset, TVBitCount, value);
        }

        static TReadValue get(TBitsEnum bitsNum)
            requires(!std::is_void_v<TReadValue>)
        {
            // We don't use to_underlying() because we want to support unsigned int as well, not just enums.
            const auto intBitsNum = static_cast<unsigned int>(bitsNum);
            // assert(intIrq && intIrq < k_irqCount);
            const auto bitPos = intBitsNum * TVBitCount;
            const auto wordIndex = bitPos & ~(Common::k_wordBits - 1); // div by 32 bits
            const auto bitOffset = bitPos & (Common::k_wordBits - 1); // mod by 32 bits
            const auto wordOffset = wordIndex * sizeof(Common::Word); // mul by 4 bytes
            const auto addr = k_addr + wordOffset;
            volatile Common::Word* p = reinterpret_cast<Common::Word*>(addr);
            return extract_bits_as<TReadValue>(*p, bitOffset, TVBitCount);
        }
    };

} // namespace Stm32f407::Bitapi::Util
