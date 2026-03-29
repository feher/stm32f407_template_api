/*

 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select
 *

 */

#include <SPI.h>

const byte led = 9;  // Slave LED digital I/O pin.

#define DATABUFF_LEN 255
uint8_t dataBuff[DATABUFF_LEN];

uint8_t board_id[10] = "ARDUINOUNO";

#define NACK 0xA5
#define ACK 0xF5

//command codes
#define COMMAND_LED_CTRL 0x50
#define COMMAND_SENSOR_READ 0x51
#define COMMAND_LED_READ 0x52
#define COMMAND_PRINT 0x53
#define COMMAND_ID_READ 0x54

#define LED_ON 1
#define LED_OFF 0

//arduino analog pins
#define ANALOG_PIN0 0
#define ANALOG_PIN1 1
#define ANALOG_PIN2 2
#define ANALOG_PIN3 3
#define ANALOG_PIN4 4

// This is used only for testing, so we dont need to connect real sensors and LEDs to the Arduino.
struct FakeState
{
  uint8_t ledState = 1;
  uint8_t sensorValue = 1;
};
FakeState fakeState;

//Initialize SPI slave.
void SPI_SlaveInit(void) {
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  //make SPI as slave

  // Enable SPI as slave.
  // Bit 1:0 are SPR1-SPR0 SPI Clock Rate Select bits. The below table shows the SCK clock frequency select bit settings.
  // SPI2X	SPR1	SPR0	Clock frequency
  // 0      0     0     Fosc/4
  // 0      0     1     Fosc/16
  // 0      1     0     Fosc/64
  // 0      1     1     Fosc/128
  // 1      0     0     Fosc/2
  // 1      0     1     Fosc/8
  // 1      1     0     Fosc/32
  // 1      1     1     Fosc/64
  // Bit 2 is CPHA, Clock Phase Select bit.The Clock Polarity (CPOL) and Clock Phase (CPHA) bits define how serial data is transferred between the Master and the Slave.
  //                If the bit is set, then the data sample is on the trailing clock edge, and if it is clear, then the data sample is on the leading clock edge.
  // Bit 3 is CPOL, Clock Polarity Select bit. If set, clocks start from logic one, and if clear, the clock starts from logic zero.
  // Bit 4 is MSTR, Master/Slave Select bit. Set for Master mode and clear the bit for Slave mode.
  // Bit 5 is DORD, Data Order bit. If the bit is set, then it transmits LSB first. If the bit is clear, then MSB is transmitted first.
  // Bit 6 is SPE, SPI Enable bit. You need to set this bit high to enable the SPI.
  // Bit 7 is SPIE, SPI Interrupt Enable bit. You can enable SPI Interrupt by setting the bit high and disabling it by setting the bit low.
  SPCR = (1 << SPE);
}

//This function returns SPDR Contents
uint8_t SPI_SlaveReceive(void) {
  /* Wait for reception complete */
  while (!(SPSR & (1 << SPIF)))
    ;
  /* Return Data Register */
  return SPDR;
}


//sends one byte of data
void SPI_SlaveTransmit(uint8_t data) {
  /* Start transmission */
  SPDR = data;

  /* Wait for transmission complete */
  while (!(SPSR & (1 << SPIF)))
    ;
}


// The setup() function runs after reset.
void setup() {
  // Initialize serial for troubleshooting.
  Serial.begin(9600);

  // Initialize slave LED pin.
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  // Initialize SPI Slave.
  SPI_SlaveInit();

  Serial.println("Slave Initialized");
}


byte checkData(byte commnad) {
  //todo
  return ACK;
}

// The loop function runs continuously after setup().
void loop() {
  byte data, command, len, ackornack = NACK;

  //1. fist make sure that ss is low . so lets wait until ss is low
  Serial.println("Slave waiting for ss to go low");
  while (digitalRead(SS))
    ;

  //2. now lets wait until rx buffer has a byte
  command = SPI_SlaveReceive();
  ackornack = checkData(command);

  SPI_SlaveTransmit(ackornack);
  len = SPI_SlaveReceive();  //dummy byte

  if (command == COMMAND_LED_CTRL) {
    Serial.println("RCVD:COMMAND_LED_CTRL");
    //read 2 more bytes pin number and value
    uint8_t pin = SPI_SlaveReceive();
    uint8_t value = SPI_SlaveReceive();
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.print("value: ");
    Serial.println(value);
    fakeState.ledState = value;
    // if(value == (uint8_t)LED_ON)
    // {
    //   digitalWrite(pin,HIGH);
    // }else if (value == (uint8_t) LED_OFF)
    // {
    //   digitalWrite(pin,LOW);
    // }
    Serial.println("DONE:COMMAND_LED_CTRL");
  } else if (command == COMMAND_SENSOR_READ) {
    Serial.println("RCVD:COMMAND_SENSOR_READ");
    //read analog pin number
    uint16_t aread;
    uint8_t pin = SPI_SlaveReceive();
    //pinMode(pin+14, INPUT_PULLUP);
    uint8_t val;

    val = fakeState.sensorValue++;
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.print("val: ");
    Serial.println(val);

    // aread = analogRead(pin+14);
    // val = map(aread, 0, 1023, 0, 255);

    SPI_SlaveTransmit(val);
    val = SPI_SlaveReceive();  //dummy read
    Serial.println("DONE:COMMAND_SENSOR_READ");
  } else if (command == COMMAND_LED_READ) {
    Serial.println("RCVD:COMMAND_LED_READ");
    uint8_t pin = SPI_SlaveReceive();
    uint8_t val = fakeState.ledState;
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.print("val: ");
    Serial.println(val);
    // uint8_t val = digitalRead(pin);
    SPI_SlaveTransmit(val);
    val = SPI_SlaveReceive();  //dummy read
    Serial.println("DONE:COMMAND_LED_READ");
  } else if (command == COMMAND_PRINT) {
    Serial.println("RCVD:COMMAND_PRINT");
    uint8_t len = SPI_SlaveReceive();
    Serial.print("len: ");
    Serial.println(len);
    memset(dataBuff, 0, DATABUFF_LEN);
    for (int i = 0; i < len && i < (DATABUFF_LEN - 1); i++) {
      dataBuff[i] = SPI_SlaveReceive();
    }
    Serial.print("message: '");
    Serial.print((char*)dataBuff);
    Serial.println("'");
    Serial.println("DONE:COMMAND_PRINT");
  } else if (command == COMMAND_ID_READ) {
    Serial.println("RCVD:COMMAND_ID_READ");
    for (int i = 0; i < sizeof(board_id); i++) {
      SPI_SlaveTransmit(board_id[i]);
      SPI_SlaveReceive();
    }
    Serial.println("DONE:COMMAND_ID_READ");
  }
}
