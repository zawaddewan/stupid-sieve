#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define getbit(A, i) ((A[(i)/8] & (1 << ((i)%8))))
#define setbit(A, i) (A[(i)/8] |= (1 << ((i)%8)))
#define clearbit(A, i) (A[(i)/8] &= ~(1 << ((i)%8)))

/*SPEED COMPARISON
1. sieve()
2. bitsieve3rd()
3. bitsieve()			//funny how my sieve that doesn't use bits is faster than the ones that do
4. halfsieve()
5. ogsieve()
*/
				   
int sieve(int n) { 
	int primes[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	if(n <= 10) {
		return primes[n];
	}
	int realsize = (n * (log(n) + log(log(n)) - 1 + ((log(log(n)) - 2) / log(n))) + 1000) / 3;
	int bound = (sqrt(3*realsize)-1) / 3 + 2;
	char *array = calloc(realsize,sizeof(char));
	n-=2;
	int o, m, j, k = 1, i = 1;
	while(i < bound) {
		if(!array[i]) {
			n--; 
			o = 3*i+1+k;
			m = i+k;
			j = 3*i*i+2*i;
			if(k){j+= 2*i + 1;}
			m *= !k-k;
			while(j < realsize) {
				array[j] = 'a';
				j+=o+m;
				m *= -1;
			};
		}
		k = !k;
		i++;
	}
	while(n) {
		n -= !array[i];
		i++;
	}
	return 3*(i-1)+1+((i-1)%2);
}

int halfsieve(int n) {
	int realsize = n*log(n*log(n)) / 2;
	int *array = malloc(realsize*sizeof(int));
	array[1] = 1;
	n-=1;
	for(int i = 1; i < realsize; i++) {
		if(array[i] != -1) {
			n--;
			int j = i+(2*i+1);
			while(j < realsize) {
				array[j] = -1;
				j+=2*i+1;
			}
		}
		if(n == 0) {
			return 2*i+1;
		}
	}
}

int bitsieve3rd(int n) {
	int size = (n * (log(n) + log(log(n)) - 1 + ((log(log(n)) - 2) / log(n)))) / 3;
	char *array = calloc(size/8, 1);
	int bound = (sqrt(3*size) - 1) / 3;
	int o, m, l, j, k = 1, i = 1;
	n -= 2;
	while(i < bound) {
		if(!getbit(array, i)) {
			n--;
			o = 3*i+1+k;
			m = i+k;
			j = 3*i*i+2*i*k+2*i+k;
			l = !k-k;
			while(j < size) {
				setbit(array, j);
				j+=o+m*l;
				l *= -1;
			};
		}
		k = !k;
		i++;
	}
	while(n) {
		n -= !getbit(array, i);
		i++;
	}
	return 3*(i-1)+1+(i-1)%2;
}

int bitsieve(int n) {
	int size = n*log(n*log(n));
	char *array = calloc(size/8, 1);
	clearbit(array, 2);
	int j;
	for(int i = 2;i < size; i++) {
		if(!(getbit(array, i) ^ 0)) {
			n--;
			j = i*i;
			if(n == 0) {
				return i;
			}
			while(i < sqrt(size) && j < size) {
				setbit(array, j);
				j += i;
			}
		}
	}
}

int ogsieve(int n) {
	int realsize = n*exp(log10(n)) / pow(log10(n), 1.8);
	int *array = malloc(realsize*sizeof(int));
	array[2] = 1;
	int j;
	n-=1;
	for(int i = 2; i < realsize; i++) {
		if(array[i] != -1) {
			n--;
			j = i*i;
			while(j < realsize && i < sqrt(realsize)) {
				array[j] = i;
				j += 2*i;
			}
		}
		if(n == 0) {
			return i;
		}
	}
}

int main() {
	for(int i = 0; i < 100; i++) {
		sieve(2000000);
	}
}