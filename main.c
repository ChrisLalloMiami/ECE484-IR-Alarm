#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include "LCDlib/hd44780.h"
#include "IRlib/irreader.h"
#include "UARTlib/uart.h"

#define ALARM_TIME 0.1 // Time to set on alarm in minutes

void my_delay_ms(unsigned int t);
void buzz();
short checkButtons(int pin);

int main() {
	// Setup Buzzer Pin
	DDRB |= (1 << PB3);

	//Setup UART
	UART_init();
	UART_print("Setup!\n\r");

	// Setup LCD
	LCD_Setup();
	UART_print("LCD setup!\n\r");

	// Setup IR
	IR_init();
	UART_print("IR setup!\n\r");

	// Print Intro
	LCD_Clear();
	UART_print("LCD cleared!\n\r");
	LCD_GotoXY(0, 0);
	LCD_PrintString("Alarm Demo");

	LCD_GotoXY(0, 1);
	LCD_PrintString("Press button");
	UART_print("LCD Printed!\n\r");

	while (1) {
		if (checkButtons(PB2)) {
			UART_print("Arming!\n\r");
			break;
		}
	}
	UART_print("Clearing screen!\n\r");
	LCD_Clear();
	my_delay_ms(1000);

	// Start Alarm
	UART_print("Starting timer!\n\r");
	start_timer(ALARM_TIME);
	UART_print("Done!\n\r");
	while (1) {
		buzz();
		uint8_t data = IR_receive();
		if (!data) {
			break;
		}
	}

	// End system
	LCD_Clear();
	LCD_GotoXY(0, 0);
	LCD_PrintString("Alarm disarmed!");
	return 0;
}

/**
 * Function to check if the given pin on port B is being pressed
*/
short checkButtons(int pin) {
	short pass = 0;
	if ((PINB & (1 << pin)) != 0) {
		// Software debounce
		_delay_ms(15);
		if ((PINB & (1 << pin)) != 0) {
			pass = 1;
		}
	}
	else {
		pass = 0;
	}
	return pass;
}

/**
 * Pulses the buzzer high for 30ms
*/
void buzz() {
	PORTB |= (1 << PB3);
	_delay_ms(30);
	PORTB &= ~(1 << PB3);
	_delay_ms(30);
}

/**
 * Sets a timer on the LCD using the given number of minutes
*/
void start_timer(float minutes) {
    uint16_t seconds = (uint16_t)(minutes * 60);
    uint8_t minutes_display, seconds_display;
    while (seconds > 0) {
        minutes_display = seconds / 60;
        seconds_display = seconds % 60;

        // Display timer on LCD
        char timer_str[10];
        sprintf(timer_str, "%d:%02d", minutes_display, seconds_display);
        LCD_Clear();
        LCD_GotoXY(0, 0);
        LCD_PrintString(timer_str);

        my_delay_ms(1000); // Wait for 1 second
        seconds--;
    }
}

/**
 * Delay function for handling longer delays
*/
void my_delay_ms(unsigned int t) {
	unsigned int i;
	for (i=0; i<(t/10); i++) {
		_delay_ms(10);
	}
}
