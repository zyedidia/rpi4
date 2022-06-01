#include <stdbool.h>
#include <stdint.h>

#include "sys.h"
#include "bits.h"
#include "gpio.h"

#define GPIO_BASE 0x200000

static volatile uint32_t* gpio_fsel = (uint32_t*) (MMIO_BASE + GPIO_BASE);
static volatile uint32_t* gpio_set = (uint32_t*) (MMIO_BASE + GPIO_BASE + 0x1C);
static volatile uint32_t* gpio_clr = (uint32_t*) (MMIO_BASE + GPIO_BASE + 0x28);
static volatile uint32_t* gpio_lev = (uint32_t*) (MMIO_BASE + GPIO_BASE + 0x34);
static volatile uint32_t* gpio_pud_ctrl = (uint32_t*) (MMIO_BASE + GPIO_BASE + 0xe4);

void gpio_set_func(unsigned pin, unsigned fn) {
    if (pin >= 32)
        return;
    unsigned off = (pin % 10) * 3;
    unsigned idx = pin / 10;

    uint32_t v = mmio_ld(&gpio_fsel[idx]);
    v &= ~(0b111 << off);
    v |= funcs[fn] << off;
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

static inline void wait_cyc(unsigned n) {
    while (n--) {
        asm volatile ("nop");
    }
}

static void gpio_apply_pud(unsigned pin) {
    wait_cyc(200);
    mmio_st(gpio_pudclk, 1 << pin);
    wait_cyc(200);
    mmio_st(gpio_pud, 0);
    mmio_st(gpio_pudclk, 0);
}

void gpio_set_pullup(unsigned pin) {
    if (pin >= 32)
        return;
    mmio_st(gpio_pud, PUD_PULLUP);
    gpio_apply_pud(pin);
}

void gpio_set_pulldown(unsigned pin) {
    if (pin >= 32)
        return;
    mmio_st(gpio_pud, PUD_PULLDOWN);
    gpio_apply_pud(pin);
}

void gpio_pud_off(unsigned pin) {
    if (pin >= 32)
        return;
    mmio_st(gpio_pud, PUD_OFF);
    gpio_apply_pud(pin);
}
