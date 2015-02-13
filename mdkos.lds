ENTRY(start_os)

SEARCH_DIR(.)

MEMORY
{
	sram : org = 0x00000000 , len = 0x1000
	sdram : org = 0x30000000 , len = 0x4000000
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

	.bss  :
	{
		__bss_start__ = .;
		*(.bss); *(COMMON)
		__bss_end__ = .;

		__stack_bottom__ = .;
		. += 0x1000;
		__stack_top__ = .;

	} > sdram

	.vector_reloc :
	{
		__exception_vector_reloc_start__ = .;
		*(.vector_reloc);
		. = ALIGN(4);
		__exception_vector_reloc_end__ = .;
	} > sdram

	.handler :
	{
		__exception_handler_start__ = .;
		*(.handler);
		. = ALIGN(4);
		__exception_handler_end__ = .;
	} > sdram

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
