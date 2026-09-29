#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool fall = false;

int main(void) {
        DDRD |= (1 << 6);
        OCR0A = 0;
        TCNT2 = 0;
        TCCR0A |= (1 << 7);
        TCCR0A |= (1 << 0);
        TCCR0A |= (1 << 1);
        TCCR0B |= (1 << 0);
        TCCR2B |= (1 << 0);
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
                if (OCR0A < 2)
                {
                        fall = false;
                }
                OCR0A--;
        }
        else 
        {
                if (OCR0A > 253)
                {
                        fall = true;
                }
                OCR0A++;
        }
}
