#pragma once

#define MMIO_BASE 0xfe000000
#define CORE_FREQ (250 * 1000 * 1000)

enum {
    GPIO_TX = 14,
    GPIO_RX = 15,
    GPIO_SDA = 2,
    GPIO_SCL = 3,
};

typedef enum {
    GPIO_FUNC_INPUT = 0,
    GPIO_FUNC_OUTPUT = 1,
    GPIO_FUNC_ALT0 = 4,
    GPIO_FUNC_ALT1 = 5,
    GPIO_FUNC_ALT2 = 6,
    GPIO_FUNC_ALT3 = 7,
    GPIO_FUNC_ALT4 = 3,
    GPIO_FUNC_ALT5 = 2,
} gpio_func_t;

void gpio_set_func(unsigned pin, unsigned fn);

static inline void dsb() {
    asm volatile ("dsb sy");
}
