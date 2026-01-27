#include <cstdint>
#include <cstdio>

#include "Src/bitapi/stm32f407_ahb1_rcc.hpp"
#include "Src/bitapi/stm32f407_utils.hpp"
#include "drivers/clocks.hpp"
#include "drivers/gpio.hpp"
#include "drivers/spi.hpp"
#include "drivers/timer.hpp"
#include "drivers/util.hpp"

using namespace Stm32f407::Driver;
// using namespace Stm32f407;

void configureMco(GpioA& gpioA, GpioC& gpioC)
{
    // Should see 4 Mhz at MCO1 -> PA8
    Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1Pre::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1PreValue::Four);
    Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco1Value::Hsi);

    // Should see 4 Mhz at MCO2 -> PC9
    Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2Pre::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2PreValue::Four);
    Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2::set(Stm32f407::Bitapi::Ahb1::Rcc::Cfgr::Mco2Value::SysClk);

    auto& pinA8 = gpioA.pin8();
    pinA8.setAltFunc(GpioAltFuncA8::Af0_Mco1);
    pinA8.setMode(GpioMode::AltFunc);

    auto& pinC9 = gpioC.pin9();
    pinC9.setAltFunc(GpioAltFuncC9::Af0_Mco2);
    pinC9.setMode(GpioMode::AltFunc);
}

int main(void)
{
    Clocks::initClocks();

    auto gpioA = GpioA{};
    auto gpioB = GpioB{};
    auto gpioC = GpioC{};
    auto gpioD = GpioD{};
    auto tim2 = Tim2{};
    auto spi2 = Spi2{};

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
    tim2.enableInterrupt(
            [&]()
            {
                // Make sure we toggle only when the button is in released state.
                if (blueButton.readInput() == Stm32f407::Bitapi::Common::PinState::Low)
                {
                    greenLed.toggleOutput();
                }
            });

    gpioB.pin15().setAltFunc(GpioAltFuncB15::Af5_Spi2_Mosi_I2s2_Sd);
    spi2.setMode(SpiMode::Master);
    spi2.setBusMode(SpiBusMode::FullDuplex);
    spi2.setDataFrameFormat(SpiDataFrameFormat::Bits8);
    const auto data = std::array<Stm32f407::Bitapi::Common::Byte, 5>{'H', 'e', 'l', 'l', 'o'};
    spi2.send<Stm32f407::Bitapi::Common::Byte>(data);

    while (true)
    {
        // if (pin0.readInput() == Common::PinState::High)
        // {
        //     if (pin12.readOutput() == Common::PinState::Low)
        //     {
        //         pin12.writeOutput(Common::PinState::High);
        //     }
        // }
        // else
        // {
        //     if (pin12.readOutput() == Common::PinState::High)
        //     {
        //         pin12.writeOutput(Common::PinState::Low);
        //     }
        // }
    }
}
