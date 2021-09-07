#ifndef CONTROLS_H_
#define CONTROLS_H_

void on_off(float temp_internal, float temp_reference, float histerese);
void pid(float temp_internal, float temp_reference);

#endif
