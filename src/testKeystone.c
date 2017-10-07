#include <testKeystone.h>

#include <keystone/keystone.h>

#define BIN_FORMAT_8 "%d%d%d%d%d%d%d%d"
#define BIN_FORMAT_16 BIN_FORMAT_8 " " BIN_FORMAT_8
#define BIN_FORMAT_32 BIN_FORMAT_16 " " BIN_FORMAT_16
#define BIN_FORMAT_64 BIN_FORMAT_32 " " BIN_FORMAT_32
#define BIN_VALUE_8(v) ((v) >> 7) & 1,\
                       ((v) >> 6) & 1,\
                       ((v) >> 5) & 1,\
                       ((v) >> 4) & 1,\
                       ((v) >> 3) & 1,\
                       ((v) >> 2) & 1,\
                       ((v) >> 1) & 1,\
                       ((v) >> 0) & 1
#define BIN_VALUE_16(v) BIN_VALUE_8((v) >> 8), BIN_VALUE_8(v)
#define BIN_VALUE_32(v) BIN_VALUE_16((v) >> 16), BIN_VALUE_16(v)
#define BIN_VALUE_64(v) BIN_VALUE_32((v) >> 32), BIN_VALUE_32(v)

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
				printf("[SUCCESS] %s ---> 0X%08X (" BIN_FORMAT_32 ")\n", table[i].txt, *((uint32_t*) encoding),
				       BIN_VALUE_32(*((uint32_t*) encoding)));
			}
			else
			{
				printf("[FAILURE] %s -X-> 0X%08X (" BIN_FORMAT_32 ")\n", table[i].txt, *((uint32_t*) encoding),
				       BIN_VALUE_32(*((uint32_t*) encoding)));
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
