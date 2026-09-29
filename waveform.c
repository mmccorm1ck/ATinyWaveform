#include <stdint.h>
#define DDRD   (*(volatile uint8_t *) 0x2A)
//#define PORTD  (*(volatile uint8_t *) 0x2B)
#define TCCR0A (*(volatile uint8_t *) 0x44)
#define TCCR0B (*(volatile uint8_t *) 0x45)
#define OCR0A  (*(volatile uint8_t *) 0x47)

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
