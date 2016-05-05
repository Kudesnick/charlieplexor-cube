#include <stdint.h>
#include "img.h"

extern void scan_copy(uint8_t p, uint8_t img[8][8]); // Copy img to matrix

// Copy img to matrix
void img_copy(uint8_t p, uint8_t img[8][8])
{
    scan_copy(p, img);
}

// Img reset
void img_set(uint8_t mask, uint8_t img[8][8])
{
    int16_t i;
    for (i = sizeof(imgbuf_t)-1; i >= 0; i--)
		((uint8_t *)&img)[i] = mask;
}

// Img inverse
extern void img_inv(uint8_t img[8][8])
{
    int16_t i;
    for (i = sizeof(imgbuf_t)-1; i >= 0; i--)
		((uint8_t *)&img)[i] = ~(((uint8_t *)&img)[i]);
}

// XOR with variable
void img_xor(uint8_t x, uint8_t img[8][8])
{
    int16_t i;
    for (i = sizeof(imgbuf_t)-1; i >= 0; i--)
		((uint8_t *)&img)[i] ^= x;
}

// Shift image
void img_shift(shift_t sh, uint8_t img[8][8])
{
    int8_t i,x,y;
    switch (sh)
    {
        case sh_leftx:
            for(x = 7; x > 0; --x)
                for (y = 7; y >= 0; --y)
                    img[x][y] = img[x-1][y];
            for (y = 7; y >= 0; --y)
                img[0][y] = 0;
            break;
        case sh_lefty:
            for(y = 7; y > 0; --y)
                for (x = 7; x >= 0; --x)
                    img[x][y] = img[x][y-1];
            for (x = 7; x >= 0; --x)
                img[x][0] = 0;
            break;
        case sh_leftz:
            for (i = sizeof(imgbuf_t)-1; i >= 0; i--)
                ((uint8_t *)&img)[i] <<= 1;
            break;
        case sh_rightx:
            for(x = 0; x < 7; ++x)
                for (y = 7; y >= 0; --y)
                    img[x][y] = img[x+1][y];
            for (y = 7; y >= 0; --y)
                img[7][y] = 0;
            break;
        case sh_righty:
            for(y = 0; y < 7; ++y)
                for (x = x; y >= 0; --x)
                    img[x][y] = img[x][y+1];
            for (x = 7; x >= 0; --x)
                img[x][7] = 0;
            break;
        case sh_rightz:
            for (i = sizeof(imgbuf_t)-1; i >= 0; i--)
                ((uint8_t *)&img)[i] >>= 1;
            break;
    }
}


// Set pixel
extern void img_setpix(uint8_t x, uint8_t y, uint8_t z, uint8_t img[8][8], uint8_t val)
{
	if (x > 7 || y > 7 || z > 7) return;
	val = (val) ? 1 : 0;
	img[x][y] &= ~(1 << z);
	img[x][y] |= val << z;
}

// Get pixel
extern uint8_t img_getpix(uint8_t x, uint8_t y, uint8_t z, uint8_t img[8][8])
{
	if (x > 7 || y > 7 || z > 7) return 0;
	return (img[x][y] & (1 << z)) ? 1 : 0;
}
