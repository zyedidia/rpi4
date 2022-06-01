#include <stdint.h>

void kernel_start();

void cstart() {
    extern int __bss_start__, __bss_end__;

    int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    kernel_start();
}
