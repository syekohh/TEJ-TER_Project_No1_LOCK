// include the header file that stores all data
#include "data.h"

// initialize the stepper library on pins 4 through 7:
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);

// initialize the distance and duration variables for the sensor in this scope
int distance;
long duration;

int counter;

// initialize a boolean variable to control unlock security
boolean accessGranted = false;

// setup method, runs once
void setup()
{

    // set the LED pins to output
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

    // set the speed at 60 rpm:
    myStepper.setSpeed(stepSpeedRPM);

    // initialize the serial port:
    Serial.begin(9600);
}

// method that loops the code
void loop()
{
    // reset the counter and accessGranted variables
    counter = 0;
    accessGranted = false;

    // set the distance variable equal to the
    // distance returned from the getDistance() method
    distance = getDistance();

    // print the distance being read
    Serial.println(distance);

    // locked phase, green LED is off, red LED is on
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);

    // if the distance between the object and the
    // sensor is less than 7cm, begin the unlock phase
    if (distance < 7)
    {

        while (distance < 7)
        {
            // blink the green LED to signify the unlock process has started
            digitalWrite(greenPin, HIGH);
            delay(500);
            digitalWrite(greenPin, LOW);

            // the counter increases by one for every blink
            counter++;

            // get the distance to ensure its still less than 7cm
            distance = getDistance();

            // grant the user access if they held for 3 counts
            if (counter == 3)
            {
                accessGranted = true;
            }
            else
            {
                accessGranted = false;
            }

            // used for debugging
            if (distance == 0)
            {
                distance = 100;
            }
        }

        // if the security check is valid, you are
        // granted access, if you are, unlock the lock.
        if (accessGranted)
        {
            // run the unlock phase
            unlockPhase();
        }
    }
}

// method to return the distance between the object and the sensor
int getDistance()
{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delay(1000);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    return distance;
}

// method for the unlock phase
void unlockPhase()
{
    // set the green LED on, and red LED off
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);

    // unlock revolution in one direction:
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    myStepper.step(stepsPerRevolution);
    myStepper.step(stepsPerRevolution / 2);

    //stay unlocked for 7 seconds
    delay(unlockTime);

    // lock revolution in the other direction:
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    myStepper.step(-stepsPerRevolution);
    myStepper.step(-stepsPerRevolution / 2);
}