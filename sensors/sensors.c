#include <stdio.h>
#include <unistd.h>

#include "../uart/uart.h"
#include "../bme280/bme280.h"
#include "../global.h"

void read_temperatures(int temp_ref_strategy, float temp_ref) {
    temp.temp_ext = get_external_temperature();

    write_uart(0x23, 0xC1);
    temp.temp_int = read_float_uart();

    if (temp_ref_strategy == 1) {
        temp.temp_ref = temp_ref;
    } else {
        write_uart(0x23, 0xC2);
        float tr = read_float_uart();
        temp.temp_ref = tr;
    }

    printf("TI: %.2f\n", temp.temp_int);
    printf("TE: %.2f\n", temp.temp_ext);
    printf("TR: %.2f\n", temp.temp_ref);
}

int read_manual_key(int control_strategy) {
    if (control_strategy == 3) {
        write_uart(0x23, 0xC3);
        return read_int_uart();
    } 

    return -1;
}

void att_control_signal(int pid) {
    write_int_uart(0x16, 0xD1, pid);
}
