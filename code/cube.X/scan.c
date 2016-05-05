#include <xc.h>
#include <stdint.h>
#include "scan.h"
#include "map.h"

outbuf_t buffer0, buffer1;
outbuf_t *out[2] = {&buffer0, &buffer1};
uint8_t ptr = 0;

// Scaning LED matrix
// The function is performed in XX mks
void scan_irq(void)
{
	static uint8_t step = 0;
    static uint8_t up[3] = {1, 0, 0};
    static uint8_t p = 0;
    #ifndef __TEST__
        CLRWDT();
        INTCONbits.TMR0IF = 0;
    #endif
	TRISB = TRISC = TRISD = 0xFF;
	PORTB = ~up[0];
	PORTC = ~up[1];
	PORTD = ~up[2];
	TRISB = ~((*out[p])[0][step] | up[0]);
	TRISC = ~((*out[p])[1][step] | up[1]);
	TRISD = ~((*out[p])[2][step] | up[2]);
    step++;
	if (up[2] > 0)
	{
        if ((up[2] <<= 1) == 0)
        {
            up[0] = 1;
            step = 0;
            p = ptr;
        }
    }
	else if (up[1] > 0)
	{
        if ((up[1] <<= 1) == 0)
            up[2] = 1;
    }
	else if (up[0] > 0)
	{
        if ((up[0] <<= 1) == 0)
            up[1] = 1;
    }
}

// Matrix reset
void scan_res(uint8_t p, uint8_t mask)
{
    int16_t i;
    if (p >= sizeof(out)/sizeof(out[0])) return;
	for (i = sizeof(outbuf_t)-1; i >= 0; i--)
		((uint8_t *)out[p])[i] = mask;
    ptr = p;
}

// Matrix inversion
void scan_inv(uint8_t p)
{
    int16_t i;
    if (p >= sizeof(out)/sizeof(out[0])) return;
	for (i = sizeof(outbuf_t)-1; i >= 0; i--)
		((uint8_t *)out[p])[i] = ~((uint8_t *)out[p])[i];
    ptr = p;
}

// Copy img to matrix
void scan_copy(const uint8_t p, uint8_t img[8][8])
{
    int16_t x, y;
    uint8_t * pointer;
    if (p >= sizeof(out)/sizeof(out[0])) return;
	for (x = 7; x >= 0; x--)
        for (y = 7; y >= 0; y--)
        {
            pointer = &((*out[p])[remap[x][y].row][remap[x][y].col]);
            *pointer &= remap[x][y].mask;
            *pointer |= ~remap[x][y].mask & img[x][y];
            if (!remap[x][y].mask) continue;
            pointer--;
            *pointer &= ~remap[x][y].mask;
            *pointer |= remap[x][y].mask & img[x][y];
        }
    ptr = p;
}
