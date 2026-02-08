#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "ringbuf.h"

ringbuf_t rb;

SemaphoreHandle_t rb_mutex;
SemaphoreHandle_t sem_empty;
SemaphoreHandle_t sem_full;

void producer_task(void *param)
{
    int id = (int)param;
    static uint8_t value = 1;

    while (1) {
        xSemaphoreTake(sem_empty, portMAX_DELAY);
        xSemaphoreTake(rb_mutex, portMAX_DELAY);

        ringbuf_push(&rb, value);
        printf("Producer %d: pushed %d\n", id, value);
        value++;

        xSemaphoreGive(rb_mutex);
        xSemaphoreGive(sem_full);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void consumer_task(void *param)
{
    int id = (int)param;
    uint8_t value;

    while (1) {
        xSemaphoreTake(sem_full, portMAX_DELAY);
        xSemaphoreTake(rb_mutex, portMAX_DELAY);

        ringbuf_pop(&rb, &value);
        printf("Consumer %d: got %d\n", id, value);

        xSemaphoreGive(rb_mutex);
        xSemaphoreGive(sem_empty);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    ringbuf_init(&rb);

    rb_mutex = xSemaphoreCreateMutex();
    sem_empty = xSemaphoreCreateCounting(RINGBUF_SIZE, RINGBUF_SIZE);
    sem_full  = xSemaphoreCreateCounting(RINGBUF_SIZE, 0);

    xTaskCreate(producer_task, "Producer1", 2048, (void *)1, 1, NULL);
    xTaskCreate(producer_task, "Producer2", 2048, (void *)2, 1, NULL);

    xTaskCreate(consumer_task, "Consumer1", 2048, (void *)1, 1, NULL);
    xTaskCreate(consumer_task, "Consumer2", 2048, (void *)2, 1, NULL);
}