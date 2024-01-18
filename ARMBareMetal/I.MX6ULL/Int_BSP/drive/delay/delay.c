#include "delay.h"

/* 主频396MHz约为1us */
void Delay_Us(volatile unsigned int n)
{
    n *= 2;
    while(n--);
}
/* 主频396MHz约为1ms */
void Delay_Ms(volatile unsigned int n)
{
    while(n--)
    {
        Delay_Us(800);
    }
}
