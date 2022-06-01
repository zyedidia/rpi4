#include "gpio.h"
#include "timer.h"

int main() {
    gpio_set_output(21);
    int v = 1;

    while (1) {
        gpio_write(21, v);
        v = !v;
        delay_ms(500);
    }

    return 0;
}
