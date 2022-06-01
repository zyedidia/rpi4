#include <stdint.h>
#include <stdlib.h>

void boot_start();

void __attribute__((section(".text.cstart"))) cstart() {
    extern char _boot_start;
    extern char _boot_size;

    char* dst = (char*) 0x0;
    char* src = &_boot_start;
    while (dst < &_boot_size) {
        *dst++ = *src++;
    }

    extern int _bss_start, _bss_end;
    int* bss = &_bss_start;
    int* bss_end = &_bss_end;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    boot_start();
}
