#ifndef SENSOR_H_
#define SENSOR_H_

struct Temperatures {
    float temp_ext, temp_int, temp_ref;
};

struct Temperatures temp = { .temp_ext = 0, .temp_int = 0, .temp_ref = 0 };

void read_temperatures(int temp_ref_strategy, float temp_ref);
int read_control_signal(int control_strategy);
void att_control_signal(int pid)

#endif
