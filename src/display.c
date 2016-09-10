#include "display.h"
#include "sensor_task.h"
#include <ch.h>
#include <hal.h>
#include <gfx.h>
#include <chprintf.h>
#include <stdio.h>
#include <stdlib.h>
//#include "../chibios/os/hal/osal/nil/osal.h"

#define INVALID_TEMPERATURE -999999

static font_t bigfont;
static font_t mediumfont;

volatile static unsigned long sampleCount = 0;
volatile unsigned long lastCount = 0;
static int flag=0;
static int lastTemp;

struct ephemerals
{
    int prev_temperature;
    int prev_gsr;
    int prev_pulse;
    char pulse[4];
    char gsr[4];
    char temperature[8];
    char alarm[4];
    int alarm_temp;
    char alarmtime[16];
    bool batt_low;
    
    int samplecount;
    int timescale; // Minimum number of seconds between samples
    
    bool need_full_update;
    
    bool alarm_white_on_black; // Persistence reduction
    
    int xrange; // Seconds on X axis
    int ymin;
    int ymax;
    
    bool have_prediction;
    int pred_x0;
    int pred_y0;
    int pred_uc_per_sec;
};

static struct ephemerals g_ephemerals;
static struct ephemerals g_prev_ephemerals;

struct tempsample
{
    int time;
    int temperature;
};

#define SAMPLECOUNT 100
static struct tempsample g_samples[SAMPLECOUNT];

void display_init()
{
    bigfont = gdispOpenFont("bigfont");
    mediumfont = gdispOpenFont("mediumfont");

    display_clear();
}

void display_clear()
{
    display_update_temperature();
    g_ephemerals.need_full_update = true;

}

int display_samplecount()
{
    return g_ephemerals.samplecount;
}

void display_export_csv(BaseSequentialStream *chp)
{
    int count = g_ephemerals.samplecount;
    
    chprintf(chp, "# Time(s), Temperature(mC)\r\n");
    
    for (int i = 0; i < count; i++)
    {
        chprintf(chp, "%8d, %8d\r\n", g_samples[i].time, g_samples[i].temperature);
    }
}

void display_update_temperature()
{
    
    bool have_temp = true;
    int heart, tempp;
    float gsr2;
    pass_heart_temp(&heart, &tempp, &gsr2);
    int rate= heart;

    int temper= tempp;
    int gsr3=gsr2;

    if (have_temp)
    {
        int timedelta = 9999;

            snprintf(g_ephemerals.temperature, sizeof(g_ephemerals.temperature),
                    "%2d", temper);
            g_ephemerals.temperature[2] = '\0';//g_ephemerals.temperature[1];

            lastTemp=temper;

            snprintf(g_ephemerals.gsr, sizeof(g_ephemerals.gsr),
                                "%2d", gsr3);

            long map(long x, long in_min, long in_max, long out_min, long out_max)
            {
              return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
            }

            if(sampleCount==0)
            {
            	snprintf(g_ephemerals.pulse, sizeof(g_ephemerals.pulse),
                                                        "%2d", rate);//rate
            if(rate>99) flag=2;
            else if (rate<100) flag=1;
            }
            sampleCount += 70;
            if(sampleCount>300)
            sampleCount=0;


            g_ephemerals.prev_temperature = temper;
            g_ephemerals.prev_gsr = gsr3;
            g_ephemerals.prev_pulse = rate;
         }
    else
    {
        snprintf(g_ephemerals.temperature, sizeof(g_ephemerals.temperature),
                 " --,-");
        g_ephemerals.prev_temperature = INVALID_TEMPERATURE;
    }
}

void display_set_alarm(int celcius)
{
    g_ephemerals.alarm_temp = celcius * 1000;
    snprintf(g_ephemerals.alarm, sizeof(g_ephemerals.alarm), "%d", celcius);
}

static void draw_temp_digit(int i, char c)
{
    const uint8_t charw[5] = {70, 75, 75, 35, 75};
    const uint8_t charpos[5] = {155, 235, 145, 220, 255};
    int x = 6 + charpos[i];
    int y = 220;
    char buf[2] = {c,'\0'};
    //chSysLock();
    gdispFillArea(x, y - 1,72 , 100, 1);//charw[i],130
    gdispDrawString(x, y, buf, bigfont, 0);
//chSysUnlock();

}

static void draw_gsr_digit(int i, char c)
{
    const uint8_t charw[5] = {70, 75, 75, 35, 75};
    const uint16_t charpos[2] = {430, 460};
    int x = 6 + charpos[i];
    int y = 570;

    char buf[2] = {c,'\0'};
    //chSysLock();
    gdispFillArea(x, y,30 , 40, 1);//charw[i],130
    gdispDrawString(x, y, buf, mediumfont, 0);
//chSysUnlock();

}

static void draw_pulse_digit(int i, char c)
{
    const uint8_t charw[5] = {70, 75, 75, 35, 75};
    const uint16_t charpos[3] = {655, 735};//{655, 735};
    int x = 6 + charpos[i];
    int y = 220;

    char buf[2] = {c,'\0'};
    gdispFillArea(x, y - 1,72 , 100, 1);
    gdispFillArea(x, y - 1,72 , 100, 1);
    gdispFillArea(x, y - 1,72 , 100, 1);
    gdispFillArea(x, y - 1,72 , 100, 1);
    //chSysLock();
    gdispFillArea(x, y - 1,72 , 100, 1);//charw[i],130
    gdispDrawString(x, y, buf, bigfont, 0);
//chSysUnlock();

}

