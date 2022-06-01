#pragma once

#include <stdint.h>

// rpi3
#define MMIO_BASE 0x3f000000
// rpi1ap
// #define MMIO_BASE 0x20000000
// rpi4b
// #define MMIO_BASE 0xfe000000

static inline void mmio_st(volatile uint32_t* addr, uint32_t val) {
    *addr = val;
}

static inline uint32_t mmio_ld(volatile uint32_t* addr) {
    return *addr;
}
