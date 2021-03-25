/************************************************************************
 * 
 * CSE130 Winter 2021 Assignment 1
 *  
 * POSIX Shared Memory Multi-Process Merge Sort
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
#include <sys/mman.h>
#include <fcntl.h>  

/* LEFT index and RIGHT index of the sub-array of ARR[] to be sorted */
void singleProcessMergeSort(int arr[], int left, int right) 
{
  if (left < right) {
    int middle = (left + right)/2;
    singleProcessMergeSort(arr, left, middle); 
    singleProcessMergeSort(arr, middle + 1, right); 
    merge(arr, left, middle, right); 
  } 
}

/* More or less a copy and paste from the usort version. Simply
   replaced the unix functions with POSIX ones, pretty much in 
   a one for one type fashion with the exception of ftruncate
   which deliberately declares the amount of size of the shared 
   array. Included a few more files to include the POSIX functions
   needed as well as the definitions for the arguments.
*/
void multiProcessMergeSort(int arr[], int left, int right){
char name[] = "bleep";
int middle = (left + right)/2;
if(left < right) {
	int shmid = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shmid,right + 1);
	int *sh_array = (int*) mmap(0, right + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shmid, 0 );
	for(int i = 0; i < right + 1; i++){
		sh_array[i] = arr[i];
 	}
	switch(fork()){
		case -1://there was an issue in creating the child process
			printf("Fork unsuccessful, exiting program.");
 			exit(EXIT_FAILURE);
			break;
		case 0://we're in the child process
			sh_array = (int*) mmap(0, right + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shmid, 0 );
 			singleProcessMergeSort(sh_array, left, middle);
 			close(shmid);
 			shm_unlink(name);
 			exit(EXIT_SUCCESS);//child process executed correctly
			break;
		default://we're in the parent process
			singleProcessMergeSort(sh_array, middle + 1, right); 
 			wait(NULL);
 			merge(sh_array, left, middle, right);
 			for(int i = 0; i < right + 1; i++){
 				arr[i] = sh_array[i];
 	    	}
 	    	close(shmid);
 			shm_unlink(name);
	}
  }
}
