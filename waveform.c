#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

volatile bool fall   = false;
volatile bool square = false;
volatile uint8_t count = 0;

int main(void) {
        DDRD   |= (1 << 6);
        DDRD  &= ~(1 << 2);
        PORTD  |= (1 << 2);
        PCMSK2 |= (1 << 2);
        PCICR  |= (1 << 2);
        OCR0A = count;
        TCNT2 = 0;
        TCCR0A |= (1 << 7);
        TCCR0A |= (1 << 0);
        TCCR0A |= (1 << 1);
        TCCR0B |= (1 << 0);
        TCCR2B |= (1 << 1);
        TCCR2B |= (1 << 2);
        TIMSK2 |= (1 << 0);
        sei();

        while(1)
        {
        }
}

ISR(TIMER2_OVF_vect) {
        if (fall)
        {
                if (count < 2)
                {
                        fall = false;
                }
                count--;
        }
        else 
        {
                if (count > 253)
                {
                        fall = true;
                }
                count++;
        }
        if (square)
        {
                OCR0A = fall * 255;
        }
        else
        {
                OCR0A = count;
        }
}

ISR(PCINT2_vect) {
        square = !(PIND & (1 << 2));
}
