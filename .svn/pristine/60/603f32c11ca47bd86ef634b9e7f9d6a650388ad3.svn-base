#include "alarm_task.h"
#include "sensor_task.h"
#include "beeper.h"
#include <ch.h>
#include <hal.h>
#include <stdlib.h>

#define HYSTERESIS 500

static bool g_alarm_active;
static int g_alarm_limit;

void alarm_set_limit(int temperature)
{
    if (temperature != g_alarm_limit)
    {
        chSysLock();
        g_alarm_limit = temperature;
        g_alarm_active = false;
        chSysUnlock();
    }
}

static bool alarm_keep_going()
{
    int temp, time;
    bool wireless;
    
    if (!sensor_get_temperature(&temp, &time, &wireless))
        g_alarm_active = false;
    
    if (chThdShouldTerminate())
        g_alarm_active = false;
    
    return g_alarm_active;
}

static Thread *alarmThread = 0;
static WORKING_AREA(alarmThread_wa, 256);

static msg_t alarm_task(void *arg)
{
    int sign = 0;
    
    chRegSetThreadName("alarm");
    
    while (!chThdShouldTerminate())
    {
        int temp, time;
        bool wireless;
        if (sensor_get_temperature(&temp, &time, &wireless))
        {
            int diff = temp - g_alarm_limit;
            int newsign = 0;
            
            if (diff > HYSTERESIS)
                newsign = +1;
            else if (diff < -HYSTERESIS)
                newsign = -1;
            else
                newsign = 0;
            
            if (sign != 0 && newsign != sign)
            {
                g_alarm_active = true;
                beeper_midi(&alarm_keep_going);
            }
            
            sign = newsign;
        }
        
        chThdSleepMilliseconds(100);
    }
    
    return 0;
}

void alarm_start()
{
    if (alarmThread != NULL)
        return;
    
    g_alarm_active = false;
    
    alarmThread = chThdCreateStatic(alarmThread_wa, sizeof(alarmThread_wa),
                                    NORMALPRIO + 5, alarm_task, NULL);
}

void alarm_stop()
{
    if (alarmThread)
    {
        chThdTerminate(alarmThread);
        chThdWait(alarmThread);
        alarmThread = NULL;
    }
}
