#include "merge.h"
#include <pthread.h>
#include <wait.h>

//for easy storage of the parameters in the multithreaded function. 
struct data{
  int left;
  int middle;
  int right; 
  int index; 
  int* array; 
};

pthread_t threads[4];

/* LEFT index and RIGHT index of the sub-array of ARR[] to be sorted */
void singleThreadedMergeSort(int arr[], int left, int right){
  if (left < right) {
    int middle = (left + right)/2;
    singleThreadedMergeSort(arr, left, middle); 
    singleThreadedMergeSort(arr, middle + 1, right); 
    merge(arr, left, middle, right); 
  } 
}

/* 
	Helper function for the pthread_create function. Each thread takes
	a piece of the array to calculate. which thread/section of this is found 
	by the index element. pthread_join is needed for the threads to merge
  at the right time without merging before the sub arrays are sorted. 
*/
void* sortHelper(void* arg){
  struct data* d = (struct data*) arg;
  switch(d -> index){
  	case 0://furthest left piece to middle/2
  		singleThreadedMergeSort(d->array,d -> left, d -> middle/2);
      //wait(NULL);
  		pthread_join(threads[1], NULL);//wait for thread1 to be finished for merge
    	merge(d->array, d -> left, (d -> middle)/2, d -> middle);
  		break;
  	case 1://second from the left piece to middle
  		singleThreadedMergeSort(d->array,(d -> middle)/2 + 1, d -> middle);
  		break;
  	case 2://middle + 1 to in between middle and right 
  		singleThreadedMergeSort(d->array,d -> middle + 1, (d->right) - (d->middle)/2);
      //wait(NULL);
  		pthread_join(threads[3],NULL);//wait for thread3 to be finished for merge
      merge(d->array, (d -> middle) + 1, (d -> right) - (d -> middle/2), (d -> right));
  		break;
  	case 3://in between middle right to right
  		singleThreadedMergeSort(d->array, (d -> right) - (d -> middle)/2 + 1, d -> right);
      break;
  }
  pthread_exit(NULL);
  return NULL;
}



/* 
  uses a struct to pass the parameters to the helper function more easily.
  array in the struct points to arr here and the helper function manipulates
  that array. divides the array into four, merges the four into two, and
  ultimately merges the two to one in the original function.

*/
void multiThreadedMergeSort(int arr[], int left, int right){
  struct data params[4]; 
  int middle = (right + left)/2;
  if(left < right){
  	for(int i = 0; i <= 3; i++){//create the threads and set params
  		params[i].index = i;//keeps track of which thread we are on
    	params[i].array = arr;//point to arr
    	params[i].left = left;//left index
    	params[i].middle = middle;//middle index
   		params[i].right = right;//right index
   		pthread_create(&threads[i], NULL, sortHelper,&params[i]); 
  	}
    for(int i = 0; i <= 3; i++){
      pthread_join(threads[i], NULL);//need to wait for all threads to be done for final merge
    }
    merge(arr, left, middle, right);//merge the two halves
  }
}