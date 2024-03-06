#include <avr/io.h>
#include <avr/interrupt.h>
#include "irreader.h"

// Global variables
volatile uint8_t IR_data = 0;
volatile uint8_t IR_bit_count = 0;
volatile uint8_t IR_receiving = 0;

// Function to initialize IR communication
void IR_init() {
    // Set IR pin as input
    DDRD &= ~(1 << IR_PIN);
    // Enable external interrupt on falling edge of IR pin
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    // Enable external interrupt INT0
    EIMSK |= (1 << INT0);
    // Enable global interrupts
    sei();
}

// Interrupt service routine for receiving IR signals
ISR(INT0_vect) {
    if (IR_receiving) {
        uint8_t bit = (PIND & (1 << IR_PIN)) >> IR_PIN;
        IR_data |= (bit << IR_bit_count);
        IR_bit_count++;
        if (IR_bit_count == 8) {
            IR_receiving = 0;
        }
    } else {
        // Start receiving
        IR_receiving = 1;
        IR_bit_count = 0;
        IR_data = 0;
    }
}

// Function to receive IR data
uint8_t IR_receive() {
    if (IR_receiving) {
      return 0;
    }
    return 1;
}
