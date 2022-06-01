#include "uart.h"
#include "sys.h"
#include "mmio.h"
#include "libc/tinyprintf.h"

extern int main();

void reboot() {
    printf("Rebooting...\n");
    uart_tx_flush();

    dsb();

    volatile uint32_t* PM_RSTC = (uint32_t*) (MMIO_BASE + 0x10001c);
    volatile uint32_t* PM_WDOG = (uint32_t*) (MMIO_BASE + 0x100024);

    const int PM_PASSWORD = 0x5a000000;
    const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;

    mmio_st(PM_WDOG, PM_PASSWORD | 1);
    mmio_st(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
    while (1)
        ;
}

void kernel_start() {
    uart_init(115200);
    init_printf(NULL, uart_putc);

    main();
    reboot();
}
