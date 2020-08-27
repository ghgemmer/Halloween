#include <arduino.h>
#include "ProgMemArray_values_reader.h"

ProgMemArray_values_reader::ProgMemArray_values_reader() : 
	indexed_values_reader(),
	pfarArray(0), 
	maxEntries(0)   	
	{
	}
ProgMemArray_values_reader::ProgMemArray_values_reader(const uint_farptr_t pfar_Array, unsigned long max_entries) : 
	indexed_values_reader(),
	pfarArray(pfar_Array), 
	maxEntries(max_entries)   	
	{
	}
	
void ProgMemArray_values_reader::Modify(const uint_farptr_t pfar_Array, unsigned long max_entries)
	{
		pfarArray = pfar_Array; 
		maxEntries = max_entries;   	
	}

// read the array value at the indicated index
uint16_t ProgMemArray_values_reader::read(unsigned long index)
{
	uint16_t value = 0;
	if (index < maxEntries)
  {
  	// read from program memory
  	value = pgm_read_word_far(pfarArray + ((sizeof(uint16_t))*(index)));  // *sizeof(uint16_t) to get the far address of the uint16_t word .  i.e (sizeof(uint16_t) address units per word. TODO: Probably would be better to have a macro for this to remove any cpu architecture dependency
  }
  return value;   
}
