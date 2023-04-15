#include "../inc/random.h"

static long __holdrand = 1L;
void srand (unsigned int seed) {
	__holdrand = (long)seed;
}
int rand (void) {
	return(((__holdrand = __holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}