#include <stdbool.h>
#include <stdint.h>

#include "bits.h"
#include "gpio.h"
#include "timer.h"

static volatile uint32_t* gpio_fsel = (uint32_t*) (MMIO_BASE + GPIO_BASE);
static volatile uint32_t* gpio_pud_ctrl = (uint32_t*) (MMIO_BASE + GPIO_BASE + 0xe4);

void gpio_set_func(unsigned pin, gpio_func_t fn) {
    if (pin >= 32)
        return;
    unsigned off = (pin % 10) * 3;
    unsigned idx = pin / 10;

    uint32_t v = mmio_ld(&gpio_fsel[idx]);
    v &= ~(0b111 << off);
    v |= fn << off;
    mmio_st(&gpio_fsel[idx], v);
}

void gpio_set_output(unsigned pin) {
    gpio_set_func(pin, GPIO_FUNC_OUTPUT);
}

void gpio_set_input(unsigned pin) {
    gpio_set_func(pin, GPIO_FUNC_INPUT);
}

void gpio_set_on(unsigned pin) {
    if (pin >= 32)
        return;
    mmio_st(gpio_set, 1 << pin);
}

void gpio_set_off(unsigned pin) {
    if (pin >= 32)
        return;
    mmio_st(gpio_clr, 1 << pin);
}

void gpio_write(unsigned pin, bool v) {
    if (v) {
        gpio_set_on(pin);
    } else {
        gpio_set_off(pin);
    }
}

bool gpio_read(unsigned pin) {
    if (pin >= 32)
        return false;
    return (mmio_ld(gpio_lev) >> pin) & 1;
}

enum {
    PUD_OFF = 0b00,
    PUD_PULLDOWN = 0b01,
    PUD_PULLUP = 0b10,
};

static void gpio_set_pud(unsigned pin, unsigned pud) {
    if (pin >= 32)
        return;
    unsigned off = (pin % 16) * 2;
    unsigned idx = (pin / 16);
    uint32_t v = mmio_ld(&gpio_pud_ctrl[idx]);
    v &= ~(0b11 << off);
    v |= pud << off;
    mmio_st(&gpio_pud_ctrl[idx], v);
}

void gpio_set_pullup(unsigned pin) {
    if (pin >= 32)
        return;
    gpio_set_pud(pin, PUD_PULLUP);
}

void gpio_set_pulldown(unsigned pin) {
    if (pin >= 32)
        return;
    gpio_set_pud(pin, PUD_PULLDOWN);
}

void gpio_pud_off(unsigned pin) {
    if (pin >= 32)
        return;
    gpio_set_pud(pin, PUD_OFF);
}
