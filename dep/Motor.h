//Libraries
#include <wiringPi.h>
#include <softPwm.h>

class Motor {
    public:
    Motor(int pin1, int pin2, int pwmPin);

    void setForward(int speed);
    void setReverse(int speed);
    void stop(int pwm);

    private:
    int pin1;
    int pin2;
    int pwm;
};

Motor::Motor (int pin1, int pin2, int pwmPin){
        pin1 = pin1;
        pin2 = pin2;
        pwm = pwmPin;

        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        softPwmCreate(pwm, 0, 100);
}

void Motor::setForward(int speed) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        softPwmWrite(pwm, speed);
    }
void Motor::setReverse(int speed) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    softPwmWrite(pwm, speed);
}
void Motor::stop() {
    softPwmWrite(pwm, 0);
}
