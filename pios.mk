MEMMAP = $(PIOS)/memmap.ld

PIOS_CSRC = $(wildcard $(PIOS)/*.c) $(wildcard $(PIOS)/libc/*.c)
PIOS_HSRC = $(wildcard $(PIOS)/*.h) $(wildcard $(PIOS)/libc/*.h)
PIOS_SSRC = $(wildcard $(PIOS)/*.s)

PIOS_OBJ_NOSAN = $(PIOS)/uart.o $(PIOS)/ksan.o $(PIOS)/cstart.o $(PIOS)/start.o $(PIOS)/gpio.o $(PIOS)/kmalloc.o $(PIOS)/libc/tinyprintf.o
PIOS_OBJ = $(PIOS_CSRC:.c=.o) $(PIOS_SSRC:.s=.o)
