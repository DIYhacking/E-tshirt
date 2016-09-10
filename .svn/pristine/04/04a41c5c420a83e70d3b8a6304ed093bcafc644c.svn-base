#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gfx.h>
#include "shell_commands.h"
#include "tempgraph.h"
#include "buttons.h"
#include "ntc.h"
#include "beeper.h"
#include "battery.h"
#include "display.h"
#include "sensor_task.h"

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
    size_t n, size;

    n = chHeapStatus(NULL, &size);
    chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
    chprintf(chp, "heap fragments   : %u\r\n", n);
    chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

extern unsigned long __main_thread_stack_base__, __main_thread_stack_end__; // From linker script
static void thread_free_stack(Thread *thread, int *free_stack_now, int *free_stack_min)
{
    uint32_t current_sp = (uint32_t)thread->p_ctx.r13;
    uint32_t stack_bottom;
    if (current_sp >= (uint32_t)&__main_thread_stack_base__
        && current_sp <= (uint32_t)&__main_thread_stack_end__)
        stack_bottom = (uint32_t)&__main_thread_stack_base__;
    else
        stack_bottom = (uint32_t)(thread + 1);
    
    *free_stack_now = current_sp - stack_bottom;
    
    uint32_t *stackentry = (uint32_t*)stack_bottom;
    uint32_t empty_val = *stackentry;
    while (*stackentry == empty_val) stackentry++;
    *free_stack_min = (uint32_t)stackentry - stack_bottom;
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
    static const char *states[] = {THD_STATE_NAMES};
    Thread *tp;

    chprintf(chp, "             addr    stack prio     state time      free stack now/min\r\n");
    tp = chRegFirstThread();
    do {
        int stacknow, stackmin;
        thread_free_stack(tp, &stacknow, &stackmin);
        
        chprintf(chp, "%8s %.8lx %.8lx %4lu %9s %8lu %lu/%lu\r\n",
            tp->p_name, (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
            (uint32_t)tp->p_prio,
            states[tp->p_state], (uint32_t)tp->p_time,
            stacknow, stackmin);
        tp = chRegNextThread(tp);
    } while (tp != NULL);
}

static void cmd_reboot(BaseSequentialStream *chp, int argc, char *argv[])
{
    SCB->AIRCR = 0x05FA0000 | SCB_AIRCR_SYSRESETREQ;
}

static void cmd_buttons(BaseSequentialStream *chp, int argc, char *argv[])
{
    buttons_t btn;
    
    do {
        btn = buttons_read_buffer();
        chprintf(chp, "buttons = %d\n", btn);
    } while (btn != BT_NONE);
}

static bool beep_cb()
{
    return buttons_read_buffer() == BT_NONE;
}

static void cmd_beep(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 3)
    {
        chprintf(chp, "Usage: beep <freq> <decay> <length>\n");
        
        beeper_midi(beep_cb);
        return;
    }
    
    beeper_bling(atoi(argv[0]), atoi(argv[1]), atoi(argv[2]), 100);
}

static void cmd_ntc(BaseSequentialStream *chp, int argc, char *argv[])
{
    chprintf(chp, "%d mC\n", ntc_read());
}

static void cmd_temperature(BaseSequentialStream *chp, int argc, char *argv[])
{
    int temperature;
    int timestamp;
    bool wireless;
    
    if (sensor_get_temperature(&temperature, &timestamp, &wireless))
    {
        chprintf(chp, "%d mC, %d s ago, wireless=%d\n", temperature, rtc_get() - timestamp, wireless);
    }
    else
    {
        chprintf(chp, "no data\n");
    }
}

static void cmd_battery(BaseSequentialStream *chp, int argc, char *argv[])
{
    chprintf(chp, "Vcc = %d mV, battery_low = %d\n",
             battery_vcc_voltage(), battery_low());
}

static void cmd_data(BaseSequentialStream *chp, int argc, char *argv[])
{
    display_export_csv(chp);
}

const ShellCommand shell_commands[] = {
  {"mem", cmd_mem},
  {"threads", cmd_threads},
  {"reboot", cmd_reboot},
  {"buttons", cmd_buttons},
  {"beep", cmd_beep},
  {"ntc", cmd_ntc},
  {"temperature", cmd_temperature},
  {"battery", cmd_battery},
  {"data", cmd_data},
  {NULL, NULL}
};
