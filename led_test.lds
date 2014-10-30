ENTRY(vectors)

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
		. += 0x800;
		__stack_top__ = .;

	} > sdram


/*
	.rel.plt :
	{
		*(.rel.plt)
	} > sdram

	.gnu.version :
	{
		*(.gnu.version)
	} > sdram

	.gnu.version_r :
	{
		*(.gnu.version_r)
	} > sdram

	.gnu.hash :
	{
		*(.gnu.hash)
	} > sdram

	.dynsym :
	{
		*(.dynsym)
	} > sdram 

	.dynstr :
	{
		*(.dynstr)
	} > sdram

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
