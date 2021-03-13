#ifndef program_memory_misc_h
#define program_memory_misc_h

#include <avr/io.h>
#include <avr/pgmspace.h>

// This macro when applied to a constant variable places them in flash memory after any PROGMEM section in memory (after but 
// not necessarily immediately after that section).
// This is accomplished by placing the PROGMEMSECTION2 after the .text section in the linker which is definitely after the PROGMEM section.
// This facilitates keeping constant variables with the PROGMEM attribute applied to them in the lower 64K of flash memory
// where they generally need to be as most of these are accessed with pgmspace routines that assume this.
// !!!! Access of a PROGMEMSECTION2 constant variable requires use of the ...far routines from pgmspace.h
#define PROGMEMSECTION2 __attribute__ ((section (".text.higher"))) 

#endif
