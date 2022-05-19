#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAP_FLAGS (MAP_PRIVATE | MAP_ANONYMOUS)
#define PAGE_SIZE 4096

static const char code[] = {
	0x31, 0xc0,
	0x31, 0xdb,
	0x31, 0xc9,
	0x31, 0xd2,
	0xff, 0xc0,
	0x0f, 0xa2,
	//0x31, 0xdb,
	//0x89, 0xc3,
	//0x31, 0xc0,
	//0x88, 0xd8,
	//0x24, 0x0f,
	0xc3                                  
};

int main()
{
	uint64_t ret = 0;
	uint64_t (*foo_func)() = (void*)code;
	size_t len = PAGE_SIZE;
	foo_func = mmap(NULL, sizeof(uint8_t) * len, PROT_READ | PROT_WRITE | PROT_EXEC, MMAP_FLAGS, -1, 0);
	if(foo_func == MAP_FAILED)
	{
		perror("mmap()");
		exit(0);
	}
	memcpy(foo_func, code, sizeof(code));
	ret = foo_func();
	printf("%lu\n", ret);
	return ret;
}