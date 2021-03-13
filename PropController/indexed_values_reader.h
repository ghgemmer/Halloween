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


