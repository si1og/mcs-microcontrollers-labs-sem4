// MyBlink_def.c (optimized version)

//========== ОПРЕДЕЛЕНИЯ АДРЕСОВ РЕГИСТРОВ ==========

// Регистр включения тактирования портов
#define RCC_AHB1ENR (*(unsigned long*)0x40023830)

// Регистры режима работы портов (MODER)
#define GPIOG_MODER (*(unsigned long*)0x40021800)
#define GPIOH_MODER (*(unsigned long*)0x40021C00)
#define GPIOI_MODER (*(unsigned long*)0x40022000)

// Регистры управления выходами (ODR - Output Data Register)
#define GPIOG_ODR (*(unsigned long*)0x40021814)
#define GPIOH_ODR (*(unsigned long*)0x40021C14)
#define GPIOI_ODR (*(unsigned long*)0x40022014)

//========== ОПРЕДЕЛЕНИЯ МАСОК ДЛЯ ТАКТИРОВАНИЯ ==========

#define RCC_GPIOG_EN 0x40   // Бит 6 - включение порта G
#define RCC_GPIOH_EN 0x80   // Бит 7 - включение порта H
#define RCC_GPIOI_EN 0x100  // Бит 8 - включение порта I

//========== ОПРЕДЕЛЕНИЯ МАСОК ДЛЯ НАСТРОЙКИ РЕЖИМОВ ==========

// Порт G - маски для MODER (настройка как выход)
#define GPIOG_MODER_PG6_CLEAR (3 << 12)  // Очистка битов 12-13
#define GPIOG_MODER_PG6_OUT   (1 << 12)  // Установка PG6 как выход (01)
#define GPIOG_MODER_PG7_CLEAR (3 << 14)  // Очистка битов 14-15
#define GPIOG_MODER_PG7_OUT   (1 << 14)  // Установка PG7 как выход (01)
#define GPIOG_MODER_PG8_CLEAR (3 << 16)  // Очистка битов 16-17
#define GPIOG_MODER_PG8_OUT   (1 << 16)  // Установка PG8 как выход (01)

// Порт H - маски для MODER
#define GPIOH_MODER_PH2_CLEAR (3 << 4)   // Очистка битов 4-5
#define GPIOH_MODER_PH2_OUT   (1 << 4)   // Установка PH2 как выход
#define GPIOH_MODER_PH3_CLEAR (3 << 6)   // Очистка битов 6-7
#define GPIOH_MODER_PH3_OUT   (1 << 6)   // Установка PH3 как выход
#define GPIOH_MODER_PH6_CLEAR (3 << 12)  // Очистка битов 12-13
#define GPIOH_MODER_PH6_OUT   (1 << 12)  // Установка PH6 как выход
#define GPIOH_MODER_PH7_CLEAR (3 << 14)  // Очистка битов 14-15
#define GPIOH_MODER_PH7_OUT   (1 << 14)  // Установка PH7 как выход

// Порт I - маски для MODER
#define GPIOI_MODER_PI10_CLEAR (3 << 20) // Очистка битов 20-21
#define GPIOI_MODER_PI10_OUT   (1 << 20) // Установка PI10 как выход

//========== ОПРЕДЕЛЕНИЯ МАСОК ДЛЯ УПРАВЛЕНИЯ СВЕТОДИОДАМИ ==========

// Порт G - светодиоды
#define LED_PG6  0x40   // Бит 6 (0x40 = 0100 0000)
#define LED_PG7  0x80   // Бит 7 (0x80 = 1000 0000)
#define LED_PG8  0x100  // Бит 8 (0x100 = 1 0000 0000)

// Порт H - светодиоды
#define LED_PH2  0x04   // Бит 2 (0x04 = 0000 0100)
#define LED_PH3  0x08   // Бит 3 (0x08 = 0000 1000)
#define LED_PH6  0x40   // Бит 6 (0x40 = 0100 0000)
#define LED_PH7  0x80   // Бит 7 (0x80 = 1000 0000)

// Порт I - светодиоды
#define LED_PI10 0x400  // Бит 10 (0x400 = 100 0000 0000)

// Комбинированные маски для групп светодиодов
#define LEDS_PORTG_ALL (LED_PG6 | LED_PG7 | LED_PG8)
#define LEDS_PORTH_ALL (LED_PH2 | LED_PH3 | LED_PH6 | LED_PH7)
#define LEDS_PORTI_ALL (LED_PI10)

