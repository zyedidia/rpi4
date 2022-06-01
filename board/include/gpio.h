#pragma once

#include <stdbool.h>

void gpio_set_output(unsigned pin);
void gpio_set_on(unsigned pin);
void gpio_set_off(unsigned pin);
void gpio_set_input(unsigned pin);
void gpio_write(unsigned pin, bool v);
bool gpio_read(unsigned pin);
void gpio_pullup(unsigned pin);
void gpio_pulldown(unsigned pin);
void gpio_pud_off(unsigned pin);
