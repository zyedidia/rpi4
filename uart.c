#include <stdbool.h>
#include <stdint.h>

#include "bits.h"
#include "gpio.h"
#include "uart.h"
#include "mmio.h"
#include "sys.h"

typedef struct {
    uint32_t io;
    uint32_t ier;
    uint32_t iir;
    uint32_t lcr;
    uint32_t mcr;
    uint32_t lsr;
    uint32_t msr;
    uint32_t scratch;
    uint32_t cntl;
    uint32_t stat;
    uint32_t baud;
} aux_periphs_t;

#define ENABLE_UART   1
#define RX_ENABLE     (1 << 0)
#define TX_ENABLE     (1 << 1)
#define CLEAR_TX_FIFO (1 << 1)
#define CLEAR_RX_FIFO (1 << 2)
#define CLEAR_FIFOS   (CLEAR_TX_FIFO | CLEAR_RX_FIFO)
#define IIR_RESET     ((0b11 << 6) | 1)

static volatile uint32_t* const aux_enables = (uint32_t*) (MMIO_BASE + 0x215004);
static aux_periphs_t* const uart = (aux_periphs_t*) (MMIO_BASE + 0x215040);

void uart_init(unsigned baud) {
    gpio_set_func(GPIO_TX, GPIO_FUNC_ALT5);
    gpio_set_func(GPIO_RX, GPIO_FUNC_ALT5);

    dsb();

    mmio_st(aux_enables, mmio_ld(aux_enables) | ENABLE_UART);

    dsb();

    mmio_st(&uart->cntl, 0);
    mmio_st(&uart->ier, 0);
    mmio_st(&uart->lcr, 0b11);
    mmio_st(&uart->mcr, 0);
    mmio_st(&uart->iir, IIR_RESET | CLEAR_FIFOS);
    mmio_st(&uart->baud, (CORE_FREQ) / (baud * 8) - 1);
    mmio_st(&uart->cntl, RX_ENABLE | TX_ENABLE);

    dsb();
}

bool uart_rx_empty() {
    return bit_get(mmio_ld(&uart->stat), 0) == 0;
}

unsigned uart_rx_sz() {
    return bits_get(mmio_ld(&uart->stat), 16, 19);
}

bool uart_can_tx() {
    return bit_get(mmio_ld(&uart->stat), 1) != 0;
}

uint8_t uart_rx() {
    dsb();
    while (uart_rx_empty())
        ;
    uint8_t c = mmio_ld(&uart->io) & 0xff;
    dsb();
    return c;
}

void uart_tx(uint8_t c) {
    dsb();
    while (!uart_can_tx())
        ;
    mmio_st(&uart->io, c & 0xff);
    dsb();
}

void uart_putc(void* p, char c) {
    (void) p;
    uart_tx(c);
}

bool uart_tx_empty() {
    dsb();

    return bit_get(mmio_ld(&uart->stat), 9) == 1;
}

void uart_tx_flush() {
    while (!uart_tx_empty())
        ;
}
