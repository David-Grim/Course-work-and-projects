/************************************************************************
 * 
 * CSE130 Winter 2021 Assignment 1
 * 
 * UNIX Shared Memory Multi-Process Merge Sort
 * 
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ************************************************************************/


#include "merge.h"
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> //for wait
#include <unistd.h> //for fork()

/* LEFT index and RIGHT index of the sub-array of ARR[] to be sorted */
void singleProcessMergeSort(int arr[], int left, int right){
  if (left < right) {
    int middle = (left+right)/2;
    singleProcessMergeSort(arr, left, middle); 
    singleProcessMergeSort(arr, middle+1, right); 
    merge(arr, left, middle, right); 
  } 
}

/* The majority of the structure here is heavily based upon
   the information from the concurrency 1 lecture slides. 
   some of the calls were copied directly from the slides, 
   such as: getting the schmid, creating the shared array, 
   the detach and control, the waiting, and of 
   course the structure of the switch statement. I simply 
   assumed the process could be generalized to apply to this 
   function.
*/
void multiProcessMergeSort(int arr[], int left, int right){
int middle = (left + right)/2;
if(left < right) {
	int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
	int *sh_array = (int*) shmat(shmid, (void*)0, 0);
	for(int i = 0; i < right + 1; i++){//fill with array to be sorted
		sh_array[i] = arr[i];
 	}

	switch(fork()){
		case -1://there was an issue in creating the child process
			printf("Fork unsuccessful, exiting program.");
 			exit(EXIT_FAILURE);
			break;
		case 0://we're in the child process
			sh_array = (int*)shmat(shmid, (void*)0, 0);
 			singleProcessMergeSort(sh_array, left, middle);
 			shmdt(sh_array);
 			shmctl(shmid, IPC_RMID, NULL);
 			exit(EXIT_SUCCESS);//child process executed correctly
			break;
		default://we're in the parent process
			singleProcessMergeSort(sh_array, middle + 1, right); 
 			wait(NULL);
 			merge(sh_array, left, middle, right);
 			for(int i = 0; i < right + 1; i++){//shared array was sorted, need to put elements back
 				arr[i] = sh_array[i];
 	    	}
 	    	shmdt(sh_array);
 			shmctl(shmid, IPC_RMID, NULL);
	}
  }
}


