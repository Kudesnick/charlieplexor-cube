#ifndef SCAN_H
#define	SCAN_H

typedef uint8_t imgbuf_t[8][8];
typedef uint8_t outbuf_t[3][24];

extern void scan_irq(void); // Scaning LED matrix
extern void scan_res(uint8_t p, uint8_t mask); // Matrix reset
extern void scan_inv(uint8_t p); //Matrix inversion
extern void scan_copy(uint8_t p, uint8_t img[8][8]); // Copy img to matrix

#endif	/* SCAN_H */
