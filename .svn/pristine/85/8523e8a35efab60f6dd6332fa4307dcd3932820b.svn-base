/* Reading of the button states */

#pragma once

typedef enum {
    BT_NONE = 0,
    BT_POWER = 1,
    BT_CLEAR = 2,
    BT_PLUS = 4,
    BT_MINUS = 8
} buttons_t;

/* Synchronous API */
buttons_t buttons_read_immediate();

/* Asynchronous (buffering) API */
buttons_t buttons_read_buffer();
void buttons_clear_buffer();

void buttons_start();
void buttons_stop();
