#pragma once

#include <stdint.h>

static inline void mmio_st(volatile uint32_t* addr, uint32_t val) {
    *addr = val;
}

static inline uint32_t mmio_ld(volatile uint32_t* addr) {
    return *addr;
}
