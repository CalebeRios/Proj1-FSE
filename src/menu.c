#include <stdio.h>
#include <stdlib.h>

extern int control_strategy, temp_ref_strategy;
extern float temp_ref, histerese;
extern double kp, ki, kd;

void print_control_strategy() {
    printf("Estratégia de Controle:\n");
    printf("1) On-Off\n");
    printf("2) PID\n");
    printf("3) Chave Externa\n");

    scanf("%d", &control_strategy);
}

void print_temp_ref_strategy() {
    printf("-----------------\n");
    printf("Temperatura de referência:\n");
    printf("1) Terminal\n");
    printf("2) Potenciômetro\n");

    scanf("%d", &temp_ref_strategy);

    if (temp_ref_strategy == 1) {
        printf("-----------------\n");
        printf("Qual a temperatura de referência?\n");
        scanf("%f", &temp_ref);
    }
}

void ask_for_histerese() {
    printf("-----------------\n");
    printf("Qual a histerese?\n");
    scanf("%f", &histerese);
    printf("-----------------\n");
}

void ask_for_constants() {
    printf("-----------------\n");
    printf("Defina o Kp?\n");
    scanf("%lf", &kp);
    printf("Defina o Ki?\n");
    scanf("%lf", &ki);
    printf("Defina o Kd?\n");
    scanf("%lf", &kd);
    printf("-----------------\n");
}

void invalid_command() {
    printf("-----------------\n");
    printf("Comando inválido!\n");
    printf("-----------------\n");
    exit(1);
}

void print_menu() {
    printf("---- MENU ----\n");
    
    print_control_strategy();

    if (control_strategy == 1 ||  control_strategy == 2 || control_strategy == 3) {
        print_temp_ref_strategy();

        if (temp_ref_strategy < 1 || temp_ref_strategy > 2 )
            invalid_command();

        if (control_strategy == 1) {
            ask_for_histerese();
        } else if (control_strategy == 2) {
            ask_for_constants();
        }
    } else {
        invalid_command();
    }
}