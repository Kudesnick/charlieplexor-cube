#include <stdint.h>
#include "img.h"

#define TIMEOUT 0xFFFF

imgbuf_t image;

void demo_init(void)
{
    img_set(0xFF, image);
    img_copy(0, image);
}

void demo_monitor(void)
{
    static uint16_t cnt = TIMEOUT;
    if (--cnt) return;
    cnt = TIMEOUT;
    {
        img_xor(0xFF, image);
        img_copy(0, image);
    }
}
