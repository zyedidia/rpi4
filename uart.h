#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "libc/tinyprintf.h"

void uart_init(unsigned baud);
bool uart_rx_empty();
bool uart_can_tx();
unsigned uart_rx_sz();
uint8_t uart_rx();
void uart_tx(uint8_t c);
bool uart_tx_empty();
void uart_tx_flush();

// for tinyprintf
void uart_putc(void* p, char c);
