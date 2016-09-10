#include "ntc.h"
#include <hal.h>
#include <ch.h>

typedef struct {
    uint16_t adc_value;
    int16_t celcius;
} ntc_entry_t;

static const ntc_entry_t g_ntc_curve[] = {
    { 65052, -55}, { 64865, -50}, { 64617, -45}, { 64293, -40},
    { 63875, -35}, { 63342, -30}, { 62673, -25}, { 61843, -20},
    { 60829, -15}, { 59607, -10}, { 58160,  -5}, { 56473,   0},
    { 54539,   5}, { 52363,  10}, { 49959,  15}, { 47353,  20},
    { 44582,  25}, { 41691,  30}, { 38730,  35}, { 35753,  40},
    { 32810,  45}, { 29947,  50}, { 27203,  55}, { 24608,  60},
    { 22182,  65}, { 19939,  70}, { 17882,  75}, { 16011,  80},
    { 14319,  85}, { 12798,  90}, { 11436,  95}, { 10220, 100},
    {  9137, 105}, {  8175, 110}, {  7321, 115}, {  6564, 120},
    {  5892, 125}, {  5296, 130}, {  4768, 135}, {  4299, 140},
    {  3882, 145}, {  3511, 150}, {  3181, 155}, {  2887, 160},
    {  2625, 165}, {  2390, 170}, {  2180, 175}, {  1992, 180},
    {  1823, 185}, {  1670, 190}, {  1534, 195}, {  1410, 200},
    {  1298, 205}, {  1198, 210}, {  1106, 215}, {  1023, 220},
    {   948, 225}, {   879, 230}, {   816, 235}, {   759, 240},
    {   707, 245}, {   659, 250}, {   615, 255}, {   575, 260},
    {   538, 265}, {   504, 270}, {   473, 275}, {   444, 280},
    {   417, 285}, {   393, 290}, {   370, 295}, {   349, 300},
    {0, 0}
};

static int linear_interpolate(const ntc_entry_t *table, int adc_value)
{
    const ntc_entry_t *p = table;
    while (p[1].adc_value > adc_value && p[2].adc_value != 0)
    {
        p++;
    }
    
    int y1 = p[0].celcius * 1000;
    int y2 = p[1].celcius * 1000;
    int x1 = p[0].adc_value;
    int x2 = p[1].adc_value;
    
    int x = adc_value;
    int y = y1 + (x - x1) * (y2 - y1)/ (x2 - x1);
    return y;
}

static const ADCConversionGroup convgrp = {
    0,
    1,
    NULL,
    NULL,
    
    // CR
    0,
    ADC_CR2_SWSTART | ADC_CR2_DELS_0,
    
    // SMPR
    0,
    0,
    ADC_SMPR3_SMP_AN0(ADC_SAMPLE_16),
    
    // SQR
    ADC_SQR1_NUM_CH(1),
    0,
    0,
    0,
    ADC_SQR5_SQ1_N(ADC_CHANNEL_IN6)
};

static int adc_oversample()
{
    int sum = 0;
    // Oversample by 256 and divide by 16 to get 4 more bits of accuracy.
    for (int i = 0; i < 16; i++)
    {
        adcsample_t buf[16];
        
        adcAcquireBus(&ADCD1);
        adcConvert(&ADCD1, &convgrp, buf, 16);
        adcReleaseBus(&ADCD1);
        
        for (int j = 0; j < 16; j++)
        {
            sum += buf[j];
        }
    }
    
    return (sum + 8) / 16;
}

bool ntc_connected()
{
    palSetPad(GPIOA, GPIOA_NTC_POWER);
    chThdSleepMilliseconds(50);
    
    adcsample_t buf;
    adcAcquireBus(&ADCD1);
    adcConvert(&ADCD1, &convgrp, &buf, 1);
    adcReleaseBus(&ADCD1);
    
    palClearPad(GPIOA, GPIOA_NTC_POWER);
    
    if (buf > 4090)
        return false;
    else
        return true;
}

int ntc_read()
{
    palSetPad(GPIOA, GPIOA_NTC_POWER);
    chThdSleepMilliseconds(50);
    int val = adc_oversample();
    palClearPad(GPIOA, GPIOA_NTC_POWER);
    
    return linear_interpolate(g_ntc_curve, val);
}
