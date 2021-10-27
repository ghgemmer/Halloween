/*
 Author: Greg Gemmer, ghgemmer@gmail.com
 Copyright (c) 2021 Greg Gemmer.
 MIT license
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
