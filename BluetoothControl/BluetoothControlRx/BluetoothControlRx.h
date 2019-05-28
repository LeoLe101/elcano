// Arduino Serial Port 
#define UART_BAUDRATE 38400 // The current TX has to be at 9600 Baurd rate so that the RX can read the data at 38400 Buard rate --- This is off, but it works for now.
#define BUFFER_LIMIT 18
#define ACK_LIMIT 5

// Arduino Debugger
#define NO_PACKAGE -1 // No package received
#define DEBUG 1       // Prints debugging info to serialUSB, can impact loop time                        
                      // WARNING: when true (!0), you must connect USB to allow hardware reset, otherwise
                      // SAMD21 Arduino will do nothing*/

// Data struct of packages being sent
typedef struct
{
    unsigned int throttle;
    unsigned int turn;
    bool ebrake;
    bool autonomous;
    bool reverse; // Future Stuff
} dataFromTransmitter;
