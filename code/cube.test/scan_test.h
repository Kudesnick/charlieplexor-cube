#ifndef SCAN_TEST_H
#define SCAN_TEST_H

#include <stdint.h>
#include "../cube.X/scan.h"
#include "../cube.X/map.h"
#include "xc.h"

// internal variables from "scan.c"
extern outbuf_t buffer0;
extern outbuf_t buffer1;
extern outbuf_t *out[2];
extern uint8_t ptr;

extern int scan_test(void);

#endif // SCAN_TEST_H
