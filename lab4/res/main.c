#include "stm32f2xx.h"
#include <stdbool.h>

static volatile bool sleep_mode = false;

void delay_ms(uint32_t milliseconds)
{
    volatile uint32_t i;
    for (i = 0; i < (milliseconds * 4200U); i++) {
        __NOP();
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF) {
        GPIOG->ODR ^= (1U << 6) | (1U << 7);
        TIM2->SR &= ~TIM_SR_UIF;
    }
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR0) {
        delay_ms(100);

        if (!sleep_mode) {
            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
            EXTI->RTSR &= ~EXTI_RTSR_TR0;
            EXTI->FTSR |= EXTI_FTSR_TR0;
            sleep_mode = true;
        } else {
            SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            EXTI->RTSR |= EXTI_RTSR_TR0;
            EXTI->FTSR &= ~EXTI_FTSR_TR0;
            sleep_mode = false;
        }

        EXTI->PR = EXTI_PR_PR0;
    }
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOGEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    GPIOG->MODER &= ~((3U << (6 * 2)) | (3U << (7 * 2)));
    GPIOG->MODER |=  ((1U << (6 * 2)) | (1U << (7 * 2)));
    GPIOA->MODER &= ~(3U << (0 * 2));

    TIM2->PSC = 119990U;
    TIM2->ARR = 249U;
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->FTSR |= EXTI_FTSR_TR0;

    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);

    while (1) {
        __WFI();
    }
}
