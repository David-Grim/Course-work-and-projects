#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"



int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	int n = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int row = 0;
	int col = 0;
	double data = 0.0;

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

	fscanf(in, "%i", &n);
	fscanf(in, "%i", &a);
	fscanf(in, "%i", &b);
	Matrix M1 = newMatrix(n);
	Matrix M2 = newMatrix(n);
	Matrix M3;

    int i = 0;
	while(i!=a){
        fscanf(in, "%i %i %lf", &row,&col,&data);
        changeEntry(M1,row,col,data);
        i++;

	}
	i = 0;

	while(i!=b){
         fscanf(in, "%i %i %lf", &row,&col,&data);
        changeEntry(M2,row,col,data);
        i++;
	}

    fprintf(out,"%s","A has ");
    fprintf(out,"%d ",a);
    fprintf(out,"%s","non-zero entries:\n");
    printMatrix(out,M1);

    fprintf(out,"B has ");
    fprintf(out,"%d ",b);
    fprintf(out,"%s","non-zero entries:\n");
    printMatrix(out,M2);

    fprintf(out,"%s","(1.5)*A =  \n");
    M3 = scalarMult(1.5,M1);
    printMatrix(out,M3);

    fprintf(out,"%s","A + B =  \n");
    M3=sum(M1,M2);
    printMatrix(out,M3);

    fprintf(out,"%s","A + A =  \n");
    M3=sum(M1,M1);
    printMatrix(out,M3);

    fprintf(out,"%s","B-A =  \n");
    M3=diff(M2,M1);
    printMatrix(out,M3);

    fprintf(out,"%s","A - A =  \n");
    M3=diff(M1,M1);
    printMatrix(out,M3);

    fprintf(out,"%s","Transpose(A) =  \n");
    M3=transpose(M1);
    printMatrix(out,M3);

    fprintf(out,"%s","A*B =  \n");
    M3=product(M1,M2);
    printMatrix(out,M3);

    fprintf(out,"%s","B*B =  \n");
    M3=product(M2,M2);
    printMatrix(out,M3);

    fclose(in);
    fclose(out);
	return(0);
}


