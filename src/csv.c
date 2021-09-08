#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../inc/global.h"

FILE *fp;

extern int actuators;

void init_csv() {
    fp = fopen("log.csv", "w+");    
    fprintf(fp, "Timestamp, Internal Temperature, External Temperature, Reference Temperature, Actuators\n");
}

void write_csv() {
    sleep(2);

    int hours, minutes, seconds, day, month, year;
    time_t now = time(NULL);

    struct tm *local = localtime(&now);

    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    fprintf(fp,"%02d/%02d/%d %02d:%02d:%02d,", day, month, year, hours, minutes, seconds);
    fprintf(fp,"%.2f,%.2f,%.2f,%d%%\n", temp.temp_int, temp.temp_ext, temp.temp_ref, actuators);

    write_csv();
}

void close_csv() {
    fclose(fp);
}
