#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

#include "../inc/bme280.h"
#include "../inc/lcd.h"
#include "../inc/pid.h"
#include "../inc/uart.h"
#include "../inc/menu.h"
#include "../inc/controls.h"
#include "../inc/wiring-pi.h"
#include "../inc/csv.h"
#include "../inc/sensors.h"
#include "../inc/main.h"
#include "../inc/global.h"

pthread_t id;
struct Temperatures temp = { .temp_ext = 0, .temp_int = 0, .temp_ref = 0 };

void handle_sigint(int sig) {
    stop_pwm_wiringPi();
    close_uart();
    close_csv();
    exit(0);
}

void read_and_print_temperature() {
    read_temperatures(temp_ref_strategy, temp_ref);
    int key = read_manual_key(control_strategy);

    write_lcd(temp.temp_int, temp.temp_ext, temp.temp_ref, actuators);

    if (control_strategy == 1 || (control_strategy == 3 && key == 0)) {
        on_off(temp.temp_int, temp.temp_ref, histerese);
    } else {
        pid(temp.temp_int, temp.temp_ref);
    }

    read_and_print_temperature();
}

void* get_log(void* p) {
    write_csv();
}

void init_sensors() {
    init_csv();
    init_uart();
    bme280Init(1, 0x76);
    lcd_init();
    init_pwm_wiringPi();
}

int main() {
    signal(SIGINT, handle_sigint);

    init_sensors();

    print_menu();

    if (control_strategy == 2) {
        pid_configura_constantes(kp, ki, kd);
    }

    pthread_create(&id, NULL, get_log, NULL);

    read_and_print_temperature();

    return 0;
}
