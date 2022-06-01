#pragma once

void timer_init();
void timer_wait_us(unsigned us);

static inline void timer_wait_ms(unsigned ms) {
    timer_wait_us(ms * 1000);
}
