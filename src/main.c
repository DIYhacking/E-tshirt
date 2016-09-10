#include <ch.h>
#include <hal.h>
#include <shell.h>
#include <gfx.h>
//#include "usb_usart.h"
#include "sensor_task.h"
#include "display.h"
#include "main_logic.h"
#include "stm32l1xx.h"

int main()
{


	SYSCFG->PMC = 0;
    halInit();
    chSysInit();

    //shellInit();
    gfxInit();

   gdispSetPowerMode(powerOff);

#if ENABLE_DEBUG
    DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP;
#endif
    
    DBGMCU->APB1FZ = 0xFFFFFFFF;
    DBGMCU->APB2FZ = 0xFFFFFFFF;
    
    // Enable watchdog (reset is done by button task)
   // IWDG->KR = 0x5555; // Enable watchdog register write
   // IWDG->PR = 6;
   // IWDG->RLR = 4095; // 30 seconds
   // IWDG->KR = 0xCCCC; // Start watchdog
    /*
     * Activates the serial driver 1 using the driver default configuration.
     * PA9(TX) and PA10(RX) are routed to USART1.
     */
     sdStart(&SD1, NULL);
     palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
     palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));
     adcStart(&ADCD1, NULL);

     display_init();
     sensor_start();

	adcStart(&ADCD1, NULL);

    main_logic_init();

    while (1)
    {
       chThdSleepMilliseconds(10);

       main_logic_step();

     /* palSetPad(GPIOB, 6);
        chThdSleepMilliseconds(1000);
        palClearPad(GPIOB, 6);
        chThdSleepMilliseconds(1000);
     */
    }
}
