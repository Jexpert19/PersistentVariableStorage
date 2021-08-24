#ifndef PGMSPACE_H
#define PGMSPACE_H

#ifndef UNIT_TEST
#include <avr/pgmspace.h>

#else
#define PROGMEM
#define PGM_P const char*
#define PSTR(s) s
#endif

#endif