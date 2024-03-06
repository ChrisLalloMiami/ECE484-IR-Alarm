#include <avr/io.h>

#ifndef UART_H
#define UART_H

#define F_CPU 16000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P)
#define BAUD 9600         // Baud rate for UART communication
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)

void UART_init();
void UART_transmit(unsigned char data);
void UART_print(const char *str);
void UART_print_uint16(uint16_t value);

#endif /* UART_H */