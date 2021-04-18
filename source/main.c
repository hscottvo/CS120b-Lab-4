/*	Author: svo021
 *  Partner(s) Name: Scott Vo
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum lock_states {lock_init, lock_unlocked, lock_locked, lock_pass_hash, lock_pass_hash_press, lock_pass_y, lock_switch} lock_state;

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
            lock_state = lock_pass_hash;
            break;
        case lock_pass_hash:
            if (PINA ==  0x04) {
                lock_state = lock_pass_hash_press;
            }
            else {
                lock_state = lock_pass_hash;
            }
            break;
        case lock_pass_hash_press:
            if (PINA == 0x04) {
                lock_state = lock_pass_hash_press;
            }else if (PINA == 0x00) {
                lock_state = lock_pass_y;
            }
            else {
                lock_state = lock_pass_hash;
            }
            break;
        case lock_pass_y:
            if (PINA == 0x00) {
                lock_state = lock_pass_y;
            }
            else if (PINA == 0x02) {
                lock_state = lock_switch;
            }
            else {
                lock_state = lock_pass_hash;
            }
            break;
        case lock_switch:
            if ((PORTB & 0x01) == 0x00) {
                lock_state = lock_unlocked;
            }
            else {
                lock_state = lock_locked;
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
        case lock_pass_hash:
            break;
        case lock_pass_hash_press:
            break;
        case lock_pass_y:
            break;
        case lock_switch:
            PORTB = 0x01;
            break;
        default:
            break;
    }
    PORTC = lock_state;
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