// Маски для пар светодиодов
#define LEDS_PAIR1 (LED_PH3 | LED_PH6)  // Пара 1: PH3, PH6
#define LEDS_PAIR2 (LED_PH7 | LED_PI10) // Пара 2: PH7, PI10 (разные порты!)
#define LEDS_PAIR3 (LED_PG6 | LED_PG7)  // Пара 3: PG6, PG7
#define LEDS_PAIR4 (LED_PG8 | LED_PH2)  // Пара 4: PG8, PH2 (разные порты!)

//========== ОСНОВНАЯ ПРОГРАММА ==========

int main()
{
    int i;
    unsigned long int j;

    i = 0;
    j = 0;

    //========== 1. ВКЛЮЧЕНИЕ ТАКТИРОВАНИЯ ПОРТОВ ==========
    RCC_AHB1ENR |= (RCC_GPIOG_EN | RCC_GPIOH_EN | RCC_GPIOI_EN);

    for (i = 0; i < 4; i++) {} // Задержка для готовности GPIO

    //========== 2. НАСТРОЙКА ПИНОВ КАК ВЫХОДОВ ==========
    
    // Порт G: настраиваем PG6, PG7 и PG8
    GPIOG_MODER &= ~(GPIOG_MODER_PG6_CLEAR | GPIOG_MODER_PG7_CLEAR | GPIOG_MODER_PG8_CLEAR);
    GPIOG_MODER |=  (GPIOG_MODER_PG6_OUT   | GPIOG_MODER_PG7_OUT   | GPIOG_MODER_PG8_OUT);
    
    // Порт H: настраиваем PH2, PH3, PH6, PH7
    GPIOH_MODER &= ~(GPIOH_MODER_PH2_CLEAR | GPIOH_MODER_PH3_CLEAR | 
                     GPIOH_MODER_PH6_CLEAR | GPIOH_MODER_PH7_CLEAR);
    GPIOH_MODER |=  (GPIOH_MODER_PH2_OUT   | GPIOH_MODER_PH3_OUT   | 
                     GPIOH_MODER_PH6_OUT   | GPIOH_MODER_PH7_OUT);
    
    // Порт I: настраиваем PI10
    GPIOI_MODER &= ~GPIOI_MODER_PI10_CLEAR;
    GPIOI_MODER |=  GPIOI_MODER_PI10_OUT;

    // Инициализируем все светодиоды выключенными перед циклом
    GPIOG_ODR &= ~LEDS_PORTG_ALL;
    GPIOH_ODR &= ~LEDS_PORTH_ALL;
    GPIOI_ODR &= ~LEDS_PORTI_ALL;

    //========== 3. ОСНОВНОЙ ЦИКЛ УПРАВЛЕНИЯ СВЕТОДИОДАМИ ==========
    while (1)
    {
        // --- ШАГ 1: Включить пару 1 (PH3, PH6) ---
        GPIOH_ODR |= LEDS_PAIR1;       // Включить PH3, PH6
        for (j = 0; j < 4000000; j++) {}

        // Выключить пару 1 перед шагом 2
        GPIOH_ODR &= ~LEDS_PAIR1;

        // --- ШАГ 2: Включить пару 2 (PH7, PI10) ---
        GPIOH_ODR |= LED_PH7;          // Включить PH7
        GPIOI_ODR |= LED_PI10;         // Включить PI10
        for (j = 0; j < 4000000; j++) {}

        // Выключить пару 2 перед шагом 3
        GPIOH_ODR &= ~LED_PH7;
        GPIOI_ODR &= ~LED_PI10;

        // --- ШАГ 3: Включить пару 3 (PG6, PG7) ---
        GPIOG_ODR |= LEDS_PAIR3;       // Включить PG6, PG7
        for (j = 0; j < 4000000; j++) {}

        // Выключить пару 3 перед шагом 4
        GPIOG_ODR &= ~LEDS_PAIR3;

        // --- ШАГ 4: Включить пару 4 (PG8, PH2) ---
        GPIOG_ODR |= LED_PG8;          // Включить PG8
        GPIOH_ODR |= LED_PH2;          // Включить PH2
        for (j = 0; j < 4000000; j++) {}

        // Выключить пару 4 перед возвратом к шагу 1
        GPIOG_ODR &= ~LED_PG8;
        GPIOH_ODR &= ~LED_PH2;
    }
}