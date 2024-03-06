#include "uart.h"

void UART_init() {
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B = (1 << TXEN0);  // Enable transmitter
    UCSR0C = (3 << UCSZ00); // Set frame format: 8 data bits, 1 stop bit, no parity
}

// Function to transmit data
void UART_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
    UDR0 = data; // Put data into buffer, sends the data
}

// Function to print string
void UART_print(const char *str) {
    while (*str) {
        UART_transmit(*str++);
    }
}

void UART_print_uint16(uint16_t value) {
    char buffer[6]; // Maximum 5 characters for uint16_t value and 1 for null terminator
    itoa(value, buffer, 10); // Convert uint16_t to string
    UART_print(buffer); // Print the string
}