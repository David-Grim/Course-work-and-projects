#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"BigInteger.h"

long power = 9;
long base = 1000000000;

typedef struct BigIntegerObj {
	int sign;
	List l;
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger() {
	BigInteger N = malloc(sizeof(BigIntegerObj));
	N->sign = 0;
	N->l = newList();
	return N;
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N) {
	return N->sign;

}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B) {


	if (equals(A, B) == 1) {
		return 0;
	}

	if (A->sign == 1 && B->sign == -1) {
		return 1;
	}
	if (A->sign == -1 && B->sign == 1) {
		return -1;
	}
	if (A->sign == B->sign) {
		if (A->sign == -1) {
			if (length(A->l) > length(B->l)) {
				return -1;
			}
			else if (length(A->l) < length(B->l)) {
				return 1;
			}
			else {
				moveFront(A->l);
				moveFront(B->l);
				while(get(A->l) == get(B->l)&&index(A->l)!= -1){
                    moveNext(A->l);
                    moveNext(B->l);
				}
				if(get(A->l)>get(B->l))
                    return -1;
                else if(get(A->l)<get(B->l))
                    return 1;
                else return 0;
				/*if (get(A->l) > get(B->l)) {
					return -1;
				}
				else if (get(A->l) < get(B->l)) {
					return 1;
				}
				else {
					moveNext(A->l);
					moveNext(B->l);
					if (get(A->l) > get(B->l)) {
						return -1;
					}
					else if (get(A->l) < get(B->l)) {
						return 1;
					}
					else {
						moveNext(A->l);
						moveNext(B->l);
						if (get(A->l) > get(B->l)) {
							return -1;
						}
						else if (get(A->l) < get(B->l)) {
							return 1;
						}
						else {
							moveNext(A->l);
							moveNext(B->l);
							if (get(A->l) > get(B->l)) {
								return -1;
							}
							else if (get(A->l) < get(B->l)) {
								return 1;
							}
							else {
								return 0;
							}

						}

					}



				}*/

			}


		}

		else if (A->sign == 1) {
			if (length(A->l) > length(B->l)) {
				return 1;
			}
			else if (length(A->l) < length(B->l)) {
				return -1;
			}
			else {
				moveFront(A->l);
				moveFront(B->l);
				while(get(A->l) == get(B->l)&&index(A->l)!= -1){
                    moveNext(A->l);
                    moveNext(B->l);
				}
				if(get(A->l)>get(B->l))
                    return 1;
                else if(get(A->l)<get(B->l))
                    return -1;
                else return 0;
				/*if (get(A->l) > get(B->l)) {
					return -1;
				}
				else if (get(A->l) < get(B->l)) {
					return 1;
				}
				else {
					moveNext(A->l);
					moveNext(B->l);
					if (get(A->l) > get(B->l)) {
						return 1;
					}
					else if (get(A->l) < get(B->l)) {
						return -1;
					}
					else {
						moveNext(A->l);
						moveNext(B->l);
						if (get(A->l) > get(B->l)) {
							return 1;
						}
						else if (get(A->l) < get(B->l)) {
							return -1;
						}
						else {
							return 0;
						}

					}

				}


*/
			}
		}

	}
}






// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
	if (listEquals(A->l, B->l) == 1 && A->sign == B->sign) {
		return 1;
	}
	else
		return 0;
}
// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N) {
	clear(N->l);
	append(N->l,0);
	N->sign = 0;
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
	if (N->sign == 1)
		N->sign = -1;
	else if (N->sign == -1)
		N->sign = 1;
	else
		return;


}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s) {
	BigInteger N = newBigInteger();
	long num = 0;
	int count = 0;
	int i = 0;
	if(s[0] == '-'){
        N->sign = -1;
        count++;
	}
	else if(s[0] == '+'){
        N->sign = 1;
        count++;
	}
	else{
        N->sign  = 1;
	}

	while(s[count] == '0'){
        count++;
	}
	if(s[0] == '-'||s[0] == '+'){
        for( i=count ; i<strlen(s) ; i++){
        num = s[i] - '0';
        append(N->l,num);
        }
	}
	else{
        for( i=count ; i<strlen(s); i++){
        num = s[i] - '0';
        append(N->l,num);
        }
	}
	return N;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
	BigInteger N2 = newBigInteger();
	N2->sign = N->sign;
	N2->l = copyList(N->l);
	return N2;

}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
	BigInteger temp;
	temp = sum(A, B);
	S->l = temp->l;
	S->sign = temp->sign;
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B) {
  //  A = copy(A);
   // B = copy(B);
	BigInteger N = newBigInteger();
	long carry = 0;
	long s = 0;
	BigInteger temp;
	if (equals(A, B) == 1) {
		A = copy(A);
	}


	if (A->sign == 1  && B->sign == -1) {
		temp = copy(B);
		temp->sign = 1;
		return diff(A, temp);
	}
	else if (A->sign == -1 && B->sign == 1) {
		temp = copy(A);
		temp->sign = 1;
		return diff(B,temp);


	}
	else {
		if (A->sign == 0 ) {
			return B;
		}
		else if (B->sign == 0) {
			return A;
		}
		moveBack(A->l);
		moveBack(B->l);
		while (index(A->l) != -1 && index(B->l) != -1) {
			s = get(A->l) + get(B->l) + carry;
			if (s >= 10 ) {
				carry = 1;
				s -= 10;
			}
			else {
				carry = 0;
			}
			prepend(N->l, s);
			movePrev(A->l);
			movePrev(B->l);
		}

		while (index(A->l) != -1) {

			prepend(N->l, get(A->l)+carry);
			movePrev(A->l);
			carry = 0;

		}
		while (index(B->l) != -1) {
			prepend(N->l, get(B->l) +carry);
			movePrev(B->l);
		}


	}
	if(A->sign == -1 && B->sign == -1){
        N->sign = -1;
	}
	else if(A->sign == 1 && B->sign == 1){
        N->sign = 1;
	}
	else if(A->sign == 0 && B->sign != 0){
        return copy(B);
	}
	else if(B->sign == 0 && A->sign != 0){
        return copy(A);
	}
	else if(A->sign == 0 && B->sign == 0){
        makeZero(N);
        return N;
	}
	return N;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
    BigInteger temp;
	temp = diff(A, B);
	D->l = temp->l;
	D->sign = temp->sign;
	if(compare(A,B) == 1)
        D->sign = 1;
    if(compare(A,B) == -1)
        D->sign = -1;

}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
	BigInteger N = newBigInteger();
	BigInteger temp;
	BigInteger temp2;
	long carry = 0;
	long s = 0;

	if(equals(A,B)==1){
		return N;
	}
	if(compare(A,B) == 1)
            N->sign = 1;
        else if(compare(A,B) == -1)
            N->sign = -1;

	if (A->sign == 1 && B->sign == -1) {
		temp = copy(B);
		negate(temp);
		temp->sign = -1;
		return sum(A, temp);
	}
	else if (B->sign == 1 && A->sign == -1) {
		temp = copy(B);
		negate(temp);
		temp->sign = -1;
		return sum(temp, A);
	}
	else{

		if (A->sign == -1 && B->sign == -1) {
            temp = copy(A);
			temp2 = copy(B);
			moveBack(A->l);
			moveBack(B->l);
			while (index(A->l) != -1 && index(B->l) != -1) {
				if (compare(temp, temp2) == 1) {
                    N->sign = 1;
					s = get(B->l) - get(A->l) + carry;
					if (s < 0) {
						carry = -1;
						s += 10;
					}
					else
						carry = 0;
				}
				else {
                    N->sign = -1;
					s = get(A->l) - get(B->l) + carry;
					if (s < 0) {
						carry = -1;
						s += 10;
					}
					else
						carry = 0;
				}

				prepend(N->l, s);
				movePrev(A->l);
				movePrev(B->l);
			}
			while (index(A->l) != -1) {
				prepend(N->l, get(A->l));
				movePrev(A->l);
				carry = 0;
			}
			while (index(B->l) != -1) {
				prepend(N->l, get(A->l) );
				movePrev(A->l);
				carry = 0;
			}
		}
		else if (A->sign == 1 && B->sign == 1) {
			temp = copy(A);
			temp2 = copy(B);
			moveBack(A->l);
			moveBack(B->l);
			while (index(A->l) != -1 && index(B->l) != -1) {
				if (compare(temp, temp2) == 1) {
                    N->sign = 1;
					s = get(A->l) - get(B->l) + carry;
					if (s < 0) {
						carry = -1;
						s += 10;
					}
					else
						carry = 0;
				}
				else {
                    N->sign = -1;
					s = get(B->l) - get(A->l) + carry;
					if (s < 0) {
						carry = -1;
						s += 10;
					}
					else
						carry = 0;
				}
				prepend(N->l, s);
				movePrev(A->l);
				movePrev(B->l);
			}
			while (index(A->l) != -1) {
				prepend(N->l, get(A->l) + carry);
				movePrev(A->l);
				carry = 0;
			}
			while (index(B->l) != -1) {
				prepend(N->l, get(A->l) + carry);
				movePrev(A->l);
				carry = 0;
			}

		}
		if(compare(A,B) == 1)
            N->sign = 1;
        if(compare(A,B) == -1)
            N->sign = -1;

	}

	return N;

}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {
	BigInteger temp;
	temp = prod(A, B);
	P->l = temp ->l;
	P->sign = temp->sign;
	if(A->sign == -1 && B->sign == -1){
        P->sign = 1;
	}
	if(A->sign == 1 && B->sign == 1){
        P->sign = 1;
	}
	if(A->sign == 1 && B->sign == -1){
        P->sign = -1;
	}
	if(A->sign == -1 && B->sign == 1){
        P->sign = -1;
	}
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {
	BigInteger N = newBigInteger();
	BigInteger N2 = newBigInteger();
	BigInteger N3 = newBigInteger();

	long s = 0;
	long carry = 0;
	long temp = 0;
	long count = 1;
	if(equals(A,B)==1){
        A = copy(A);
	}
	if(A->sign == -1 && B->sign == -1){
		N->sign =1;
	}
	else if(A->sign == -1 && B->sign == 1){
		N->sign = -1;
	}
	else if(B->sign == -1&& A->sign == 1){
		N->sign = -1;
	}
	else{
		N->sign = 1;
	}
	moveBack(B->l);
	while (index(B->l) != -1) {
		moveBack(A->l);
		while (index(A->l) != -1) {
			s = get(A->l) * get(B->l) + carry;
			if (s > 10 && index(A->l) != 0) {
				carry = s/10;
				temp = carry * 10;
				s -= temp;
			}
			else {
				carry = 0;
			}
			prepend(N->l, s);
			movePrev(A->l);

		}
		for (int j = 0; j < count; j++) {
			append(N->l, 0);
		}


		N2 = copy(N);
		N3 = sum(N2,N3);
		makeZero(N);
		movePrev(B->l);
		count++;
	}


	if (A->sign == 0 || B->sign == 0) {
		N->sign = 0;
	}
	return N3;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N) {

	if(N->sign == 0)
		fprintf(out,"%d",0);
	else{
		moveFront(N->l);
		if (N->sign == -1) {
			fprintf(out, "%c", '-');
		}
		while (index(N->l) >= 0) {
			fprintf(out, "%lu", get(N->l));
			moveNext(N->l);
		}
	}
	fprintf(out,"%c", '\n');
}
