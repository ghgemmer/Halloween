#include <arduino.h>
#include "NormalArray_values_reader.h"

NormalArray_values_reader::NormalArray_values_reader() : 
	indexed_values_reader(),
	valuesArray(0), 
	maxEntries(0)   	
	{
	}
NormalArray_values_reader::NormalArray_values_reader(const uint16_t * values_array, unsigned long max_entries) : 
	indexed_values_reader(),
	valuesArray(values_array), 
	maxEntries(max_entries)   	
	{
	}
	
void NormalArray_values_reader::Modify(const uint16_t * values_array, unsigned long max_entries)
	{
		valuesArray = values_array;
		maxEntries = max_entries;
	}

// read the array value at the indicated index
uint16_t NormalArray_values_reader::read(unsigned long index)
{
	uint16_t value = 0;
	if (index < maxEntries)
  {
  	value = valuesArray[index];
  }
  return value;   
}
