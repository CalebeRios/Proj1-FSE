#include <stdio.h>

#include "../inc/wiring-pi.h"
#include "../inc/pid.h"
#include "../inc/sensors.h"

extern int actuators;

void on_off(float temp_internal, float temp_reference, float histerese) {
    if (temp_internal > temp_reference + (histerese / 2)) {
        actuators = -100;
        turn_on_fan(100);
    } else if (temp_internal < temp_reference - (histerese / 2)) {
        actuators = 100;
        turn_on_resistor(100);
    }
}

void pid(float temp_internal, float temp_reference) {
    pid_atualiza_referencia(temp_reference);

    int pid = (int) pid_controle((double) temp_internal);
    actuators = pid;

    att_control_signal(pid);

    printf("PID: %d\n", pid);

    if (pid > 0) {
        turn_on_resistor(pid);
    } else if(pid < -40) {
        turn_on_fan((pid) * -1);
    } else {
        turn_off_pins();
    }
}
