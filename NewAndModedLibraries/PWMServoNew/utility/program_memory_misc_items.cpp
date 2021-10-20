#include <avr/io.h>
#include <avr/pgmspace.h>
#include "program_memory_misc_items.h"


void program_memory_misc_items::getPrgmMemory (uint16_t sizeBytes, uint_farptr_t src, uint8_t * dst)
{
	for (unsigned int i = 0; i < sizeBytes ; i++)
	{
		dst[i] = pgm_read_byte_far(src + i);
	}
}
