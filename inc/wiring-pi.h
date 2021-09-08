#ifndef WIRING_PI_H_
#define WIRING_PI_H_

void init_pwm_wiringPi();
void stop_pwm_wiringPi();
void turn_on_fan(int intensity);
void turn_on_resistor(int intensity);
void turn_off_pins();

#endif
