#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t sem1 = NULL;
SemaphoreHandle_t sem2 = NULL;
SemaphoreHandle_t sem3 = NULL;

void Task1(void *pvParameters)
{
    printf("Task1 iniciada\n"); // Adicione este print
    while (1)
    {
        if (xSemaphoreTake(sem1, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 1] Executou - Nome:Mike\n");
            vTaskDelay(pdMS_TO_TICKS(3000));
            xSemaphoreGive(sem2); // Libera a próxima tarefa
        }
    }
}

void Task2(void *pvParameters)
{
    printf("Task2 iniciada\n");
    while (1)
    {
        if (xSemaphoreTake(sem2, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 2] Executou - Nome:Mike\n");
            vTaskDelay(pdMS_TO_TICKS(3000));
            xSemaphoreGive(sem3); // Libera a próxima tarefa
        }
    }
}

void Task3(void *pvParameters)
{
    printf("Task3 iniciada\n"); 
    while (1)
    {
        if (xSemaphoreTake(sem3, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 3] Executou - Nome:Mike\n");
            vTaskDelay(pdMS_TO_TICKS(3000));
            xSemaphoreGive(sem1); // Libera a próxima tarefa
        }
    }
}

void app_main(void)
{
    sem1 = xSemaphoreCreateBinary();
    sem2 = xSemaphoreCreateBinary();
    sem3 = xSemaphoreCreateBinary();

    if (sem1 == NULL || sem2 == NULL || sem3 == NULL)
    {
        printf("Falha ao criar semáforos\n");
        return;
    }

    xTaskCreate(Task1, "Task1", 2048, NULL, 5, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 5, NULL);
    xTaskCreate(Task3, "Task3", 2048, NULL, 5, NULL);

    xSemaphoreGive(sem1); // Inicia a primeira tarefa
}

