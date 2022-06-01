#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "sys.h"

static inline void delay_ncycles(unsigned n) {
    while (n--) {
        asm volatile ("nop");
    }
}

static inline void delay_us(unsigned us) {
    unsigned long f, t, r;
    // get the current counter frequency
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    // read the current counter
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    // calculate expire value for counter
    t += ((f / 1000) * us) / 1000;
    do {
        asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    } while (r < t);
}

static inline void delay_ms(unsigned ms) {
    delay_us(ms * 1000);
}
