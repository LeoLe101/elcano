#include "BluetoothControlRx.h"
Hello world
// initialize package and variables
dataFromTransmitter receiverDat;
// Utilities variables
unsigned long currTime = 0;
int counter = 0;
// Data/Buffer variables
String logger;
char dataBuffer[BUFFER_LIMIT];
char ackBuffer[ACK_LIMIT];
char dataChar;

void setup()
{
    // Init hardware serial port --> PIN: 0 (RX) | 1 (TX)
    Serial1.begin(UART_BAUDRATE);
    SerialUSB.begin(UART_BAUDRATE); // Serial Monitor

    if (DEBUG)
        // wait until SerialUSB initialize
        while (!SerialUSB)
            ;

    logger = "ACK@";
    logger.toCharArray(ackBuffer, ACK_LIMIT);
    String initMesg = "** RecX Init at " + String(UART_BAUDRATE);
    SerialUSB.println(initMesg);
    SerialUSB.println("Setup Complete!");
}

void loop()
{
    // Checks whether data is comming from the serial port
    while (Serial1.available() > 0)
    {
        processComingData();
    }
   ackMessage();
}

/**
 * --------------------- Helper Functions --------------------------------
 */

// Gather/Process data and put it into dataBuffer buffer for parsing
void processComingData()
{
    dataChar = Serial1.read(); // Reads the data from the serial port
    if (dataChar == '@')
    {
        // End of this data reached! Parsing process start
        dataParser(dataBuffer);
        counter = 0;
        dataBuffer[counter] = NULL;
    }
    else
    {
        dataBuffer[counter] = dataChar;
        counter++;
        dataBuffer[counter] = '\0'; // Keep the string NULL terminated
    }
}

// Parse the completed data buffer from the transmitter
void dataParser(char *dataRecv)
{
    SerialUSB.print("Parsing...");
    for (int i = 0; i < BUFFER_LIMIT; i++)
    {
        if (dataRecv[i] == '|')
        {
            // Skip this character
            SerialUSB.print(" -- ");
            continue;
        }
        else
            SerialUSB.print(dataRecv[i]);
    }
}

// ACKNOWLEDGE the data received
void ackMessage()
{
    SerialUSB.println();
    if (Serial1.available())
    {
        Serial1.print("ACK");
    }
}

// Better version of delay() in Arduino Lib
void waitForProcess(long interval)
{
    currTime = millis();
    while (millis() < currTime + interval)
    {
        ; // Wait for "interval" ms to ensure packages are received
    }
}
