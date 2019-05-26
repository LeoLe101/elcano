#define UART_BAUDRATE 9600
#define BUFFER_LIMIT 17
#define ACK_LIMIT 5

// transmitter input pins
#define TURN_PIN A3     // joystick 2 L/R
#define THROTTLE_PIN A2 // joystick 1 U/D
#define INTERRUPT_PIN 2
#define AUTO_PIN 5
#define EBRAKE_PIN 4
#define REVERSE_PIN 20
#define RX_PIN 6      // Change according to the board
#define TX_PIN 7      // Change according to the board
#define DEBUG 1       // Prints debugging info to serialUSB, can impact loop time                         \
                      // WARNING: when true (!0), you must connect USB to allow hardware reset, otherwise \
                      // SAMD21 Arduino will do nothing*/

#define TX_LED_LINK 6 // LED pins on the transmitter

// other outputs
#define SS_PIN 10
/* pins 11 - 13 are reserved for SPI */


typedef struct
{
    unsigned int throttle;
    unsigned int turn;
    bool ebrake;
    bool autonomous;
    bool reverse; // Future Stuff
} dataFromTransmitter;
