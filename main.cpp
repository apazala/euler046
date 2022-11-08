#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LIMIT 50000

int primesList[5200];
int numprimes;
void fillprimes(int upperBound);

uint64_t iscompound[1 + ((LIMIT+1)>>6)];
int hits[LIMIT+1];

void init() {
	fillprimes(LIMIT);

	for (int i = 1; ; i++) {
		int sq2 = 2 * i*i;
		if (sq2 > LIMIT) break;

		for (int j = 1; ; j++) {
			int v = primesList[j] + sq2;
			if (v > LIMIT) break;

			hits[v]=1;
		}
	}
}


#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

int main()
{
	int t;

	init();

    int res = -1;
	for (int i = 9; res == -1 && i < LIMIT; i += 2) {
		if (baisset(iscompound, i)) {
			if (!hits[i]) {
				res = i;
			}
		}
	}

    //-1 = not found
	printf("%d\n", res);

	return 0;
}


void fillprimes(int upperBound) {
	int i, j;


	baset(iscompound, 0);
	baset(iscompound, 1);
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

	for (i = sqrtUb + 1; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
		}
	}

}