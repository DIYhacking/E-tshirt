/* Task for receiving readings from the wireless or NTC sensor. */

#include <stdbool.h>

bool sensor_get_temperature(int *temperature, int *timestamp, bool *wireless);
void sensor_reset_timestamp();
bool pass_heart_temp(int *heart, int *temper, float *gsr1);

void sensor_start();
void sensor_stop();
