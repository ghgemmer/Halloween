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
This derived class allows values stored in a normal unit16_t array to be read based on the index
the certain functionalities.
*/
#ifndef NormalArray_values_reader_h
#define NormalArray_values_reader_h

#include <inttypes.h>
#include "indexed_values_reader.h"

class NormalArray_values_reader : public indexed_values_reader 
{  
  public:
  	NormalArray_values_reader();
    NormalArray_values_reader(const uint16_t * values_array, unsigned long max_entries);
    void Modify(const uint16_t * values_array, unsigned long max_entries);
 
    // read the value associated with index   
    virtual uint16_t read(unsigned long index);
        
    protected:
    const uint16_t * valuesArray;
    unsigned long maxEntries;
        
};

#endif


