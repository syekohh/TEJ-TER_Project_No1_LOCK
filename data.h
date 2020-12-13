// include the header file for the Stepper 
// Motor and its functions and classes
#include <Stepper.h>

// define constants for the Stepper Motor
//#define stepsPerRevolution 500
#define stepsPerRevolution 200
#define unlockTime 7000
#define stepSpeedRPM 60

// define constants for the LEDs
#define greenPin 3
#define redPin 2

// define constants for the UltraSonic Sensor
#define trigPin 9
#define echoPin 10

#define acceptedCode "HQH"

// Create Global Variables for the distance measure and
// sound wave travel duraction for the UltraSonic Sensor
extern int distance;
extern long duration;
