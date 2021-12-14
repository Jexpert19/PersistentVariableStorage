#pragma once
#include <stdio.h>

#ifdef UNIT_TEST

#define sscanf_P sscanf

int printf_P(const char *__format, ...);

#endif