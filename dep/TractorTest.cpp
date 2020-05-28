//Libraries
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"

//Pin Initializations
const int HARDWARE_PIN = 1;

const int BACK_IN1 = 0;
const int BACK_IN2 = 2;
const int BACK_IN3 = 21;
const int BACK_IN4 = 22;
const int BACK_LEFT_PWM = 3;
const int BACK_RIGHT_PWM = 25;

/*
const int MID_IN1;
const int MID_IN2;
const int MID_IN3;
const int MID_IN4;

const int FRONT_IN1;
const int FRONT_IN2;
const int FRONT_IN3;
const int FRONT_IN4;
*/

int main(void) {
    if (wiringPiSetup() == -1) {
        std::cout << "The wiringPi library has failed to initialize." << endl;     
    }

    Motor left(BACK_IN1, BACK_IN2, BACK_LEFT_PWM);
    Motor right(BACK_IN3, BACK_IN4, BACK_RIGHT_PWM);
    
    right.setForward(50);
    left.setForward(50);
    delay(500);

    right.stop();
    left.stop();
    return 0;
}
