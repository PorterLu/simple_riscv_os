/* 
 * rvos.ld
 * Linker script for outputting ro RVOS
 */


/*
 * OUTPUT_ARCH command specifies a particular output machine architecture.
 * "riscv" is the name of the architecture for both 64-bit and 32-bit
 *	we will further refine this by using -march=rv64im and -mabi=lp64 
 *	when calling gcc	
 */

OUTPUT_ARCH( "riscv" )

/*
 *ENTRY command is used to set the "entry point", which is the first instruction
 to execute in a program.
 */

ENTRY( _start )

/*
 *The MEMORY command describes the location and size of blocks of memory in the target.
 * MEMORY
 * {
 *		name [(attr)]: ORIGIN = origin, LENGTH = len
 *		......
 * }
 */

MEMORY
{
		ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{

		.text : {
				PROVIDE(_text_start = .);
				*(.text .text.*)
				PROVIDE(_text_end = .);
		} >ram

		.rodata : {
				PROVIDE(_rodata_start = .);
				*(.rodata .rodata.*)
				PROVIDE(_rodata_end = .);
		} >ram

		.data : {
			
				. = ALIGN(4096);
				PROVIDE(_data_start = .);
				*(.sdata .sdata.*)
				*(.data .data.*)
				PROVIDE(_data_end = .);
		} >ram

		.bss : {
			PROVIDE(_bss_start = .);
			*(.sbss .sbss.*)
			*(.bss .bss.*)
			*(COMMON)
			PROVIDE(_bss_end = .);
		} >ram

		PROVIDE(_memory_start = ORIGIN(ram));
		PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));

		PROVIDE(_heap_start = _bss_end);
		PROVIDE(_heap_size = _memory_end - _heap_start);
}
