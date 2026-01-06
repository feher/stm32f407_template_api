#pragma once

#include <cstdint>

using Word = std::uint32_t;
using Address = std::uint32_t;

enum class EnDi : Word
{
    Disabled = 0,
    Enabled = 1
};

enum class ResetBit : Word
{
    NoReset = 0,
    Reset = 1
};

enum class PinState : Word
{
    Low = 0,
    High = 1
};

static inline Word extract_bits(Word bits, int bitPos, int bitCount)
{
    const Word valueMask = (Word{1} << bitCount) - Word{1};
    const Word bitsMask = (valueMask << bitPos);
    return (bits & bitsMask) >> bitPos;
}

template <typename T>
constexpr T extract_bits_as(Word value, int bitPos, int bitCount)
{
    const auto bits = extract_bits(value, bitPos, bitCount);
    return static_cast<T>(bits);
}

static inline Word set_bits(Word bits, int bitPos, int bitCount, Word value)
{
    const Word valueMask = (Word{1} << bitCount) - Word{1};
    const Word maskedValue = value & valueMask;
    const Word bitsMask = ~(valueMask << bitPos);
    return (bits & bitsMask) | (maskedValue << bitPos);
}

template <typename T>
Word set_bits(Word value, int bitPos, int bitCount, T bits)
{
    return set_bits(value, bitPos, bitCount, static_cast<Word>(bits));
}

template <Address TVRegAddr, int TVBitPos, int TVBitCount>
struct BitsBase
{
    static constexpr Word k_regAddr = TVRegAddr;
    static constexpr int k_bitPos = TVBitPos;
    static constexpr int k_bitCount = TVBitCount;
};

template <typename TBitsBase, typename TValue>
struct BitsReadMixin
{
    // Get the value of the bits.
    static TValue get()
    {
        volatile Word* ptr = reinterpret_cast<Word*>(TBitsBase::k_regAddr);
        return extract_bits_as<TValue>(*ptr, TBitsBase::k_bitPos, TBitsBase::k_bitCount);
    }
};

template <typename TBitsBase, typename TValue>
struct BitsWriteMixin
{
    // Set the value of the bits.
    static void set(TValue value)
    {
        volatile Word* ptr = reinterpret_cast<Word*>(TBitsBase::k_regAddr);
        *ptr = set_bits(*ptr, TBitsBase::k_bitPos, TBitsBase::k_bitCount, value);
    }
};

// Read-Only Bits.
template <Address TVRegAddr, int TVBitPos, int TVBitCount, typename TValue>
struct RoBits : public BitsBase<TVRegAddr, TVBitPos, TVBitCount>,
                public BitsReadMixin<RoBits<TVRegAddr, TVBitPos, TVBitCount, TValue>, TValue>
{
};

// Write-Only Bits.
template <Address TVRegAddr, int TVBitPos, int TVBitCount, typename TValue>
struct WoBits : public BitsBase<TVRegAddr, TVBitPos, TVBitCount>,
                public BitsWriteMixin<WoBits<TVRegAddr, TVBitPos, TVBitCount, TValue>, TValue>
{
};

// Read/Write Bits.
template <Address TVRegAddr, int TVBitPos, int TVBitCount, typename TRValue, typename TWValue = TRValue>
struct Bits : public BitsBase<TVRegAddr, TVBitPos, TVBitCount>,
              public BitsReadMixin<Bits<TVRegAddr, TVBitPos, TVBitCount, TRValue, TWValue>, TRValue>,
              public BitsWriteMixin<Bits<TVRegAddr, TVBitPos, TVBitCount, TRValue, TWValue>, TWValue>
{
};
