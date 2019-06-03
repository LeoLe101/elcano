// Arduino Serial Port 
#define UART_BAUDRATE 38400
#define BUFFER_LIMIT 20
#define ACK_LIMIT 5

// Arduino Debugger
#define NO_PACKAGE -1 // No package received
#define DEBUG_PARSE 0 // This debug only for process coming data function
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
} receiverData;
