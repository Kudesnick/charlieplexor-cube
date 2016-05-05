#ifndef IMG_H
#define	IMG_H

#include <stdint.h>

typedef uint8_t imgbuf_t[8][8];

typedef enum {
    sh_leftx,
    sh_lefty,
    sh_leftz,
    sh_rightx,
    sh_righty,
    sh_rightz,
    sh_ovf        
} shift_t;

extern void img_copy(uint8_t p, uint8_t img[8][8]); // Copy img to matrix
extern void img_set(uint8_t mask, uint8_t img[8][8]); // Img reset
extern void img_inv(uint8_t img[8][8]); // Img inverse
extern void img_xor(uint8_t x, uint8_t img[8][8]); // XOR with variable
extern void img_shift(shift_t sh, uint8_t img[8][8]); // Shift image
extern void img_setpix(uint8_t x, uint8_t y, uint8_t z, uint8_t img[8][8], uint8_t val); // Set pixel
extern uint8_t img_getpix(uint8_t x, uint8_t y, uint8_t z, uint8_t img[8][8]); // Get pixel

#endif	/* IMG_H */
