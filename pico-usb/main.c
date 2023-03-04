#include "pico/stdlib.h"
#include <stdio.h>

int main()
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        gpio_put(LED_PIN, 1);
        printf("hello world1\n");
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        printf("hello world2\n");
        sleep_ms(500);
    }
}