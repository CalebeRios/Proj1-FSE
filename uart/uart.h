#ifndef UART_H_
#define UART_H_

void init_uart();
void close_uart();
void clean_buffer();
void write_uart(char code, char subcode);
void write_int_uart(char code, char subcode, int value);
int read_int_uart();
float read_float_uart();

#endif /* UART_H_ */