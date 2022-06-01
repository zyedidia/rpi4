include ../defs.mk

MEMMAP = memmap.ld

O ?= s

KERN = boot

CSRC = $(wildcard *.c)
HSRC = $(wildcard *.h)

LIBOBJ = start.o uart.o gpio.o
OBJ = $(CSRC:.c=.o) $(addprefix $(PIOS)/,$(LIBOBJ))

CFLAGS += -I$(PIOS)

all: $(KERN).bin

$(KERN).elf: $(OBJ)
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f *.list *.o $(KERN).elf $(KERN).bin

format:
	clang-format -i $(CSRC) $(HSRC)

qemu-gdb: $(KERN).elf
	$(QEMU) -s -S -M $(BOARD) -nographic -kernel $< -serial null -serial mon:stdio -no-reboot &
	$(GDB) -ex "file $(KERN).elf" -ex "target remote localhost:1234"

.PHONY: format all install
