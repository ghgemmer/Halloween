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