static void draw_pulse_digit2(int i, char c)
{
    const uint8_t charw[5] = {70, 75, 75, 35, 75};
    const uint16_t charpos[3] = {575, 655, 735};//{655, 735};
    int x = 6 + charpos[i];
    int y = 220;

    char buf[2] = {c,'\0'};gdispFillArea(x, y - 1,72 , 100, 1);
    gdispFillArea(x, y - 1,72 , 100, 1);
    gdispFillArea(x, y - 1,72 , 100, 1);
    gdispFillArea(x, y - 1,72 , 100, 1);
    //chSysLock();
    gdispFillArea(x, y - 1,72 , 100, 1);//charw[i],130
    gdispDrawString(x, y, buf, bigfont, 0);
//chSysUnlock();

}

void display_full_redraw()
{
    
    gdispSetPowerMode(powerOn);

    gdispClear(1);
    gdispClear(1);
    gdispClear(1);

   for(int i=0;i<4;i++)
   {
   gdispDrawCircle(252,250,250,0);
   gdispDrawCircle(754,250,250,0);
   gdispDrawCircle(500,600,170,0);
   gdispDrawString(170, 90, "SKIN", mediumfont, 0);
   gdispDrawString(70, 140, "TEMPERATURE", mediumfont, 0);
   gdispDrawString(320, 210, "°C", mediumfont, 0);
   gdispDrawString(100, 360, "Average = 34°C", mediumfont, 0);
  // gdispDrawString(170, 90, "BODY", mediumfont, 0);

   gdispDrawString(590, 90, "HEART RATE", mediumfont, 0);
   gdispDrawString(700, 140, "/min", mediumfont, 0);
   gdispDrawString(560, 360, "Average = 80bpm", mediumfont, 0);
   gdispDrawString(810, 210, "bpm", mediumfont, 0);

   gdispDrawString(400, 450, "galvanic", mediumfont, 0);
   gdispDrawString(440, 500, "skin", mediumfont, 0);
   gdispDrawString(400, 640, "response", mediumfont, 0);
   gdispDrawString(500, 570, "mV", mediumfont, 0);
   }

   for (int i = 0; i < 2; i++)// draws skin temperature
    {
        draw_temp_digit(i, g_ephemerals.temperature[i]);
    }
   for (int i = 0; i < 2; i++)// draws GSR value
    {
        draw_gsr_digit(i, g_ephemerals.gsr[i]);
    }
   int heart, tempp;
   float gsr2;
   pass_heart_temp(&heart, &tempp, &gsr2);

   int rate=heart;
   if(flag==2)//rate>99
   {
   for (int i = 0; i < 3; i++)//draws heart rate
      {
          draw_pulse_digit2(i, g_ephemerals.pulse[i]);
      }
   }
   else if (flag==1){
	   for (int i = 0; i < 2; i++)//5 actually
	         {
		 		   draw_pulse_digit(i, g_ephemerals.pulse[i]);
	         }
   }
   	  gdispDrawString(170, 90, "SKIN", mediumfont, 0);
      gdispDrawString(70, 140, "TEMPERATURE", mediumfont, 0);
      gdispDrawString(320, 210, "°C", mediumfont, 0);
      gdispDrawString(100, 360, "Average = 34°C", mediumfont, 0);
     // gdispDrawString(170, 90, "BODY", mediumfont, 0);

      gdispDrawString(590, 90, "HEART RATE", mediumfont, 0);
      gdispDrawString(700, 140, "/min", mediumfont, 0);
      gdispDrawString(560, 360, "Average = 80bpm", mediumfont, 0);
      gdispDrawString(810, 210, "bpm", mediumfont, 0);

      gdispDrawString(400, 450, "galvanic", mediumfont, 0);
      gdispDrawString(440, 500, "skin", mediumfont, 0);
      gdispDrawString(400, 640, "response", mediumfont, 0);
      gdispDrawString(500, 570, "mV", mediumfont, 0);

    gdispSetPowerMode(powerOff);

    g_ephemerals.need_full_update = false;
    g_prev_ephemerals = g_ephemerals;

 }

void display_partial_redraw()
{
	palClearPad(GPIOB, 6);
	if (g_ephemerals.need_full_update)
    {
    	display_full_redraw();
    	return;
    }

    gdispSetPowerMode(powerOn);

    for (int i = 0; i < 2; i++)//draws skin temperature
    {
       	draw_temp_digit(i, g_ephemerals.temperature[i]);

    }
    for (int i = 0; i < 2; i++)//draws GSR value
    {
         draw_gsr_digit(i, g_ephemerals.gsr[i]);
    }

    int heart, tempp;
    float gsr2;
    pass_heart_temp(&heart, &tempp, &gsr2);
    int rate=heart;

   if(flag==2)
    {
    for (int i = 0; i < 3; i++)//draws three digit heart rate
       {
           draw_pulse_digit2(i, g_ephemerals.pulse[i]);
       }
    }
    else if (flag==1){
 	   for (int i = 0; i < 2; i++)//draws two digit heart rate
 	         {
 		 		   draw_pulse_digit(i, g_ephemerals.pulse[i]);
 	         }
    }

    gdispSetPowerMode(powerOff);
    memcpy(&g_prev_ephemerals, &g_ephemerals, sizeof(g_ephemerals));

}
