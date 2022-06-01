DEP = $(OBJ:.o=.d)
CFLAGS += -MMD

-include $(DEP)

format:
	clang-format -i $(CSRC) $(HSRC)

clean:
	rm -f *.d *.list *.o *.elf *.bin
