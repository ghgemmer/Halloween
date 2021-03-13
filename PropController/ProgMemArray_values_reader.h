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


