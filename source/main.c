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

enum counter_states {counter_init, counter_reset, counter_wait, counter_dec, counter_dec_wait, counter_inc, counter_inc_wait} counter_state = ;

void counter_tick() {
    switch(counter_state){
        case counter_init:
            counter_state = counter_wait;
            break;
        case counter_reset:
            if ((PINA & 0x03) == 0x03){
                counter_state = counter_reset;
            }
            else {
                counter_state = counter_wait;
            }
            break;
        case counter_wait:
            if ((PINA & 0x03) == 0x00){
                counter_state = counter_wait;
            }
            else if ((PINA & 0x03) == 0x01){
                counter_state = counter_inc;
            }
            else if ((PINA & 0x03) == 0x02) {
                counter_state = counter_dec;
            }
            else {
                counter_state = counter_reset;
            }
            break;
        case counter_dec:
            counter_state = counter_dec_wait;
            break;
        case counter_dec_wait:
            if ((PINA & 0x03) == 0x02) {
                counter_state = counter_dec_wait;
            }
            else if ((PINA & 0x03) == 0x03) {
                counter_state = counter_reset;
            }
            else {
                counter_state = counter_wait;
            }
            break;
        case counter_inc:
            counter_state = counter_inc_wait;
            break;
        case counter_inc_wait:
            if ((PINA & 0x03) == 0x01) {
                counter_state = counter_inc_wait;
            }
            else if ((PINA & 0x03) == 0x03) {
                counter_state = counter_reset;
            }
            else {
                counter_state = counter_wait;
            }
            break;
        default:
            counter_state = counter_init;
            break;
    }
    switch(counter_state){
        case counter_init:
            PORTC = 0x07;
            break;
        case counter_reset:
            PORTC = 0x00;
            break;
        case counter_wait:
            break;
        case counter_dec:
            if (PORTC > 0x00) {
                PORTC = PORTC - 0x01;
            }
            break;
        case counter_dec_wait:
            break;
        case counter_inc:
            if (PORTC < 0x09) {
                PORTC = PORTC + 0x01;
            }
            break;
        case counter_inc_wait:
            break;
        default:
            PORTC = 0x07;
            break;
    }

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */

    while (1) {
        counter_tick();
    }
    return 1;
}