#include <stdio.h>
#include <stdlib.h>
#include "scan_test.h"

int main()
{
    int r;
    printf("Unit test run..\n");
    r = scan_test();
    if (r == 0)
        printf("Unit test O'k.\n");
    else
        printf("Unit test error!\n");
    return r;
}
