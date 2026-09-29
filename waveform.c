#include <avr/io.h>

int main(void) {
        DDRD |= (1 << 6);
        OCR0A = 128;
        TCCR0A |= (1 << 7);
        TCCR0A |= (1 << 0);
        TCCR0A |= (1 << 1);
        TCCR0B |= (1 << 0);

        while(1)
        {
        }
}
