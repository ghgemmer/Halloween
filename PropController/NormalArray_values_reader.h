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


