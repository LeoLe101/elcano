#include "BluetoothControlRx.h"

// initialize package and variables
dataFromTransmitter rxData;

String btData = "";
bool received = true;
unsigned long currTime = 0;
const long interval = 10;

void setup()
{
    // @TODO: need to reconfigure pins for data received
    // pinMode(TURN_PIN, INPUT);
    // pinMode(THROTTLE_PIN, INPUT);
    // pinMode(AUTO_PIN, INPUT_PULLUP);
    // pinMode(EBRAKE_PIN, INPUT_PULLUP);
    // pinMode(TX_LED_LINK, OUTPUT);

    SerialUSB.begin(UART_BAUDRATE_SERIAL_USB);
    Serial1.begin(UART_BAUDRATE_SERIAL_USB); // Init hardware serial port --> PIN: 0 (RX) | 1 (TX)

    if (DEBUG)
        // wait until SerialUSB initialize
        while (!SerialUSB)
            ;

    String initMesg = "** RecX Init at " + String(UART_BAUDRATE_SERIAL_USB);
    SerialUSB.println(initMesg);
    SerialUSB.println("Setup Complete!");
}

void loop()
{
    processData();
    ackPackage();
}

/**
 * --------------------- Helper Functions --------------------------------
 */

// Read data from Bluetooth module
void processData()
{
    // If the data is sent to the monitor
    if (SerialUSB.available())
    {
        // While the data is available
        while (SerialUSB.available())
        {
            rxData.turn = SerialUSB.read();
            waitForProcess();
            rxData.throttle = SerialUSB.read();
            waitForProcess();
            rxData.autonomous = SerialUSB.read();
            waitForProcess();
            rxData.ebrake = SerialUSB.read();
        }
        waitForProcess();
        if (DEBUG)
        {
            logger("FIRST READ");
            btData = "turn (" + String(rxData.turn) + ")";
            logger(btData);
            btData = "throttle (" + String(rxData.throttle) + ")";
            logger(btData);
            btData = "Autonomous (" + String(rxData.autonomous) + ")";
            logger(btData);
            btData = "Ebrake (" + String(rxData.ebrake) + ")";
            logger(btData);
        }

        // Data is invalid! Return
        if (!validateData())
        {
            return;
        }

        // convert data Byte back to origin value (0-256 to 0-1023)
        rxData.turn = rxData.turn * 4;
        rxData.throttle = rxData.throttle * 4;

        if (DEBUG)
        {
            logger("AFTER NORMALIZED");
            btData = "turn (" + String(rxData.turn) + ")";
            logger(btData);
            btData = "throttle (" + String(rxData.throttle) + ")";
            logger(btData);
            btData = "Autonomous (" + String(rxData.autonomous) + ")";
            logger(btData);
            btData = "Ebrake (" + String(rxData.ebrake) + ")";
            logger(btData);
        }
    }
}

void ackPackage()
{
    // ACK package and send the mesg to the Bluetooh module (Send to PIN 1-TX)
    if (Serial1.available())
    {
        if (!received)
        {
            btData = "...No package received...";
            Serial1.print(btData);
            received = true; // reset received
        }
        else
        {
            btData = "Data -- " + String(rxData.throttle) + "," + String(rxData.turn);
            Serial1.print(btData);
        }
    }
}

bool validateData()
{
    if (DEBUG)
    {
        // In case no package received
        if (rxData.turn == NO_PACKAGE)
        {
            received = false;
        }
        else if (rxData.throttle == NO_PACKAGE)
        {
            received = false;
        }
        // else if (rxData.autonomous == NO_PACKAGE)
        // {
        //     received = false;
        // }
        // else if (rxData.ebrake == NO_PACKAGE)
        // {
        //     received = false;
        // }
        // Write back to the Transmitter (ACK package received) and normalize data
        else
        {
            // @TODO normalize and process the data here
            SerialUSB.print("Received: ");
            SerialUSB.println(btData);
        }
    }
    return received;
}

// Better version of delay() in Arduino Lib
void waitForProcess()
{
    currTime = millis();
    while (millis() < currTime + interval)
    {
        ; // Wait for 10 ms to ensure packages are received
    }
}

// Use for Debugging
void logger(String data)
{
    SerialUSB.print("Logger: ");
    SerialUSB.println(data);
}
