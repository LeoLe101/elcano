/*
    REFERENCES: 
    https://www.instructables.com/id/How-to-control-Arduino-with-RC-receiver-in-10-minu/
    https://www.arduino.cc/en/Reference/Servo
    https://www.sparkfun.com/tutorials/348
*/
#include <Servo.h> // servo library

Servo mServo; // servo initialization

/*
    Servo.Writes() write a value to the servo, controlling the shaft accordingly. 
    On a standard servo, this will set the angle of the shaft (in degrees), 
    moving the shaft to that orientation. On a continuous rotation servo, this 
    will set the speed of the servo.
*/

int post = 0; // 0:   full-speed in one direction,
              // 180: full speed in the other direction
              // 90:  no movement).
int channel1, channel2, channel3, channel4, channel5, channel6;
unsigned long currTime = 0;

void setup()
{
    pinMode(THROTTLE_PIN, INPUT);
    pinMode(TURN_PIN, INPUT);
    pinMode(INTERRUPT_PIN, INPUT);
    pinMode(AUTO_PIN, INPUT);
    pinMode(EBRAKE_PIN, INPUT);
    pinMode(REVERSE_PIN, INPUT);
    mServo.attach(9); // attaches the servo on pin 9 or 10 only
    Serial.begin(SERIAL_USB_UART);
}

void loop()
{
    // Read the pulse width of each channel
    channel1 = pulseIn(THROTTLE_PIN, HIGH, 25000);
    channel2 = pulseIn(TURN_PIN, HIGH, 25000);
    channel3 = pulseIn(INTERRUPT_PIN, HIGH, 25000);
    channel4 = pulseIn(AUTO_PIN, HIGH, 25000);
    channel5 = pulseIn(EBRAKE_PIN, HIGH, 25000);
    channel6 = pulseIn(REVERSE_PIN, HIGH, 25000);

    if (DEBUG)
        channelDebugger();

    // Checking Throttle
    if ((channel1 >= 1500) && (channel1 <= 1600))
    {
        Serial.println("Throttle -- Default");
        pos = 90;
        mServo.write(pos);
    }
    else
    {
        Serial.println("Throttle -- Moving");
        // Testing servo to move forward from 0 to 180 and vice versa.
        for (pos = 0; pos < 180; pos += 1)
        {
            mServo.write(pos);
            waitForProcess(1); // waits 1ms for the servo to reach the position
        }

        for (pos = 180; pos >= 1; pos -= 1)
        {
            mServo.write(pos);
            waitForProcess(1); // waits 1ms for the servo to reach the position
        }
    }

    // Checking Turn
    if ((channel2 >= 1500) && (channel2 <= 1600))
    {
        Serial.println("Turn -- Default");
        pos = 90;          //set servo to center
        mServo.write(pos); // set to pos which is 90
    }
    else
    {
        Serial.println("Turn -- Moving");
                // Testing servo to move forward from 0 to 180 and vice versa.
        for (pos = 0; pos < 180; pos += 1)
        {
            mServo.write(pos);
            waitForProcess(1); // waits 1ms for the servo to reach the position
        }

        for (pos = 180; pos >= 1; pos -= 1)
        {
            mServo.write(pos);
            waitForProcess(1); // waits 1ms for the servo to reach the position
        }
    }

    // Checking Reverse
    if ((channel6 >= 1500) && (channel6 <= 1600))
    {
        Serial.println("Reverse -- Default");
        pos = 90;          //set servo to center
        mServo.write(pos); // set to pos which is 90
    }
    else
    {
        Serial.println("Reverse -- Moving");
                // Testing servo to move forward from 0 to 180 and vice versa.
        for (pos = 0; pos < 180; pos += 1)
        {
            mServo.write(pos);
            waitForProcess(1); // waits 1ms for the servo to reach the position
        }

        for (pos = 180; pos >= 1; pos -= 1)
        {
            mServo.write(pos);
            waitForProcess(1); // waits 1ms for the servo to reach the position
        }
    }
    waitForProcess(100);
}

/*
    HELPER FUNCTIONS...
*/
void channelDebugger()
{
    Serial.print("C1:");
    Serial.println(channel1);
    Serial.print("C2:");
    Serial.println(channel2);
    Serial.print("C3:");
    Serial.println(channel3);
    Serial.print("C4:");
    Serial.println(channel4);
    Serial.print("C5:");
    Serial.println(channel5);
    Serial.print("C6:");
    Serial.println(channel6);
}

void logger(String str)
{
    Serial.print("Logger: ");
    Serial.println(str);
}

void waitForProcess(long interval)
{
    currTime = millis();
    while (millis() < currTime + interval)
    {
        ; // Wait for 10 ms to ensure packages are received
    }
}