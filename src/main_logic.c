#include "main_logic.h"
#include <ch.h>
#include <hal.h>
#include "display.h"
#include "sensor_task.h"

void main_logic_init()
{
	display_clear();
    display_update_temperature();
   }

void main_logic_step()
{
    display_update_temperature();
    display_partial_redraw();
}
