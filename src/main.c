#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

void PrintTime();

/* The main function sets up the board to communicate over the serial
 * connection, creates a task using the PrintTime() function, and then
 * begins to run that task.
 */
int main()
{
    stdio_init_all();

    xTaskCreate(PrintTime, "PrintTime", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1);
}

/* The PrintTime() function prints the amount of time (in seconds) since
 * initial boot to stdout (the serial console). It prints its message once per
 * second using the vTaskDelay() function. That function takes in a TickType_t
 * argument, so to get the clock accurate, I used the pdMS_TO_TICKS macro which
 * converts a number in milliseconds to the number of ticks using the
 * configTICK_RATE_HZ macro in the FreeRTOSConfig.h file as a conversion factor.
 * I get the time since boot by calling the get_absolute_time() function and
 * storing it in current_time. To convert the microseconds that are returned
 * from get_absolute_time() into seconds, I divide the result by 1 million.
 */
void PrintTime()
{
    uint64_t current_time = 0;
    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

    while (true) {
        current_time = get_absolute_time() / 1000000;
        printf("seconds since boot: %lld \n", current_time);
        vTaskDelay(xDelay1000ms);
    }
}
