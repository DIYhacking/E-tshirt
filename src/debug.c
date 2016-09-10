#include "stm32l1xx.h"

void usart1_putstring(const char *p)
{
    while (*p)
    {
        while(!(USART1->SR & USART_SR_TXE));
        USART1->DR=*p;
        p++;
    }
}

void reboot()
{
    SCB->AIRCR = 0x05FA0000 | SCB_AIRCR_SYSRESETREQ;
}

void **HARDFAULT_PSP;
register void *stack_pointer asm("sp");

void __attribute__((naked)) HardFaultVector()
{
    // Hijack the process stack pointer to make backtrace work
    asm("mrs %0, psp" : "=r"(HARDFAULT_PSP) : :);
    usart1_putstring("\r\nHARDFAULT\r\n");
    (void)SCB->HFSR;
    
    stack_pointer = HARDFAULT_PSP;
    reboot();
}

void NMIVector(void) __attribute__((alias("HardFaultVector")));
void MemManageVector(void) __attribute__((alias("HardFaultVector")));
void BusFaultVector(void) __attribute__((alias("HardFaultVector")));
void UsageFaultVector(void) __attribute__((alias("HardFaultVector")));
