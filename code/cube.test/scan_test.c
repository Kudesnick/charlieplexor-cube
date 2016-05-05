#include <stdio.h>
#include <stdint.h>
#include "scan_test.h"

imgbuf_t image;

static int scan_res_test(void)
{
    int r = 0;
    printf("    Function \"scan_res\" test run..\n");
    for (int p = 1; p >= 0; --p)
        for (int mask = 255; mask >= 0; --mask)
        {
            scan_res(p, mask);
            for (int x = 2; x >= 0; --x)
                for (int y = 23; y >= 0; --y)
                {
                    if (p == 0)
                        {if (buffer0[x][y] != mask) r = 1;}
                    else
                        {if (buffer1[x][y] != mask) r = 2;}
                }
        }
    if (r == 0)
        printf("    Function \"scan_res\" O'k.\n");
    else
        printf("    Function \"scan_res\" Error.\n");
    return r;
}

static int scan_inv_test(void)
{
    int r = 0;
    printf("    Function \"scan_inv\" test run..\n");
    for (int p = 1; p >= 0; --p)
        for (int mask = 255; mask >= 0; --mask)
        {
            scan_res(p, mask);
            scan_inv(p);
            for (int x = 2; x >= 0; --x)
                for (int y = 23; y >= 0; --y)
                {
                    uint8_t mskinv = ~mask;
                    if (p == 0)
                        {if (buffer0[x][y] != mskinv) r = 1;}
                    else
                        {if (buffer1[x][y] != mskinv) r = 2;}
                }
        }
    if (r == 0)
        printf("    Function \"scan_inv\" O'k.\n");
    else
        printf("    Function \"scan_inv\" Error.\n");
    return r;
}

static int scan_irq_test(void)
{
    ports_t tPORT;
    ports_t tTRIS;
    int r = 0;
    printf("    Function \"scan_irq\" test run..\n");
    tPORT.uint32 = 1;
    for (int n = 0xFF; n >= 0; --n)
    {
        scan_res(0, n);
        for (int stp = 0; stp < 24; ++stp)
        {
            scan_irq();
            // Testing
            if ((PORT.uint32 ^ tPORT.uint32) != 0xFFFFFF) r = 1;
            tTRIS.uint32 = (((buffer0[2][stp] << 8) | buffer0[1][stp]) << 8) | buffer0[0][stp];
            if ((TRIS.uint32 ^ (tTRIS.uint32 | tPORT.uint32)) != 0xFFFFFF) r = 2;
            // End testing
            scan_inv(0);
            tPORT.uint32 <<= 1;
            if (tPORT.uint32 >= (1<<24)) tPORT.uint32 = 1;
        }
    }
    if (r == 0)
        printf("    Function \"scan_irq\" O'k.\n");
    else
        printf("    Function \"scan_irq\" Error.\n");
    return r;
}

static int scan_copy_test(void)
{
    int r = 0;
    printf("    Function \"scan_copy\" test run..\n");
    for (int i = 255; i >= 0; --i)
    {
        uint8_t mask = i;
        for (int x = 7; x >= 0; --x)
            for (int y = 7; y >= 0; --y)
                image[x][y] = mask--;
        scan_copy(0, image);
        for (int x = 7; x >= 0; --x)
            for (int y = 7; y >= 0; --y)
            {
                if ((buffer0[remap[x][y].row][remap[x][y].col] & ~remap[x][y].mask) != (image[x][y] & ~remap[x][y].mask)) r = 1;
                if (remap[x][y].mask == 0) continue;
                if ((buffer0[remap[x][y].row][remap[x][y].col-1] & remap[x][y].mask) != (image[x][y] & remap[x][y].mask)) r = 2;
            }
    }
    if (r == 0)
        printf("    Function \"scan_copy\" O'k.\n");
    else
        printf("    Function \"scan_copy\" Error.\n");
    return r;
}

// Main test function
int scan_test(void)
{
    int r = 0;
    printf("  Unit \"scan.c\" test run..\n");
        r += scan_res_test();
        r += scan_inv_test();
        r += scan_irq_test();
        r += scan_copy_test();
    if (r == 0)
        printf("  Unit \"scan.c\" test O'k.\n");
    else
        printf("  Unit \"scan.c\" test error!\n");
    return r;
}
