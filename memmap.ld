SECTIONS
{
    .text 0x80000 :  { 
        __code_start__ = .;
        KEEP(*(.text.boot))  
        *(.text*) 
        __code_end__ = .;
        . = ALIGN(8);
    }
    .rodata : {
        __rodata_start__ = .;
        *(.rodata*)
        __rodata_end__ = .;
    }
    .data : { 
        __data_start__ = .;
        *(.data*) 
        . = ALIGN(4);
        __data_end__ = .;
    } 
    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end__ = .;
        . = ALIGN(8);
        __prog_end__ = .;
        __heap_start__ = .;
    }
}
