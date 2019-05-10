#include "BluetoothControlTx.h"

// initialize package
dataFromTransmitter txData; // sent from transmitter

String btData = "";
unsigned long currTime = 0;
const long interval = 20;

void setup()
{
    SerialUSB.begin(UART_BAUDRATE_SERIAL_USB);
    Serial1.begin(UART_BAUDRATE_SERIAL_USB); // Init hardware serial port --> PIN: 0 (RX) | 1 (TX)
    if (DEBUG)
        // wait until SerialUSB initialize
        while (!SerialUSB)
            ;

    String initMesg = "** TranX Init at " + String(UART_BAUDRATE_BT_SERIAL);
    SerialUSB.println(initMesg);
    SerialUSB.println("Setup Complete!");
}

void loop()
{
    // readInputs(); 

    // TESTING IN PROGRESS
    txData.turn = 10;
    txData.throttle = 20;
    txData.autonomous = 30;
    txData.ebrake = 40;

    // Send the values to through Bluetooh module
    // (Dividing 4 to convert value from 0-1023 to 0-256 for 1 Byte size)
    Serial1.print(txData.turn / 4);
    Serial1.print(txData.throttle / 4);
    Serial1.print(txData.autonomous / 4);
    Serial1.print(txData.ebrake / 4);

    btData = "Data to be sent --> " + String(txData.throttle) + "," + String(txData.turn);
    SerialUSB.println(btData);

    // Read from Bluetooh module and send to Arduino Serial Monitor
    // (Receiving ACK message from the RX)
    if (SerialUSB.available() > 0)
    {
        if (DEBUG)
        {
            btData = SerialUSB.read();
            SerialUSB.println(btData);
        }
    }
    waitForProcess();
}

/**
 * --------------------- Helper Functions --------------------------------
 */
void readInputs()
{
    txData.turn = analogRead(TURN_PIN);
    txData.throttle = analogRead(THROTTLE_PIN);
    txData.autonomous = digitalRead(AUTO_PIN);
    txData.ebrake = digitalRead(EBRAKE_PIN);
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