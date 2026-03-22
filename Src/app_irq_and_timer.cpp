#include <stm32f407_bitapi/stm32f407_ahb1_rcc.hpp>
#include <stm32f407_bitapi/stm32f407_utils.hpp>
#include <stm32f407_drivers/clocks.hpp>
#include <stm32f407_drivers/gpio.hpp>
#include <stm32f407_drivers/spi.hpp>
#include <stm32f407_drivers/timer.hpp>
#include <stm32f407_drivers/util.hpp>

#include <cstdint>
#include <cstdio>

using namespace Stm32f407::Driver;
// using namespace Stm32f407;

namespace
{
    void configureMco(GpioA& gpioA, GpioC& gpioC)
    {
        // Should see 4 Mhz at MCO1 -> PA8
        Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1Pre::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1PreValue::Four);
        Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1Value::Hsi);

        // Should see 4 Mhz at MCO2 -> PC9
        Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2Pre::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2PreValue::Four);
        Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2Value::SysClk);

        auto& pinA8 = gpioA.pin8();
        pinA8.setMode(GpioMode::AltFunc);
        pinA8.setAltFunc(GpioAltFuncA8::Af0_Mco1);

        auto& pinC9 = gpioC.pin9();
        pinC9.setMode(GpioMode::AltFunc);
        pinC9.setAltFunc(GpioAltFuncC9::Af0_Mco2);
    }

} // namespace

int app_irq_and_timer()
{
    Clocks::initClocks();

    auto gpioA = GpioA{};
    auto gpioC = GpioC{};
    auto gpioD = GpioD{};
    auto tim2 = Tim2{};

    configureMco(gpioA, gpioC);

    // printf("Hello Wordl!\n");
    auto& greenLed = gpioD.pin12();
    greenLed.setMode(GpioMode::Output);
    greenLed.setOutputType(GpioOutputType::PushPull);
    greenLed.setOutputSpeed(GpioOutputSpeed::Low);
    greenLed.setPupd(GpioPupd::NoPull);

    tim2.setDirection(TimerDirection::Upcounter);
    tim2.setPeriod(30);
    tim2.setPrescaler(0);
    tim2.setOneShot(true);

    // When the button (PA0) is released, toggle the LED (PD12).
    auto& blueButton = gpioA.pin0();
    blueButton.configureInterrupt(GpioInterruptMode::FallingEdge, GpioPupd::NoPull, IrqPriority::Priority0,
            [&]()
            {
                // Debounce with a timer.
                tim2.restart();
            });
    tim2.enableInterrupt(IrqPriority::Priority0,
            [&]()
            {
                // Make sure we toggle only when the button is in released state.
                if (blueButton.readInput() == Stm32f407::Bitapi::Common::PinState::Low)
                {
                    greenLed.toggleOutput();
                }
            });

    while (true)
    {
    }

    return 0;
}
