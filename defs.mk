ARCHID = aarch64
PREFIX = $(ARCHID)-none-elf

CC = $(PREFIX)-gcc
AS = $(PREFIX)-as
LD = $(PREFIX)-ld
CPP = $(PREFIX)-cpp
OBJCOPY = $(PREFIX)-objcopy
OBJDUMP = $(PREFIX)-objdump

QEMU = qemu-system-$(ARCHID)
BOARD = raspi3b
GDB = gdb-multiarch
PIPROG = piprog

LIBGCC = $(shell $(CC) --print-file-name=libgcc.a)

CPU = cortex-a72
ARCH = armv8-a+crc

PIOS ?= $(shell git rev-parse --show-toplevel)

CFLAGS = -O$(O) -g -Werror -Wall -nostdlib -nostartfiles -ffreestanding -Wa,-mcpu=$(CPU) -Wa,-march=$(ARCH)
ASFLAGS = -mcpu=$(CPU) -march=$(ARCH)
LDFLAGS = -T $(MEMMAP)
LDLIBS = $(LIBGCC)
SANITIZE ?= 0
ifeq ($(SANITIZE),1)
	ASAN_FLAGS = -fsanitize=kernel-address,undefined -DSANITIZE=1
else
	ASAN_FLAGS = -DSANITIZE=0
endif

$(PIOS_OBJ_NOSAN): ASAN_FLAGS := -DSANITIZE=$(SANITIZE)

%.o: %.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $< -c -o $@

%.o: %.s
	$(CPP) $< | $(AS) $(ASFLAGS) -c -o $@

%.bin: %.elf
	$(OBJCOPY) $< -O binary $@

%.list: %.elf
	$(OBJDUMP) -D $< > $@
