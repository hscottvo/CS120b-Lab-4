/*	Author: svo021
 *  Partner(s) Name: Scott Vo
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum led_states {led_init, led_one, led_one_wait, led_zero, led_zero_wait} led_state;

void led_tick() {
    switch(led_state){
        case led_init:
            led_state = led_zero_wait;
            break;
        case led_one:
            if (PINA & 0x01 == 1) {
                led_state = led_one;
            }
            else {
                led_state = led_one_wait;
            }
            break;
        case led_one_wait:
            if (PINA & 0x01 == 1) {
                led_state = led_zero;
            }
            else {
                led_state = led_one_wait;
            }
        case led_zero;
            if (PINA & 0x01 == 1) {
                led_state = led_zero;
            }
            else {
                led_state = led_zero_wait;
            }
            break;
        case led_zero_wait;
            if (PINA & 0x01 == 1) {
                led_state = led_one;
            }
            else {
                led_state = led_zero_wait;
            }
            break;
        default:
            led_state = led_init;
            break;

    }

    switch(led_state){
        case led_init:
            PORTB = 0x01;
            break;
        case led_one:
            PORTB = 0x02;
            break;
        case led_one_wait:
            PORTB = 0x02;
            break;
        case led_zero;
            PORTB = 0x01;
            break;
        case led_zero_wait;
            PORTB = 0x01;
            break;
        default:
            PORTB = 0x01;
            break;
    }

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */

    while (1) {

    }
    return 1;
}