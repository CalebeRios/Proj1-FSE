#ifndef SENSORS_H_
#define SENSORS_H_

void read_temperatures(int temp_ref_strategy, float temp_ref);
int read_manual_key(int control_strategy);
void att_control_signal(int pid);

#endif
