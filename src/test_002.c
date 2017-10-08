#include <ext_headers.h>
EXT_HEADERS_OPEN
#include <stdio.h>
#include <stdlib.h>
#include <keystone/keystone.h>
EXT_HEADERS_CLOSE

#include <testKeystone.h>

#define COUNT_OF(X) (sizeof(X)/sizeof(*(X)))

static const TestInstruction Mips32TestInstructions[] = {
  {0Xd8000000, "j"},
};

int main()
{
	printf("### TEST: incomplete j instruction alone\n");

	return testKeystone(KS_MODE_32 ,Mips32TestInstructions, COUNT_OF(Mips32TestInstructions));
}
