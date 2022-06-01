#include <stdint.h>

void kernel_start();

void cstart() {
    extern int _kbss_start, _kbss_end;

    int* bss = &_kbss_start;
    int* bss_end = &_kbss_end;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    kernel_start();
}
