#ifndef program_memory_misc_items_h
#define program_memory_misc_items_h

#include <avr/io.h>
#include <avr/pgmspace.h>

//#define pgm_get_far_address(var) \
//({                                                    \
//	uint_farptr_t tmp;                                \
//                                                      \
//    __asm__ __volatile__(                             \
//                                                      \
//            "ldi    %A0, lo8(%1)"           "\n\t"    \
//            "ldi    %B0, hi8(%1)"           "\n\t"    \
//            "ldi    %C0, hh8(%1)"           "\n\t"    \
//            "clr    %D0"                    "\n\t"    \
//        :                                             \
//            "=d" (tmp)                                \
//        :                                             \
//            "p"  (&(var))                             \
//    );                                                \
//    tmp;                                              \
//})

#define GET_PROGRAM_MEMORY_ARRAY_ENTRY(srcPrgmArrayVariable, index, dstVariable) program_memory_misc_items::getPrgmMemory((uint16_t)sizeof(dstVariable), pgm_get_far_address(srcPrgmArrayVariable) + (((unsigned long)index) * (unsigned long)(sizeof(srcPrgmArrayVariable[0])))   , (uint8_t *)(&(dstVariable)))
// srcPrgmArrayVariable must be the name of a declared const static base array in PROGMEM
// dstVariable should be of the array entry type

class program_memory_misc_items
{
  public:
  	
		static void getPrgmMemory (uint16_t sizeBytes, uint_farptr_t src, uint8_t * dst);
};

#endif
