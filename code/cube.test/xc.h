#ifndef XC_H
#define XC_H

#include <stdint.h>

typedef union{
    uint32_t uint32;
    uint8_t uint8[4];
} ports_t;

extern ports_t PORT;
extern ports_t TRIS;

#define PORTB PORT.uint8[0]
#define PORTC PORT.uint8[1]
#define PORTD PORT.uint8[2]
#define TRISB TRIS.uint8[0]
#define TRISC TRIS.uint8[1]
#define TRISD TRIS.uint8[2]

#endif // XC_H
