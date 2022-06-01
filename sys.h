#pragma once

#define ARM_FREQ (700 * 1000 * 1000)
#define CORE_FREQ (250 * 1000 * 1000)

static inline void dsb() {
    asm volatile ("dsb sy");
}
