void timer_init() {}

void timer_wait_us(unsigned us) {
    unsigned long f, t, r;
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    t += ((f / 1000) * us) / 1000;
    do {
        asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    } while (r < t);
}
