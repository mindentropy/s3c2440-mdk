ENTRY(start_os)

SEARCH_DIR(.)

MEMORY
{
	sram : org = 0x00000000 , len = 0x1000
	/*sdram : org = 0x30000000 , len = 0x4000000*/
	sdram : org = 0x30000000 , len = 0x3F00000 /* 63MB RAM */
	vectors : org = 0x33F00000 , len = 0x100000 /* Last 1MB for the isr handlers */
}

SECTIONS
{

	.text :
	{
		*(.text);
		. = ALIGN(4);
	} > sdram


	.data :
	{
		__data_start__ = .;
		*(.data);
		. = ALIGN(4);
		__data_end__ = .;
	} > sdram

/*
 * Note on constant string bug (related to .rodata): 
 * There was a bug initially when printing a string constant would make the 
 * device go into a loop printing nonsense. This was due the fact that .rodata section
 * was left out. Due to this the addresses of the constant was emitted after the interrupt
 * vectors but the actual address of the constant was somewhere in between the file. (it
 * was after the stack setup. All the functions which referred to the string would use
 * the address which was emitted at the end of the isr handlers but the string was sitting
 * way before. It would have worked if after startup the string was moved to the address
 * at the end of the isr handler. Instead of doing this we can create a .rodata section and
 * put in the RAM. Also make sure we don't overwrite the read only section with some 
 * method. We can later write the .rodata to say flash and lock the write and do only a
 * read.
 */
	.rodata :
	{
		__rodata_start__ = .;
		*(.rodata);
		. = ALIGN(4);
		__rodata_end__ = .;
	} > sdram

	.bss  :
	{
		__bss_start__ = .;
		*(.bss); *(COMMON)
		__bss_end__ = .;

		__usr_sys_stack_bottom__ = .;
		. += 0x1000;
		__usr_sys_stack_top__ = .;

		__irq_stack_bottom__ = .;
		. += 0x1000;
		__irq_stack_top__ = .;

		__fiq_stack_bottom__ = .;
		. += 0x1000;
		__fiq_stack_top__ = .;

		__svc_stack_bottom__ = .;
		. += 0x1000;
		__svc_stack_top__ = .;
	} > sdram

	.vector_reloc :
	{
		__exception_vector_reloc_start__ = .;
		*(.vector_reloc);
	/*	. = ALIGN(4);*/
		__exception_vector_reloc_end__ = .;
	} >vectors AT>sdram /* SDRAM is where it will be stored in the file but address
	                     * references will be in the addresses of the isr handler section */

	.isrhandler :
	{
		__exception_handler_start__ = .;
		*(.isrhandler);
	/*	. = ALIGN(4);*/
		__exception_handler_end__ = .;
	} >vectors AT>sdram

	/* 
	 * >vma region AT > lma region 
	 */

	/* 
	 * eg: .data section is linked with LMA in ROM and
	 * the VMA pointing to the real RAM versions
	 */

	.stab 0 (NOLOAD) : 
	{
		[ .stab ]
	}

	.stabstr 0 (NOLOAD) :
	{
		[ .stabstr ]
	}
}
