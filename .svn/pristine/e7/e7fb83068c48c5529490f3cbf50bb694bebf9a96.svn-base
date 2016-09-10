#include "powersave.h"
#include <ch.h>
#include <hal.h>
#include <gfx.h>
#include "stm32l_rtc.h"
#include "buttons.h"
#include "sensor_task.h"
#include "alarm_task.h"
#include "beeper.h"
#include "display.h"
#include "usb_usart.h"

volatile systime_t g_last_keep_alive = 0;

void powersave_keep_alive()
{
    chSysLock();
    g_last_keep_alive = chTimeNow();
    chSysUnlock();
}

bool powersave_should_sleep()
{
    chSysLock();
    systime_t time = g_last_keep_alive;
    chSysUnlock();
    
    time = chTimeNow() - time;
    return time > S2ST(4 * 3600);
}

void powersave_sleep()
{
    gdispSetPowerMode(powerOn);
    gdispClear(1);
    gdispSetPowerMode(powerOff);
    
    // Stop most of the tasks
    buttons_stop();
    sensor_stop();
    alarm_stop();
    stop_usb_usart(); // Will be restarted automatically if connected.
    beeper_deinit();
    
    // Sleep until the power button is pressed; keep resetting watchdog.
    buttons_t button;
    do
    {
        adcStop(&ADCD1);
        
        // Stop the kernel
        chSysLock();
        
        // Store old GPIO states
        uint32_t gpioa_moder = GPIOA->MODER;
        uint32_t gpioa_odr = GPIOA->ODR;
        uint32_t gpiob_moder = GPIOB->MODER;
        uint32_t gpiob_odr = GPIOB->ODR;
        
        // Make sure that important IO pins are in the states that we want.
        palSetPadMode(GPIOA, GPIOA_BUTTONS, PAL_MODE_INPUT);
        palSetPadMode(GPIOA, GPIOA_SPEAKER_OUT, PAL_MODE_INPUT);
        palSetPadMode(GPIOA, GPIOA_NTC_POWER, PAL_MODE_INPUT);
        palSetPadMode(GPIOA, GPIOA_USBDM, PAL_MODE_INPUT_ANALOG);
        palSetPadMode(GPIOA, GPIOA_USBDP, PAL_MODE_INPUT_ANALOG);
        palSetPadMode(GPIOA, GPIOA_SWDIO, PAL_MODE_INPUT_ANALOG);
        palSetPadMode(GPIOA, GPIOA_SWCLK, PAL_MODE_INPUT_ANALOG);
        palClearPad(GPIOA, GPIOA_RF_POWER);
        palSetPadMode(GPIOA, GPIOA_EINK_VDD, PAL_MODE_INPUT_PULLDOWN);
        palSetPadMode(GPIOB, GPIOB_EINK_PWR, PAL_MODE_INPUT);
    
        IWDG->KR = 0xAAAA; // Reset watchdog
        
        rtc_sleep(15000); // Sleep 15 sec or until button press
        
        // Restore GPIO states
        GPIOA->MODER = gpioa_moder;
        GPIOA->ODR = gpioa_odr;
        GPIOB->MODER = gpiob_moder;
        GPIOB->ODR = gpiob_odr;
        
        // Resume normal operations
        chSysUnlock();
        
        adcStart(&ADCD1, NULL);
        
        // Check if a button was pressed
        if (palReadPad(GPIOA, GPIOA_BUTTONS))
            button = buttons_read_immediate();
        else
            button = BT_NONE;
    } while (button != BT_POWER);
    
    // Acknowledge button press
    beeper_init();
    beeper_click();
    powersave_keep_alive();
    
    // Wait for button release
    while (palReadPad(GPIOA, GPIOA_BUTTONS))
        chThdSleepMilliseconds(50);
    
    // Restart the core tasks
    buttons_clear_buffer();
    buttons_start();
    sensor_start();
    alarm_start();
    
    // If there is no saved graph, start a new measurement immediately.
    if (display_samplecount() <= 2)
    {
        sensor_reset_timestamp();
        display_clear();
    }
    
    // Redraw display contents
    display_full_redraw();
}
