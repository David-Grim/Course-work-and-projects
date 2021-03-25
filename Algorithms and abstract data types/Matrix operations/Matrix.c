#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"
#include <string.h>

typedef struct EntryObj {
	double data;
	int column;

} EntryObj;

typedef EntryObj* Entry;


typedef struct MatrixObj {
	List* row;
	int NNZ;
	int size;



} MatrixObj;


Entry newEntry(int col, double data) {
	Entry E;
	E = malloc(sizeof(EntryObj));
	E->data = data;
	E->column = col;
	return E;
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	M->row = calloc(n+1,sizeof(List));
	for (int i = 0; i < n+1; i++) {
		M->row[i] = newList();
	}
	M->size = n;
	M->NNZ = 0;
	return M;
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
	if (pM != NULL && *pM != NULL) {
		free(*pM);
		*pM = NULL;
	}
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	return M->NNZ;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	Entry EA;
	Entry EB;
	if (size(A) != size(B)) {
		return 0;
	}
	if(A->NNZ != B->NNZ){
        return 0;
	}
	if(A == B){
        return 1;
	}
	for (int i = 1; i <= size(A); i++) {
		moveFront(A->row[i]);
		moveFront(B->row[i]);
		while (index(A->row[i]) >= 0 &&  index(B->row[i])>=0) {
			EA = (Entry)get(A->row[i]);
			EB = (Entry)get(B->row[i]);
			if (EA->column == EB->column && EA->data == EB->data) {
				moveNext(A->row[i]);
				moveNext(B->row[i]);
			}
			else
				return 0;

		}
	}
	return 1;

}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M) {
	for (int i = 0; i <= size(M); i++) {
		clear(M->row[i]);
	}
	M->NNZ = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
	Entry E = NULL;
	Entry E2 = newEntry(j, x); //create the entry to append.
	int numFound = 0; //boolean
	moveFront(M->row[i]);
	//look to see if the column is found in row
	while (index(M->row[i]) != -1) {
		E = (Entry)get(M->row[i]);
		if (E->column == j)
			numFound = 1;
		if ( numFound == 1) {// if number exists and x == 0 then delete that entry
			if (x == 0.0) {
				delete(M->row[i]);
				M->NNZ--;
			}
			else {
				E->data = x;
			}
		}
		moveNext(M->row[i]);
	}
//if column does not exist we must add entry to the list if x != 0
	if (numFound==0 && x != 0.0) {
		moveFront(M->row[i]);
		if (index(M->row[i]) == -1) {
			append(M->row[i],E2);
			M->NNZ++;
		}
		else {
			while (index(M->row[i]) > -1 && E->column < j) {
				moveNext(M->row[i]);
			}
			if (index(M->row[i]) > -1) {
				insertBefore(M->row[i],E2);
				M->NNZ++;
			}
			else {
				append(M->row[i],E2);
				M->NNZ++;

			}
		}
	}

}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	Matrix M = newMatrix(size(A));
	for (int i = 1; i <= size(A); i++) {
		for (moveFront(A->row[i]); index(A->row[i]) != -1; moveNext(A->row[i])) {
			Entry E = get(A->row[i]);
			changeEntry(M, i, E->column, E->data);
		}
	}
	M->NNZ = A->NNZ;
	return M;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
	Matrix M = newMatrix(size(A));
	Entry E;
	for (int i = 1; i <= size(A); i++) {
		moveFront(A->row[i]);
		while (index(A->row[i]) != -1) {
			E = (Entry)get(A->row[i]);
			changeEntry(M, E->column, i , E->data);
			moveNext(A->row[i]);
		}
	}
	return M;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	Matrix M = newMatrix(size(A));
	Entry E;
	for (int i = 1; i <= size(A); i++) {
		if (length(A->row[i]) != 0) {
			moveFront(A->row[i]);
			while (index(A->row[i]) != -1) {
				E = (Entry)get(A->row[i]);
				changeEntry(M, i, E->column, E->data * x);
				moveNext(A->row[i]);
			}
		}
	}
	return M;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	int c = 0;
	double d1 = 0;
	double d2 = 0;
	Entry E1;
	Entry E2;
	Matrix M = newMatrix(size(A));
	if (size(A) != size(B)) {
		printf("ERROR: Matrices not of the same size");
		exit(1);
	}
	if(equals(A,B) == 1){
        return scalarMult(2.0,A);
	}
	for (int i = 1; i <= size(A); i++) {
		if (length(B->row[i]) == 0 && length(A->row[i]) != 0) {
			moveFront(A->row[i]);
			while (index(A->row[i]) != -1) {
				E1 = (Entry)get(A->row[i]);
				changeEntry(M, i, E1->column, E1->data);
				moveNext(A->row[i]);
			}
		}
		else if (length(B->row[i]) != 0 && length(A->row[i]) == 0) {
			moveFront(B->row[i]);
			while (index(B->row[i]) != -1) {
				E2 = (Entry)get(B->row[i]);
				changeEntry(M,i, E2->column, E2->data);
				moveNext(B->row[i]);
			}
		}
		else if (length(B->row[i]) != 0 && length(A->row[i]) != 0) {
			moveFront(A->row[i]);
			moveFront(B->row[i]);
			while (index(B->row[i]) != -1 && index(A->row[i]) != -1) {
				E1 = (Entry)get(A->row[i]);
				E2 = (Entry)get(B->row[i]);
				if (E2->column == E1->column) {
					d1 = E2->data;
					d2 = E1->data;
					c = E1->column;
					changeEntry(M,i, c, (d1 + d2));
					moveNext(B->row[i]);
					moveNext(A->row[i]);
				}
				else if (E2->column < E1->column) {
					d1 = E2->data;
					c = E2->column;
					changeEntry(M,i, c, d1);
					moveNext(B->row[i]);
				}
				else if (E2->column > E1->column) {
					d2 = E1->data;
					c = E1->column;
					changeEntry(M,i, c, d2);
					moveNext(A->row[i]);
				}
			}
			while (index(B->row[i]) != -1) {
				E2 = (Entry)get(B->row[i]);
				changeEntry(M,i, E2->column, E2->data);
				moveNext(B->row[i]);
			}

			while (index(A->row[i]) != -1) {
				E1 = (Entry)get(A->row[i]);
				changeEntry(M, i, E1->column, E1->data);
				moveNext(A->row[i]);
			}
		}
	}
	return M;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    int s = size(A);
    if(equals(A,B)==1){
        A = newMatrix(s);
        return A;
    }
    else{
    B = scalarMult(-1, B);
	A = sum(A, B);
	return A;
    }

}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    Matrix temp1 = newMatrix(size(A));
    Matrix temp2 = transpose(B);
    for(int i = 1; i <= size(A); ++i) {
        if(length(A->row[i]) != 0){
            for(int j = 1; j <= size(A); ++j) {
                if(length(temp2->row[j]) != 0){
                    changeEntry(temp1,i, j, dot(A->row[i], temp2->row[j]));
                }
            }
        }
    }
		return temp1;


}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is representedNonEmpty_equals as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	Entry E;
	for (int i = 1; i <= size(M); i++) {
		if (length(M->row[i]) > 0) {
			fprintf(out, "%d: ", i);
			moveFront(M->row[i]);
			while (index(M->row[i]) >= 0) {
				E = (Entry)get(M->row[i]);
				if (length(M->row[i]) > 0 && E->data != 0.0) {
					fprintf(out, "(%d, ", E->column);
					fprintf(out, "%.1f)", E->data);
					moveNext(M->row[i]);
				}
			}
			fprintf(out, "\n");
		}

	}
	fprintf(out, "\n");
}
double dot(List P, List Q) {
	double d = 0.0;
	moveFront(P);
	moveFront(Q);
	while (index(P) >= 0 && index(Q) >= 0) {
		Entry a = (Entry)get(P);
		Entry b = (Entry)get(Q);
		if (a->column > b->column) {
			moveNext(Q);
		}
		else if (a->column < b->column) {
			moveNext(P);
		}
		else {
			d += (a->data * b->data);
			moveNext(P);
			moveNext(Q);
		}
	}
	return d;

}
