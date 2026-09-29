#include <stdint.h>
#define DDRB  (*(volatile uint8_t *) 0x24)
#define PORTB (*(volatile uint8_t *) 0x25)

void delay(volatile long time) {
        while (time > 0)
        {
                time--;
        }
}

int main(void) {
        DDRB |= (1 << 5);

        while(1)
        {
                PORTB ^= (1 << 5);
                delay(100000);
        }
}
