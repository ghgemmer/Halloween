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
This class is the base class for the indexed values reader functionality.
This class reads a value associated with an index
Derived classes of this allow different constructors to handle different ways the values are stored such as
normal addressable array,  array in PROGMEM, values stored on a SD card, etc.
Thus a class dervied off of this can be instantiated and passed to another class to hide the
mechanics of where the indexed values are stored and how they are accessed.
*/
#ifndef indexed_values_reader_h
#define indexed_values_reader_h

#include <inttypes.h>

class indexed_values_reader 
{  
  public:
    indexed_values_reader();
 
    // read the value associated with index   
    virtual uint16_t read(unsigned long index);
        
    protected:   
};

#endif


