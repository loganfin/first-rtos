#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

void task_1();
void task_2();

int main()
{
    stdio_init_all();

    xTaskCreate(task_1, "Task_1", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}

void task_1()
{
    uint64_t current_time = 0;

    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
    while (true) {
        current_time = get_absolute_time() / 1000000;
        printf("seconds since boot: %lld \n", current_time);
        vTaskDelay(xDelay1000ms);
    }
}
