#ifndef SOFTWARE_SERIAL_H
#define SOFTWARE_SERIAL_H

#define UART_BAUDRATE_BT_SERIAL 115200
#define UART_BAUDRATE_SERIAL_USB 9600
#define NO_PACKAGE -1

// transmitter input pins
#define TURN_PIN A3     // joystick 2 L/R
#define THROTTLE_PIN A2 // joystick 1 U/D
#define INTERRUPT_PIN 2
#define AUTO_PIN 5
#define EBRAKE_PIN 4
#define REVERSE_PIN 20
#define RX_PIN 6 // Change according to the board
#define TX_PIN 7 // Change according to the board
#define DEBUG 1  // Prints debugging info to serialUSB, can impact loop time                         \
                      // WARNING: when true (!0), you must connect USB to allow hardware reset, otherwise \
                      // SAMD21 Arduino will do nothing*/

#define TX_LED_LINK 6 // LED pins on the transmitter

// other outputs
#define SS_PIN 10
/* pins 11 - 13 are reserved for SPI */

// The encryption key has to be the same for transmitter and receiver
uint8_t key[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};

typedef struct
{
    unsigned int throttle;
    unsigned int turn;
    unsigned char ebrake;
    unsigned char autonomous;
} dataFromTransmitter;

#endif
