include pios.mk
include defs.mk

O ?= s

CFLAGS += -MMD
DEP = $(PIOS_OBJ:.o=.d)

all: $(PIOS_OBJ)

clean:
	rm -f *.d *.list *.o *.elf *.bin

-include $(DEP)

format:
	clang-format -i $(PIOS_CSRC) $(PIOS_HSRC)

.PHONY: format all install
