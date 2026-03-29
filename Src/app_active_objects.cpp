#include <active_object/active_object.hpp>

#include <stm32f407_bitapi/stm32f407_ahb1_rcc.hpp>
#include <stm32f407_bitapi/stm32f407_utils.hpp>
#include <stm32f407_drivers/clocks.hpp>
#include <stm32f407_drivers/gpio.hpp>
#include <stm32f407_drivers/spi.hpp>
#include <stm32f407_drivers/timer.hpp>
#include <stm32f407_drivers/util.hpp>

#include <cstdint>
#include <cstdio>
#include <string_view>
#include <span>
#include <optional>

using namespace Stm32f407::Driver;
// using namespace Stm32f407;

namespace
{
    void assertOrLoop(bool condition)
    {
        if (!condition)
        {
            while (true)
            {
            }
        }
    }

    bool isEqual(std::span<const Stm32f407::Bitapi::Common::Byte> data, std::string_view str)
    {
        for (auto i = 0u; i < data.size() && i < str.size(); ++i)
        {
            if (static_cast<char>(data[i]) != str[i])
            {
                return false;
            }
        }
        return true;
    }

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

    void configureSpi(GpioB& gpioB, Spi2& spi2)
    {
        auto& pinB12 = gpioB.pin12();
        auto& pinB13 = gpioB.pin13();
        auto& pinB14 = gpioB.pin14();
        auto& pinB15 = gpioB.pin15();

        pinB12.setMode(GpioMode::AltFunc);
        pinB12.setAltFunc(GpioAltFuncB12::Af5_Spi2_Nss_I2s2_Ws);
        pinB12.setOutputType(GpioOutputType::PushPull);
        pinB12.setPupd(GpioPupd::NoPull);
        pinB12.setOutputSpeed(GpioOutputSpeed::Medium);

        pinB13.setMode(GpioMode::AltFunc);
        pinB13.setAltFunc(GpioAltFuncB13::Af5_Spi2_Sck_I2s2_Ck);
        pinB13.setOutputType(GpioOutputType::PushPull);
        pinB13.setPupd(GpioPupd::NoPull);
        pinB13.setOutputSpeed(GpioOutputSpeed::Medium);

        pinB14.setMode(GpioMode::AltFunc);
        pinB14.setAltFunc(GpioAltFuncB14::Af5_Spi2_Miso);
        pinB14.setOutputType(GpioOutputType::PushPull);
        pinB14.setPupd(GpioPupd::NoPull);
        pinB14.setOutputSpeed(GpioOutputSpeed::Medium);

        pinB15.setMode(GpioMode::AltFunc);
        pinB15.setAltFunc(GpioAltFuncB15::Af5_Spi2_Mosi_I2s2_Sd);
        pinB15.setOutputType(GpioOutputType::PushPull);
        pinB15.setPupd(GpioPupd::NoPull);
        pinB15.setOutputSpeed(GpioOutputSpeed::Medium);

        spi2.setEnabled(false);
        spi2.setMode(SpiMode::Master);
        spi2.setBusMode(SpiBusMode::FullDuplex);
        spi2.setDataFrameFormat(SpiDataFrameFormat::Bits8);
        // The baud rate is important. If the master is too fast then the slave
        // may not be fast enough to consume the data. This may result in master
        // overwriting unconsumed data in the RX buffer of the slave.
        // For example, in my case ClkDiv4 was causing data corruption with
        // Arduino slave (arduino/spi_slave_cmd_handling/spi_slave_cmd_handling.ino).
        spi2.setBaudRateDiv(SpiBaudRateDiv::ClkDiv8);
        spi2.setClockPolarity(SpiClockPolarity::IdleLow);
        spi2.setClockPhase(SpiClockPhase::FirstEdge);
    }

    enum class Event
    {
        None,
        ButtonReleasedInterrupt,
        TimerTimeoutInterrupt,
        ButtonPressed,
    };

    class ButtonDebouncer : public Ao::ActiveObject<Event, 4>
    {
    public:
        ButtonDebouncer(GpioA& gpioA, Tim2& tim2) : m_gpioA{gpioA}, m_tim2{tim2}
        {
        }

    protected:
        void handleEvent(const Event& event) override
        {
            switch (event)
            {
            case Event::ButtonReleasedInterrupt:
                {
                    // Debounce with a timer.
                    m_tim2.restart();
                    break;
                }
            case Event::TimerTimeoutInterrupt:
                {
                    auto& blueButton = m_gpioA.pin0();
                    // Make sure we toggle only when the button is in released state.
                    if (blueButton.readInput() == Stm32f407::Bitapi::Common::PinState::Low)
                    {
                        send(Event::ButtonPressed);
                    }
                }
                break;
            default:
                break;
            }
        }

    private:
        GpioA& m_gpioA;
        Tim2& m_tim2;
    };

    class LedToggler : public Ao::ActiveObject<Event, 4>
    {
    public:
        explicit LedToggler(GpioD& gpioD) : m_gpioD{gpioD}
        {
        }

    protected:
        void handleEvent(const Event& event)
        {
            switch (event)
            {
            case Event::ButtonPressed:
                {
                    auto& greenLed = m_gpioD.pin12();
                    greenLed.toggleOutput();
                }
                break;
            default:
                break;
            }
        }

    private:
        GpioD& m_gpioD;
    };

    class SpiTester : public Ao::ActiveObject<Event, 4>
    {
    public:
        explicit SpiTester(Spi2& spi2) : m_spi2{spi2}
        {
        }

