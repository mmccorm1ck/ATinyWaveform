#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdint.h>

volatile bool fall   = false;
volatile bool square = false;
volatile bool sine   = false;
volatile uint8_t count = 0;

const uint8_t sinTable[128] PROGMEM =
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
        0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05,
        0x06, 0x06, 0x06, 0x07, 0x07, 0x08, 0x09, 0x09,
        0x0A, 0x0A, 0x0B, 0x0C, 0x0C, 0x0D, 0x0E, 0x0E,
        0x0F, 0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
        0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24,
        0x25, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2E,
        0x2F, 0x30, 0x31, 0x32, 0x34, 0x35, 0x36, 0x38,
        0x39, 0x3A, 0x3C, 0x3D, 0x3E, 0x40, 0x41, 0x42,
        0x44, 0x45, 0x46, 0x48, 0x49, 0x4B, 0x4C, 0x4E,
        0x4F, 0x50, 0x52, 0x53, 0x55, 0x56, 0x58, 0x59,
        0x5B, 0x5C, 0x5E, 0x5F, 0x61, 0x62, 0x64, 0x65,
        0x67, 0x69, 0x6A, 0x6C, 0x6D, 0x6F, 0x70, 0x72,
        0x73, 0x75, 0x77, 0x78, 0x7A, 0x7B, 0x7D, 0x7F
};

int main(void) {
        DDRD   |= (1 << 6);
        DDRD  &= ~(1 << 2);
        PORTD  |= (1 << 2);
        PCMSK2 |= (1 << 2);
        DDRD  &= ~(1 << 3);
        PORTD  |= (1 << 3);
        PCMSK2 |= (1 << 3);
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
                OCR0A = fall ? 255 : 0;
        }
        else if (sine)
        {
                uint8_t temp = count;
                if (count & 0x80)
                {
                        temp = 255 - temp;
                }
                uint8_t sinResult = pgm_read_byte(&(sinTable[temp]));
                if (count & 0x80)
                {
                        sinResult = 255 - sinResult;
                }
                OCR0A = sinResult;
        }
        else
        {
                OCR0A = count;
        }
}

ISR(PCINT2_vect) {
        square = !(PIND & (1 << 2));
        sine   = !(PIND & (1 << 3));
}
