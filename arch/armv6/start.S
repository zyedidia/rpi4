.section ".text.boot"

.globl _start
_start:
	// Set stack below our code
	ldr sp, =_start
	# clear frame pointer
	mov fp, #0
	// TODO: for mode to be system
	bl cstart
_hlt:
	b _hlt