    protected:
        void handleEvent(const Event& event)
        {
            switch (event)
            {
            case Event::ButtonPressed:
                {
                    // The busyWait() calls are needed to make sure the slave is ready to
                    // receive or send data.
                    // Otherwise, the master may send too soon (i.e. it may overwrite unread data in the slave's RX buffer),
                    // or the master may receive too soon (i.e. it may pull zero/garbage data from the slave's TX buffer).
                    constexpr auto waitMs = 1u;
                    switch (m_state)
                    {
                    case State::SendIdReadCommand:
                        {
                            // Send command.
                            m_buffer[0] = 0x54;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive ACK.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(m_buffer[0] == 0xf5);

                            // Receive ID string.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 10));
                            assertOrLoop(isEqual(m_bufferSpan.subspan(0, 10), "ARDUINOUNO"));
                            m_state = State::SendLedReadCommand;
                            break;
                        }
                    case State::SendLedReadCommand:
                        {
                            // Send command.
                            m_buffer[0] = 0x52;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive ACK.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(m_buffer[0] == 0xf5);

                            // Send led pin number.
                            //Util::busyWait(waitMs);
                            constexpr auto pinNumber = 1;
                            m_buffer[0] = pinNumber;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive led state.
                            // Wait for the slave to write its data into its SPI TX buffer.
                            // Otherwise we may read too soon (whatever garbage the slave's TX buffer has).
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(!m_ledState.has_value() || m_buffer[0] == *m_ledState);
                            m_ledState = m_buffer[0];
                            m_state = State::SendLedControlCommand;
                            break;
                        }
                    case State::SendLedControlCommand:
                        {
                            // Send command.
                            m_buffer[0] = 0x50;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive ACK.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(m_buffer[0] == 0xf5);

                            // Send led pin number and state.
                            Util::busyWait(waitMs);
                            constexpr auto pinNumber = 1;
                            m_ledState = m_ledState.has_value() ? (1 - *m_ledState) : 1;
                            m_buffer[0] = pinNumber;
                            m_buffer[1] = *m_ledState;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 2));
                            m_state = State::SendSensorReadCommand;
                            break;
                        }
                    case State::SendSensorReadCommand:
                        {
                            // Send command.
                            m_buffer[0] = 0x51;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive ACK.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(m_buffer[0] == 0xf5);

                            // Send sensor pin number.
                            Util::busyWait(waitMs);
                            constexpr auto pinNumber = 1;
                            m_buffer[0] = pinNumber;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive sensor value.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(!m_sensorValue.has_value() || m_buffer[0] == *m_sensorValue + 1);
                            m_sensorValue = m_buffer[0];
                            m_state = State::SendPrintCommand;
                            break;
                        }
                    case State::SendPrintCommand:
                        {
                            // Send command.
                            m_buffer[0] = 0x53;
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));

                            // Receive ACK.
                            Util::busyWait(waitMs);
                            m_spi2.receiveFromSlave<Stm32f407::Bitapi::Common::Byte>(m_bufferSpan.subspan(0, 1));
                            assertOrLoop(m_buffer[0] == 0xf5);

                            // Send message.
                            Util::busyWait(waitMs);
                            m_spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(s_printMessage);
                            m_state = State::SendIdReadCommand;
                            break;
                        }
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }

    private:
        enum class State
        {
            SendIdReadCommand,
            SendPrintCommand,
            SendSensorReadCommand,
            SendLedReadCommand,
            SendLedControlCommand
        };

        static constexpr std::array<Stm32f407::Bitapi::Common::Byte, 6> s_printMessage{5, 'H', 'e', 'l', 'l', 'o'};

        std::array<Stm32f407::Bitapi::Common::Byte, 256> m_buffer{};
        std::span<Stm32f407::Bitapi::Common::Byte, 256> m_bufferSpan{m_buffer};
        std::optional<Stm32f407::Bitapi::Common::Byte> m_ledState;
        std::optional<Stm32f407::Bitapi::Common::Byte> m_sensorValue;
        State m_state = State::SendIdReadCommand;
        Spi2& m_spi2;
    };

} // namespace

int app_active_objects()
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

    ButtonDebouncer buttonDebouncer{gpioA, tim2};
    Ao::EventSender<Event> buttonInterruptSender;
    buttonInterruptSender.connect(&buttonDebouncer);
    Ao::EventSender<Event> timerInterruptSender;
    timerInterruptSender.connect(&buttonDebouncer);

    LedToggler ledToggler{gpioD};
    buttonDebouncer.connect(&ledToggler);
    SpiTester spiTester{spi2};
    buttonDebouncer.connect(&spiTester);

    // When the button (PA0) is released, toggle the LED (PD12).
    auto& blueButton = gpioA.pin0();
    blueButton.configureInterrupt(GpioInterruptMode::FallingEdge, GpioPupd::NoPull, IrqPriority::Priority1,
            [&]() { buttonInterruptSender.send(Event::ButtonReleasedInterrupt); });
    tim2.enableInterrupt(IrqPriority::Priority0, [&]() { timerInterruptSender.send(Event::TimerTimeoutInterrupt); });

    configureSpi(gpioB, spi2);
    spi2.setEnabled(true);

    while (true)
    {
        // spi2.sendToSlave<Stm32f407::Bitapi::Common::Byte>(data);

        // Util::busyWait(10);

        buttonDebouncer.step();
        ledToggler.step();
        spiTester.step();
    }

    return 0;
}
