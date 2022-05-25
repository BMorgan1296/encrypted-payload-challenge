#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Hiding this from compilation
//From https://github.com/Marghrid/TinyRSA/blob/master/encrypt.c
// long encrypt(char chr, long N, long e)
// {
// 	long tmp_msg = (long)chr, final_msg = 1, i;

// 	for (i = 0; e > 0; ++i) {
// 		if (e%2)
// 			final_msg = (final_msg * tmp_msg) % N;
// 		e /= 2;
// 		tmp_msg = (tmp_msg * tmp_msg) % N;
// 	}
// 	return final_msg;
// }

//From https://github.com/Marghrid/TinyRSA/blob/master/decrypt.c
long decrypt(long init_msg, long N, long e_til)
{
	long final_msg = 1, i;

	for (i = 0; e_til; ++i)
	{
		if (e_til%2)
			final_msg = (final_msg * init_msg) % N;
		e_til /= 2;
		init_msg = (init_msg * init_msg) % N;
	}
	return final_msg;
}

//Hiding this from compilation
// static const unsigned char code[] = {
// 	0x31, 0xc0,
// 	0x31, 0xdb,
// 	0x31, 0xc9,
// 	0x31, 0xd2,
// 	0xff, 0xc0,
// 	0x0f, 0xa2,
// 	0xc3
// };

long enc[] = {382339, -323385, 382339, -146022, 382339, -2594726, 382339, -908507, -1, -323385, 628298, -1654734, -166880};

int main()
{
	uint64_t ret = 0;
	uint64_t (*foo_func)();

	long N = 2732927; //long secret = 984913;
	long pub = 97;

	//Get the size of the encrypted payload
	int size = 0;
	while(enc[size] != 0)
		size++;

	unsigned char *dec = malloc(size * sizeof(unsigned char));
	//decrypt the payload
	for (int i = 0; i < size; ++i)
		dec[i] = decrypt(enc[i], N, pub);

	//Map executable section of a single 4kb page into memory
	foo_func = mmap(NULL, 4096, (PROT_READ | PROT_WRITE | PROT_EXEC), (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
	if(foo_func == MAP_FAILED)
	{
		perror("mmap()");
		exit(0);
	}

	//Copy the decrypted x86_64 payload into the mmap'd section
	memcpy(foo_func, dec, size);
	//Run
	ret = foo_func();
	//Print the result of the code
	printf("%lu\n", ret);

	free(dec);
	return ret;
}
