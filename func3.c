#include "api.h"
#include <stdio.h>

void func3(int k)
{
    if(k > 10)
    {
        printf("calling func1 from func3\n");
        func1();
    }
    else
    {
        printf("calling func2 from func3\n");
        func2();
    }
}

