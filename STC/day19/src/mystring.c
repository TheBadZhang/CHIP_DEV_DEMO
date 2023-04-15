#include "mystring.h"
#include "trick.h"

int strcmp_eq_n (char* a, char* b, int len) {
	int i;
	FOR (i, len) {
		if (*a++ != *b++) {
			return 0;
		}
	}
	return 1;
}