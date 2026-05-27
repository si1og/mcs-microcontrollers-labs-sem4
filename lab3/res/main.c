#include "stm32f2xx.h"

void delay(unsigned long time)
{
    volatile unsigned long i;
    for (i = 0; i < time; i++) {}
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR0) {
        GPIOG->ODR |=  (1 << 6);
        delay(3000000);
        GPIOG->ODR &= ~(1 << 6);
        EXTI->PR = EXTI_PR_PR0;
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR15) {
        GPIOG->ODR |=  (1 << 8);
        delay(3000000);
        GPIOG->ODR &= ~(1 << 8);
        EXTI->PR = EXTI_PR_PR15;
    }
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOGEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    GPIOG->MODER &= ~(3 << (6 * 2));
    GPIOG->MODER |=  (1 << (6 * 2));
    GPIOG->MODER &= ~(3 << (7 * 2));
    GPIOG->MODER |=  (1 << (7 * 2));
    GPIOG->MODER &= ~(3 << (8 * 2));
    GPIOG->MODER |=  (1 << (8 * 2));
    GPIOA->MODER &= ~(3 << (0 * 2));
    GPIOG->MODER &= ~(3 << (15 * 2));

    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PG;

    EXTI->IMR |= (1 << 0) | (1 << 15);
    EXTI->RTSR |= (1 << 0) | (1 << 15);
    EXTI->FTSR |= (1 << 0) | (1 << 15);

    NVIC_SetPriority(EXTI15_10_IRQn, 0);
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    while (1) {
        GPIOG->ODR |=  (1 << 7);
        delay(2000000);
        GPIOG->ODR &= ~(1 << 7);
        delay(2000000);
    }
}
