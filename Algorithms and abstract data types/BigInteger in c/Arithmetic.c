#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BigInteger.h"
#include"List.h"

int main(int argc, char * argv[]) {
	FILE* in;
	FILE* out;
	int count = 0;
	BigInteger N = newBigInteger();
	BigInteger N2 = newBigInteger();
	BigInteger N3 = newBigInteger();
	BigInteger N4 = newBigInteger();
	BigInteger N5 = newBigInteger();

	char str[10000] = " ";
	char str2[10000] = " ";

	if (argc != 3) {
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL) {
		printf("ERROR: INPUT FILE NOT FOUND");
		exit(1);
	}
	if (out == NULL) {
		printf("ERROR: OUTPUT FILE NOT FOUND");
		exit(1);
	}
	fscanf(in, "%d", &count);
	fscanf(in,"%s", str);

	fscanf(in,"%d", &count);
	fscanf(in,"%s", str2);


	N = stringToBigInteger(str);
	N2 = stringToBigInteger(str2);
	printBigInteger(out, N);
	fprintf(out,"%c",'\n');
	printBigInteger(out, N2);
	fprintf(out,"%c",'\n');

	N3 = sum(N,N2);
	printBigInteger(out, N3);
	fprintf(out,"%c",'\n');



	N3 = diff(N,N2);
	printBigInteger(out,N3);
	fprintf(out,"%c",'\n');

	N3 = diff(N,N);
	printBigInteger(out,N3);
	fprintf(out,"%c",'\n');

	char str3[10] = {"3"};
	char str4[10] = {"2"};
	N4 = stringToBigInteger(str3);
	N5 = stringToBigInteger(str4);

    N = prod(N,N4);
    N2 = prod(N2,N5);

	N3 = diff(N,N2);
	printBigInteger(out,N3);
	fprintf(out,"%c",'\n');

	N = stringToBigInteger(str);
	N2 = stringToBigInteger(str2);

	N3 = prod(N,N2);
	printBigInteger(out,N3);
	fprintf(out,"%c",'\n');

	N3 = prod(N,N);
	printBigInteger(out,N3);
	fprintf(out,"%c",'\n');

	N3 = prod(N2,N2);
	printBigInteger(out,N3);
	fprintf(out,"%c",'\n');

	char str5[10] = {"9"};
	char str6[10] = {"16"};
	N4 = stringToBigInteger(str5);
	N5 = stringToBigInteger(str6);

    N = prod(N,N);
    N = prod(N,N);
    N = prod(N,N);
    N = prod(N,N4);

    N2 = prod(N2,N2);
    N2 = prod(N2,N2);
    N2 = prod(N2,N2);
    N2 = prod(N2,N2);
    N2 = prod(N2,N5);

    N3 = sum(N,N2);
    printBigInteger(out,N3);
	fprintf(out,"%c",'\n');


    freeBigInteger(&N);
    freeBigInteger(&N2);
    freeBigInteger(&N3);
    freeBigInteger(&N4);
    freeBigInteger(&N5);








	return 0;
}
