#ifndef GRAY_DYNAMIC_H__INC
#define GRAY_DYNAMIC_H__INC

#include "GrayShared.hpp"

// Fill a with Gray codes
void gray_dynamic(code_t* a, codesize_t s,GrayView t);

// Compare static and dynamic generated codes
bool gray_check(code_t,code_t,codesize_t);

void print_success(const char*);

#endif
