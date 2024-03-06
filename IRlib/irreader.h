#ifndef IRREADER_H
#define IRREADER_H

#include <stdint.h>

// Define constants
#define IR_PIN 2  // This refers to physical pin PD2 on ATmega328P

// Function prototypes
void IR_init();
uint8_t IR_receive();

#endif /* IRREADER_H */