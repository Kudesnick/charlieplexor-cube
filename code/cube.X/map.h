#ifndef MAP_H
#define	MAP_H

#include <stdint.h>

typedef struct{
    const uint8_t col:5; // column number
    const uint8_t row:3; // row number
    const uint8_t mask;
} remap_t;

extern const remap_t remap[8][8];

#endif	/* MAP_H */

