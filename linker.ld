ENTRY(_start)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
  RAM (rwx)  : ORIGIN = 0x10000000, LENGTH = 64K
}

SECTIONS
{
  .text : 
  {
    *(.text*)
    *(.rodata*)
    *(.eh_frame*)
  } > FLASH

  .data : 
  {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
  } > RAM AT > FLASH

  .bss (NOLOAD) : 
  {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(COMMON)
    _bss_end = .;
  } > RAM

  PROVIDE(__global_pointer$ = _data_start + 0x800);  /* GP is near .sdata */

  /* Define memory region symbols */
  PROVIDE(__bss_start = _bss_start);
  PROVIDE(_end = .);
}
_stack_top = ORIGIN(RAM) + LENGTH(RAM);

  PROVIDE(_data_start = .);
  PROVIDE(_data_end = .);
  PROVIDE(_data_load = LOADADDR(.data));
  PROVIDE(_bss_start = .);
  PROVIDE(_bss_end = .);
