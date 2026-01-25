#include "clocks.hpp"
#include "Src/bitapi/stm32f407_ahb1_rcc.hpp"
#include "Src/bitapi/stm32f407_clocks.hpp"
#include "Src/bitapi/stm32f407_utils.hpp"

namespace Stm32Clocks = Stm32f407::Bitapi::Clocks;

using namespace Stm32f407;

namespace Stm32f407::Driver::detail
{
    void sysTickHandler()
    {
        // TODO
    }
} // namespace Stm32f407::Driver::detail

namespace Stm32f407::Driver::Clocks
{
    void initClocks()
    {
        // Configure AHB1 prescaler.
        Bitapi::Ahb1::Rcc::Cfgr::HPre::set(Bitapi::Ahb1::Rcc::Cfgr::intToHPre(Stm32Clocks::k_ahbPrescaler));

        // Configure APB1 prescaler.
        Bitapi::Ahb1::Rcc::Cfgr::PPre1::set(Bitapi::Ahb1::Rcc::Cfgr::intToPPre(Stm32Clocks::k_apb1Prescaler));

        // Configure APB2 prescaler.
        Bitapi::Ahb1::Rcc::Cfgr::PPre2::set(Bitapi::Ahb1::Rcc::Cfgr::intToPPre(Stm32Clocks::k_apb2Prescaler));

        // Configure HSI.
        Bitapi::Ahb1::Rcc::Cr::HsiOn::set(Bitapi::Common::OffOn::On);
        while (Bitapi::Ahb1::Rcc::Cr::HsiRdy::get() != Bitapi::Common::ReadyFlag::Ready)
        {
            // Wait for HSI to become ready.
        }

        // Configure HSE.
        if (Stm32Clocks::getHseHz() == 0)
        {
            Bitapi::Ahb1::Rcc::Cr::HseOn::set(Bitapi::Common::OffOn::Off);
            while (Bitapi::Ahb1::Rcc::Cr::HseRdy::get() == Bitapi::Common::ReadyFlag::Ready)
            {
                // Wait for HSI to become not ready.
            }
        }
        else
        {
            Bitapi::Ahb1::Rcc::Cr::HseOn::set(Bitapi::Common::OffOn::On);
            while (Bitapi::Ahb1::Rcc::Cr::HseRdy::get() != Bitapi::Common::ReadyFlag::Ready)
            {
                // Wait for HSI to become ready.
            }
        }

        // Configure SysClk source.
        switch (Stm32Clocks::k_sysClkSrc)
        {
        case Stm32Clocks::SysClkSrc::HsiRc:
            Bitapi::Ahb1::Rcc::Cfgr::Sw::set(Bitapi::Ahb1::Rcc::Cfgr::SwValue::Hsi);
            break;
        case Stm32Clocks::SysClkSrc::Hse:
            Bitapi::Ahb1::Rcc::Cfgr::Sw::set(Bitapi::Ahb1::Rcc::Cfgr::SwValue::Hse);
            break;
        case Stm32Clocks::SysClkSrc::PllClk:
            Bitapi::Ahb1::Rcc::Cfgr::Sw::set(Bitapi::Ahb1::Rcc::Cfgr::SwValue::Pll);
            break;
        }
    }
} // namespace Stm32f407::Driver::Clocks
