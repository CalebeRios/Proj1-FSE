#include <wiringPi.h>
#include <softPwm.h>

const int PWM_pin_resistor = 4;
const int PWM_pin_fan = 5;

void init_pwm_wiringPi() {
    wiringPiSetup();
	pinMode(PWM_pin_resistor, OUTPUT);
	pinMode(PWM_pin_fan, OUTPUT);
	softPwmCreate(PWM_pin_resistor, 0, 100);
	softPwmCreate(PWM_pin_fan, 0, 100);
}

void stop_pwm_wiringPi() {
    softPwmStop(PWM_pin_resistor);
    softPwmStop(PWM_pin_fan);
}

void turn_on_fan(int intensity) {
    softPwmWrite(PWM_pin_fan, intensity);
    softPwmWrite(PWM_pin_resistor, 0);
}

void turn_on_resistor(int intensity) {
    softPwmWrite(PWM_pin_resistor, intensity);
    softPwmWrite(PWM_pin_fan, 0);
}

void turn_off_pins() {
    softPwmWrite(PWM_pin_resistor, 0);
    softPwmWrite(PWM_pin_fan, 0);
}
