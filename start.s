.section ".text.boot"

.globl _start
_start:
    // Check processor ID is zero (executing on main core), else hang
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 1f
    // We're not on the main core, so hang in an infinite wait loop
_hlt:
    wfe
    b       _hlt
1:  // We're on the main core!

    // Set stack to start below our code
    ldr     x1, =_start
    mov     sp, x1

	// TODO: force system or super mode

	bl cstart
	b _hlt
