#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include<string.h>

int numberCount(FILE* fpointer);

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	int numbers = 0;

	if(argc != 3){
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

	numbers += numberCount(in);
	
	fclose(in);
	char a[1100][1100];

	int i = 0;
	in = fopen(argv[1], "r");

	while (fgets(a[i], 1100,in) != NULL) {
		a[i][strlen(a[i]) - 1] = '\0';
		i++;
	}
	fclose(in);
	List L = newList();

	
	for (int i = 0; i < numbers; i++) {
		moveFront(L);
		while (index(L) >= 0) {
			if (strcmp(a[get(L)], a[i] ) > 0) {
				insertBefore(L, i);
				break;
			}
			moveNext(L);
		}
		if (index(L) < 0) {
			append(L, i);
		}
	}
	
	
	moveFront(L);
	int x = 0;
	while (x < numbers) {
		fprintf(out,"%s\n",a[get(L)]);
		
		moveNext(L);
		x++;
	}
	fclose(out);
	
	
	//system("pause");
	return(0);
}

int numberCount(FILE* fpointer) {
	int i = 0;
	char ch;
	while ((ch = fgetc(fpointer)) != EOF) {
		if (ch == '\n') {
			i++;
		}
	}
	
	return i;
}
