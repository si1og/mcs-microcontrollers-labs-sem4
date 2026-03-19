/*--------------------------------------------------------------
 * Name:    BlinkyLed.c
 * Purpose: LED PG7 Flasher for MCBSTM32F200
 *--------------------------------------------------------------*/

#define RCCAHB1_ENR   (*(unsigned long*)0x40023830)
#define RCCAHB1_PORTG 0x40

#define GPIOG_MODER   (*(unsigned long*)0x40021800)
#define GPIOG_ODR     (*(unsigned long*)0x40021814)

#define PG7_MODE_MASK 0x00008000
#define PG7_MODE_OUT  0x00004000
#define PG7_PIN       0x80

#define DELAY_COUNT   2000000

/*--------------------------------------------------------------
   Main function
 *--------------------------------------------------------------*/
int main()
{
    int i;
    unsigned long int j;

    i = 0;
    j = 0;

    //--- Main cycle of algorithm ---

    RCCAHB1_ENR |= RCCAHB1_PORTG; // Enable port G clocking

    for (i = 0; i < 4; i++) {} // Small delay for GPIOG get ready

    GPIOG_MODER = (GPIOG_MODER & (~PG7_MODE_MASK)) | PG7_MODE_OUT; // Set PG7 as General purpose output

    while (1)
    {
        GPIOG_ODR |= PG7_PIN;  // Turn LED ON!

        for (j = 0; j < DELAY_COUNT; j++) {} // Delay

        GPIOG_ODR &= ~PG7_PIN; // Turn LED OFF

        for (j = 0; j < DELAY_COUNT; j++) {} // Delay
    }
}
