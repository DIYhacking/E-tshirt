#include "battery.h"
#include <hal.h>
#include <ch.h>

static const ADCConversionGroup g_adcconvgrp = {
    0,                                      // Circular
    1,                                      // Number of channels
    NULL,                                   // Callback
    NULL,                                   // Error callback
    0,                                      // CR1
    ADC_CR2_SWSTART | ADC_CR2_DELS_0,       // CR2
    0,                                      // SMPR1
    ADC_SMPR2_SMP_VREF(ADC_SAMPLE_384),     // SMPR2
    0,                                      // SMPR3
    ADC_SQR1_NUM_CH(1),                     // SQR1
    0,                                      // SQR2
    0,                                      // SQR3
    0,                                      // SQR4
    ADC_SQR5_SQ1_N(ADC_CHANNEL_VREFINT)     // SQR5
};

int battery_vcc_voltage()
{
    ADC->CCR |= ADC_CCR_TSVREFE;
    chThdSleepMilliseconds(10);
    
    adcsample_t buf;
    adcAcquireBus(&ADCD1);
    adcConvert(&ADCD1, &g_adcconvgrp, &buf, 1);
    adcConvert(&ADCD1, &g_adcconvgrp, &buf, 1);
    adcReleaseBus(&ADCD1);
    
    ADC->CCR &= ~ADC_CCR_TSVREFE;
    
    // buf = 4096 * 1224mV / Vcc
    // => Vcc = 1224mV * 4096 / buf;
    return 1224 * 4096 / buf;
}

bool battery_low()
{
    return battery_vcc_voltage() < 3100;
}