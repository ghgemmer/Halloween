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
// The following is now defined in pgmspace.h so is compiled out here.  Remove once verify code works ok
#if 0
#define pgm_get_far_address(var) \
({                                                    \
	uint_farptr_t tmp;                                \
                                                      \
    __asm__ __volatile__(                             \
                                                      \
            "ldi    %A0, lo8(%1)"           "\n\t"    \
            "ldi    %B0, hi8(%1)"           "\n\t"    \
            "ldi    %C0, hh8(%1)"           "\n\t"    \
            "clr    %D0"                    "\n\t"    \
        :                                             \
            "=d" (tmp)                                \
        :                                             \
            "p"  (&(var))                             \
    );                                                \
    tmp;                                              \
})
#endif
#endif
