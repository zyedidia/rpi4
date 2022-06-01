#include "sys.h"

void timer_init() {
    asm volatile("mcr p15, 0, %0, c15, c12, 0" ::"r"(1));
}

static inline unsigned timer_cycles() {
    unsigned cyc;
    asm volatile("mrc p15, 0, %0, c15, c12, 1" : "=r"(cyc));
    return cyc;
}

void timer_wait_us(unsigned us) {
    unsigned rb = timer_cycles();
    while (1) {
        unsigned ra = timer_cycles();
        if ((ra - rb) >= us * CPU_FREQ_MHZ) {
            break;
        }
    }
}
