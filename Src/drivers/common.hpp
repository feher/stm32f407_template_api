#pragma once

#include "Src/bitapi/stm32f407_core_nvic.hpp"

#include <functional>

namespace Stm32f407::Driver
{
    using IrqPriority = Bitapi::Core::Nvic::IprValue;
    using IrqHandler = std::function<void()>;
} // namespace Stm32f407::Driver
