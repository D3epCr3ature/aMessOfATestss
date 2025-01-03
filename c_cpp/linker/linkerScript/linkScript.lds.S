SECTIONS
{
	. = 0x100;

	.text :
	{
		*(.text*)
	}

	. = 0x500;

	.data_section :
	{
		*(.data_section)
	}

	. = ALIGN(4096);

	.code_section :
	{
                *(.code_section)
	}
}
