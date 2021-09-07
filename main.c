#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

#include "./bme280/bme280.h"
#include "./lcd/lcd.h"
#include "./pid/pid.h"
#include "./uart/uart.h"
#include "./menu/menu.h"
#include "./controls/controls.h"
#include "./wiring-pi/wiring-pi.h"
#include "./csv/csv.h"
#include "./sensors/sensors.h"
#include "./main.h"
#include "./global.h"

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

    write_lcd(temp.temp_int, temp.temp_ext, temp.temp_ref);

    if (control_strategy == 1 || (control_strategy == 3 && key == 0)) {
        printf("On/Off Values: %d %d %f, %f, %f\n", control_strategy, temp_ref_strategy, temp.temp_int, temp.temp_ref, histerese);
        on_off(temp.temp_int, temp.temp_ref, histerese);
    } else {
        printf("PID Values: %d %d %f, %f, %lf, %lf, %lf\n", control_strategy, temp_ref_strategy, temp.temp_int, temp.temp_ref, kp, ki, kd);
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

    printf("%d\n", control_strategy);
    printf("%d\n", temp_ref_strategy);
    printf("%d\n", histerese);
    printf("%d %d %d\n", kp, ki, kd);

    if (control_strategy == 2) {
        pid_configura_constantes(kp, ki, kd);
    }

    pthread_create(&id, NULL, get_log, NULL);

    read_and_print_temperature();

    return 0;
}
