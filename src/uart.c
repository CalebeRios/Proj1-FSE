#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "../inc/crc.h"

unsigned char buffer[256] = {0};
unsigned char *array = &buffer[0];
int fd;
char address = 0x01;

void init_uart() {
    fd = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
}

void close_uart() {
    close(fd);
}

void clean_buffer() {
    array = &buffer[0];
}

void calcule_CRC(int length) {
    short crc = calcula_CRC(buffer, (7 + length));
    *array++ = crc & 0xff;
    *array++ = (crc >> 8) & 0xff;
}

void read_trash() {
    char tmp;
    read(fd, &tmp, 1);
}

void write_uart(char code, char subcode) {
    *array++ = address;
    *array++ = code;
    *array++ = subcode;
    *array++ = 0;
    *array++ = 7;
    *array++ = 0;
    *array++ = 2;
    
    calcule_CRC(0);

    write(fd, buffer, 9);

    clean_buffer();
    sleep(1);
}

void write_int_uart(char code, char subcode, int value) {
    *array++ = address;
    *array++ = code;
    *array++ = subcode;
    *array++ = 0;
    *array++ = 7;
    *array++ = 0;
    *array++ = 2;

    *array++ = value & 0xff;
    *array++ = (value >> 8) & 0xff;
    *array++ = (value >> 16) & 0xff;
    *array++ = (value >> 24) & 0xff;

    calcule_CRC(4);

    write(fd, buffer, 13);

    clean_buffer();
}

int read_int_uart() {
    int value;

    read_trash();
    read_trash();
    read_trash();

    read(fd, &value, sizeof(int));

    read_trash();
    read_trash();

    return value;
}

float read_float_uart() {
    float value;

    read_trash();
    read_trash();
    read_trash();

    read(fd, &value, sizeof(float));

    read_trash();
    read_trash();

    return value;
}
