ENTRY(os_vector_jmp)

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
		*(.data)
		. = ALIGN(4);
		__data_end__ = .;
	} > sdram

	.bss  :
	{
		__bss_start__ = .;
		*(.bss); *(COMMON)
		__bss_end__ = .;

		__stack_bottom__ = .;
		. += 0x300;
		__stack_top__ = .;

	} > sdram

	/*.exception_vectors_reloc :
	{
		__exception_vector_reloc_start = .;
		*(.exception_vectors_reloc)
		.=ALIGN(4);
		__exception_vector_reloc_end = .;
	} > sdram*/
	
	.stab 0 (NOLOAD) : 
	{
		[ .stab ]
	}

	.stabstr 0 (NOLOAD) :
	{
		[ .stabstr ]
	}
}
