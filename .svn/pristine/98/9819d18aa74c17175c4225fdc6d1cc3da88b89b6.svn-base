/* Driver for the beeper connected to DAC */

#pragma once

#include <stdbool.h>

void beeper_init();
void beeper_deinit();

void beeper_click();

/* Play a guitarlike "bling", with given frequency (Hz),
 * decay time (ms), length (ms) and volume (%). */
void beeper_bling(int freq, int decay, int length, int volume);

/* Play a built-in midi song */
typedef bool (*keep_going_t)();
void beeper_midi(keep_going_t callback);