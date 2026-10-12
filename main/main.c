#include <stdbool.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"
#include <stdio.h>

#define RED_LED GPIO_NUM_15
#define BLUE_LED GPIO_NUM_16
#define LED_OFF 0
#define LED_ON 1
#define FAST_MODE 300
#define SLOW_MODE 1000

void separeteMode(int blinkDelayMs);
void combineMode(int blinkDelayMs);

void app_main(void) {

    gpio_reset_pin(RED_LED);
    gpio_reset_pin(BLUE_LED);
    gpio_set_direction(RED_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLUE_LED, GPIO_MODE_OUTPUT);
    gpio_set_level(BLUE_LED, LED_OFF);
    gpio_set_level(RED_LED, LED_OFF);
    unsigned int blinkDelayMs;
    unsigned int counter = 0;
    bool blinkMode = false;


    while (1) {
        if(counter % 4 == 0) blinkMode = esp_random() % 2;
        if(counter % 8 > 3) {
             blinkDelayMs = SLOW_MODE;
        } else {
             blinkDelayMs = FAST_MODE;
        }
        if (blinkMode) {
            separeteMode(blinkDelayMs);
        }else {
            combineMode(blinkDelayMs);
        }
        counter++;
    }

}

void combineMode(int blinkDelayMs){
    gpio_set_level(BLUE_LED, LED_ON);
    gpio_set_level(RED_LED, LED_ON);
    vTaskDelay(pdMS_TO_TICKS(blinkDelayMs));
    gpio_set_level(BLUE_LED, LED_OFF);
    gpio_set_level(RED_LED, LED_OFF);
    vTaskDelay(pdMS_TO_TICKS(blinkDelayMs));
}

void separeteMode(int blinkDelayMs){
    gpio_set_level(BLUE_LED, LED_ON);
    gpio_set_level(RED_LED, LED_OFF);
    vTaskDelay(pdMS_TO_TICKS(blinkDelayMs));
    gpio_set_level(BLUE_LED, LED_OFF);
    gpio_set_level(RED_LED, LED_ON);
    vTaskDelay(pdMS_TO_TICKS(blinkDelayMs));
}


