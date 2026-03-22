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

int app_blink_led()
{
    Clocks::initClocks();

    auto gpioA = GpioA{};
    auto gpioD = GpioD{};

    // printf("Hello Wordl!\n");
    auto& greenLed = gpioD.pin12();
    greenLed.setMode(GpioMode::Output);
    greenLed.setOutputType(GpioOutputType::PushPull);
    greenLed.setOutputSpeed(GpioOutputSpeed::Low);
    greenLed.setPupd(GpioPupd::NoPull);

    auto& pin0 = gpioA.pin0();
    pin0.setMode(GpioMode::Input);
    // pin0.setOutputType(GpioOutputType::PushPull);
    // pin0.setOutputSpeed(GpioOutputSpeed::Low);
    pin0.setPupd(GpioPupd::NoPull);

    while (true)
    {
        if (pin0.readInput() == Stm32f407::Bitapi::Common::PinState::High)
        {
            if (greenLed.readOutput() == Stm32f407::Bitapi::Common::PinState::Low)
            {
                greenLed.writeOutput(Stm32f407::Bitapi::Common::PinState::High);
            }
        }
        else
        {
            if (greenLed.readOutput() == Stm32f407::Bitapi::Common::PinState::High)
            {
                greenLed.writeOutput(Stm32f407::Bitapi::Common::PinState::Low);
            }
        }
    }

    return 0;
}
