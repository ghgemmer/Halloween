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

/*
This derived class allows values stored in a unit16_t array in PROGMEM (program memory) to be read based on the index
the certain functionalities.
*/
#ifndef ProgMemArray_values_reader_h
#define ProgMemArray_values_reader_h

#include <inttypes.h>
#include "indexed_values_reader.h"
#include <avr/pgmspace.h>

class ProgMemArray_values_reader : public indexed_values_reader 
{  
  public:
  	ProgMemArray_values_reader();
    ProgMemArray_values_reader(const uint_farptr_t pfar_Array, unsigned long max_entries);
    void Modify(const uint_farptr_t pfar_Array, unsigned long max_entries);
 
    // read the value associated with index   
    virtual uint16_t read(unsigned long index);
        
    protected:
    uint_farptr_t pfarArray;
    unsigned long maxEntries;
        
};

#endif


