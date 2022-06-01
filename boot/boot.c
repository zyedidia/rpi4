#include "timer.h"
#include "uart.h"
#include "crc32.h"

enum {
    BOOT_START      = 0xFFFF0000,

    GET_PROG_INFO   = 0x11112222,
    PUT_PROG_INFO   = 0x33334444,

    GET_CODE        = 0x55556666,
    PUT_CODE        = 0x77778888,

    BOOT_SUCCESS    = 0x9999AAAA,
    BOOT_ERROR      = 0xBBBBCCCC,

    BAD_CODE_ADDR   = 0xdeadbeef,
    BAD_CODE_CKSUM  = 0xfeedface,
};

static uint32_t get_uint() {
    union {
        char b[4];
        uint32_t i;
    } x;

    x.b[0] = uart_rx();
    x.b[1] = uart_rx();
    x.b[2] = uart_rx();
    x.b[3] = uart_rx();
    return x.i;
}

static void put_uint(uint32_t u) {
    uart_tx((u >> 0) & 0xff);
    uart_tx((u >> 8) & 0xff);
    uart_tx((u >> 16) & 0xff);
    uart_tx((u >> 24) & 0xff);
}

static void* boot() {
    while (1) {
        put_uint(GET_PROG_INFO);
        delay_ms(200);

        if (!uart_rx_empty() && get_uint() == PUT_PROG_INFO) {
            break;
        }
    }

    char* base = (char*) (uint64_t) get_uint();
    uint32_t nbytes = get_uint();
    uint32_t crc_recv = get_uint();

    put_uint(GET_CODE);
    put_uint(crc_recv);

    if (get_uint() != PUT_CODE) {
        return NULL;
    }

    for (uint32_t i = 0; i < nbytes; i++) {
        base[i] = uart_rx();
    }
    uint32_t crc_calc = crc32(base, nbytes);
    if (crc_calc != crc_recv) {
        put_uint(BAD_CODE_CKSUM);
        return NULL;
    }
    put_uint(BOOT_SUCCESS);

    uart_tx_flush();
    return (void*) base;
}

void boot_start() {
    uart_init(115200);

    void* code = boot();
    uart_tx_flush();
    if (code) {
        void (*main)() = (typeof(main)) code;
        main();
    }
}
