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
int post = 0; //(0: full-speed in one direction, 180: full speed in the other direction, value near 90: no movement).
int channel1, channel2, channel3, channel4, channel5, channel6;
unsigned long currTime = 0;
const long interval = 100;

void setup()
{
    pinMode(THROTTLE_PIN, INPUT);
    pinMode(TURN_PIN, INPUT);
    pinMode(INTERRUPT_PIN, INPUT);
    pinMode(AUTO_PIN, INPUT);
    pinMode(EBRAKE_PIN, INPUT);
    pinMode(REVERSE_PIN, INPUT);
    mServo.attach(THROTTLE_PIN); // attaches the servo on pin 9 -- change pin number accordingly
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
        pos = 90;           //set servo to center
        myservo.write(pos); // set to pos which is 90
    }
    else
    {
        Serial.println("Throttle -- Moving");
        for (pos = 0; pos < 180; pos += 1) // goes from 0 degrees to 180 degrees
        {                                  // in steps of 1 degree
            myservo.write(pos);            // tell servo to go to position in variable 'pos'
            delay(1);                      // waits 1ms for the servo to reach the position
        }

        for (pos = 180; pos >= 1; pos -= 1) // goes from 180 degrees to 0 degrees
        {
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(1);           // waits 1ms for the servo to reach the position
        }
    }

    // Checking Turn
    if ((channel2 >= 1500) && (channel2 <= 1600))
    {
        Serial.println("Turn -- Default");
        pos = 90;           //set servo to center
        myservo.write(pos); // set to pos which is 90
    }
    else
    {
        Serial.println("Turn -- Moving");
    }

    // Checking Reverse
    if ((channel6 >= 1500) && (channel6 <= 1600))
    {
        Serial.println("Reverse -- Default");
        pos = 90;           //set servo to center
        myservo.write(pos); // set to pos which is 90
    }
    else
    {
        Serial.println("Reverse -- Moving");
    }
    waitForProcess();
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

void waitForProcess()
{
    currTime = millis();
    while (millis() < currTime + interval)
    {
        ; // Wait for 10 ms to ensure packages are received
    }
}