#include "sensor.h"
#include "../uart/uart.h"

void read_temperatures(int temp_ref_strategy, float temp_ref) {
    temp.temp_ext = get_external_temperature();

    write_uart(0x23, 0xC1);
    temp.temp_int = read_float_uart();

    usleep(500);

    if (temp_ref_strategy == 1) { 
        temp.temp_ref = temp_ref;
    } else {
        write_uart(0x23, 0xC2);
        temp.temp_ref = read_float_uart();
    }

    printf("TI: %.2f\n", temp.temp_int);
    printf("TE: %.2f\n", temp.temp_ext);
    printf("TR: %.2f\n", temp.temp_ref);
}

int read_manual_key(int control_strategy) {
    if (control_strategy == 3) {
        write_uart(0x23, 0xC3);
        return read_int_uart();
    } else {
        return -1;
    }
}

void att_control_signal(int pid) {
    write_int_uart(0x16, 0xD1, pid);
}
