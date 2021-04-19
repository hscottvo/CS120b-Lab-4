/*	Author: svo021
 *  Partner(s) Name: Scott Vo
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum lock_states {lock_init, lock_unlocked, lock_locked, lock_pass, lock_pass_press, lock_switch} lock_state;
unsigned char pass[4] = {0x04, 0x01, 0x02, 0x01};
unsigned char i = 0x00;

void lock_tick() {
    switch(lock_state){
        case lock_init:
            lock_state = lock_locked;
            break;
        case lock_unlocked:
            if (((PINA >> 7) & 0x01) == 1){
                lock_state = lock_locked;
            }
            else {
                lock_state = lock_unlocked;
            }
            break;
        case lock_locked:
            lock_state = lock_pass;
            break;
        case lock_pass:
            if (PINA ==  pass[i]) {
                lock_state = lock_pass_press;
                i = i + 1;
                if(i >= 3) lock_state = lock_switch;
            }
            else if (PINA == 0x00) {
                lock_state = lock_pass;
            }
            else {
                lock_state = lock_pass;
                i = 0x00;
            }
            break;
        case lock_pass_press:
            if (PINA == pass[i-1]) {
                lock_state = lock_pass_press;
            }else if (PINA == 0x00) {
                lock_state = lock_pass;
            }
            else {
                lock_state = lock_pass;
                // i = 0x00;
            }
            break;
        case lock_switch:
            i = 0x00;
            if ((PORTB & 0x01) == 0x00) {
                lock_state = lock_unlocked;
                PORTB = 0x01;
            }
            else {
                lock_state = lock_locked;
                PORTB = 0x00;
            }
            break;
        default:
            break;
    }
    switch(lock_state){
        case lock_init:
            PORTB = 0x00; //locked
            break;
        case lock_unlocked:
            PORTB = 0x01;
            break;
        case lock_locked:
            PORTB = 0x00;
            break;
        case lock_pass:
            break;
        case lock_pass_press:
            break;
        case lock_switch:
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    lock_state = lock_init;
    /* Insert your solution below */

    while (1) {
        lock_tick();
    }
    return 1;
}
