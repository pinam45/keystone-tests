#include <testKeystone.h>

#include <keystone/keystone.h>

int testKeystone(int ksMode, const TestInstruction* table, size_t tableSize)
{

	ks_engine* pKeystoneHandle;
	ks_err err = ks_open(KS_ARCH_MIPS, ksMode, &pKeystoneHandle);

	if(err)
	{
		printf("[ERROR  ] ks_open\n");
		return EXIT_FAILURE;
	}

	for(size_t i = 0; i < tableSize; ++i)
	{
		unsigned char* encoding;
		size_t encodingSize;
		size_t nbInstr;
		if(!ks_asm(pKeystoneHandle, table[i].txt, 0, &encoding, &encodingSize, &nbInstr))
		{
			fflush(stderr);
			if(*((uint32_t*) encoding) == table[i].data)
			{
				printf("[SUCCESS] %s ---> 0X%08X\n", table[i].txt, *((uint32_t*) encoding));
			}
			else
			{
				printf("[FAILURE] %s -X-> 0X%08X\n", table[i].txt, *((uint32_t*) encoding));
			}
			ks_free(encoding);
		}
		else
		{
			printf("[ERROR  ] %s\n", ks_strerror(ks_errno(pKeystoneHandle)));
		}
	}

	ks_close(pKeystoneHandle);
	return EXIT_SUCCESS;
}
