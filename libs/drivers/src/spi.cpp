#include "stm32f407_drivers/spi.hpp"

#include <stm32f407_bitapi/stm32f407_common_spi.hpp>

namespace Stm32f407::Driver::detail
{
    std::array<IrqHandler, Bitapi::Common::Spi::k_spiCount> g_spiIrqHandlers;

    void spiIrqHandler(unsigned int spiNumber)
    {
        // TODO: Clear the pending interrupt flag ????

        // Call the registered handler.
        auto& handler = g_spiIrqHandlers[spiNumber - 1];
        if (handler != nullptr)
        {
            handler();
        }
    }
} // namespace Stm32f407::Driver::detail
