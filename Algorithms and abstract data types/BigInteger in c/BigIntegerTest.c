#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"BigInteger.h"


int main() {

	BigInteger N = newBigInteger();
	BigInteger N2 = newBigInteger();
	BigInteger N3 = newBigInteger();
	char str[100] = {"918453454353423465456345634563456345"};
	char str2[100] = {"913456345634563567356784678435234524564576645234345878"};

	N = stringToBigInteger(str);
	N2 = stringToBigInteger(str2);
	printBigInteger(stdout, N);
	printBigInteger(stdout, N2);

	printf("N+N\n");
	N3 = sum(N, N);
	printBigInteger(stdout, N3);

	printf("N+N2\n");
	add(N3,N,N2);
	printBigInteger(stdout, N3);

	printf("N-N2\n");
	N3 = diff(N, N2);
	printBigInteger(stdout, N3);

	printf("N+N2\n");
	subtract(N3,N,N2);
	printBigInteger(stdout, N3);

	printf("compare N with N2\n");
	printf("%d",compare(N,N2));

    printf("N*N2\n");
	N3 = prod(N, N2);
	printBigInteger(stdout, N3);

    printf("N*N\n");
	multiply(N3,N,N));
	printBigInteger(stdout, N3);

    printf("Negate N\n");
    N = negate(N);
    printBigInteger(stdout, N);

    printf("see if N equals itself\n");
    if(equals(N,N)==1){
        printf("they are equal \n");
    }
    else
        printf("they are not equal\n");


    printf("zero out N3\n");
    makeZero(N3);
    printBigInteger(stdout, N3);











	system("pause");
	return 0;
}
