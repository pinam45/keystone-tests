#ifndef KEYSTONE_TESTS_TESTKEYSTONE_H
#define KEYSTONE_TESTS_TESTKEYSTONE_H


#include <ext_headers.h>
EXT_HEADERS_OPEN
#include <stdio.h>
#include <stdint.h>
EXT_HEADERS_CLOSE

typedef struct TestInstruction
{
	const uint32_t data;
	const char* txt;
} TestInstruction;

int testKeystone(int ksMode, const TestInstruction* table, size_t tableSize);


#endif //KEYSTONE_TESTS_TESTKEYSTONE_H
