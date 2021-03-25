/*********************************************************************
 *
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ***********************************************************************/

#include "fileman.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


/*
 * You need to implement this function, see fileman.h for details 
 */
int fileman_read(char* fname, size_t foffset, char* buf, size_t boffset, size_t size){
	int desc = open(fname, O_RDONLY);
	switch(desc){
		case -1://if the file doesn't exist just exit. nothing to read
			return -1;
			break;

		default://if it does exist go to foffset and read from buf starting at boffset
			lseek(desc, foffset, SEEK_CUR);
			int numBytes = read(desc, boffset + buf, size);
			close(desc);
			return numBytes;
	}
}

/*
 * You need to implement this function, see fileman.h for details 
 */
int fileman_write(char* fname, size_t foffset, char* buf, size_t boffset, size_t size){
	int desc = open(fname, O_RDWR);//need to check if the file already exists since 
	switch(desc){
		case -1://case for if it doesn't exist. go through with creation and writing
			creat(fname, S_IRWXU);
			int descr = open(fname, O_WRONLY);
			lseek(descr, foffset, SEEK_CUR);
			int numBytes = write(descr, boffset + buf, size);
			close(descr);
			return numBytes;
			break;

		default://case for if it does exist. just close it and return an error
			close(desc);
			return -1;

	}
}

/*
 * You need to implement this function, see fileman.h for details 
 */
int fileman_append(char* fname, char* buf, size_t size){
	int desc = open(fname, O_RDWR | O_APPEND);
	switch(desc){
		case -1:
			return -1;
			break;

		default:;
			int numBytes = write(desc, buf, size);
			close(desc);
			return numBytes;

	}
}

/*
 * You need to implement this function, see fileman.h for details 
 */
int fileman_copy(char* fsrc, char* fdest){
	int descSrc = open(fsrc, O_RDWR);
	int descDest = open(fdest, O_RDWR);
	if(descSrc == -1) {//if there is no source just return an error
		return -1;
	}
	else{
		switch(descDest){//since there is a source now check if destination address is already taken
			case -1:
				creat(fdest, S_IRWXU);//create the destination
				int desc = open(fdest, O_RDWR);
				char* buf = malloc(500000);
				int numBytesRead = read(descSrc, buf, 500000);
				close(descSrc);

				int numBytesCopied = write(desc, buf, numBytesRead);
				free(buf);
				close(desc);
				return numBytesCopied;
				break;

			default://if it is taken just close it and return an error
				close(descDest);
				return -1;

		}
	}

}


void get_dir(int fd, char* dname, int indent){

}

/*
 * You need to implement this function, see fileman.h for details 
 */
void fileman_dir(int fd, char* dname){

	//get_dir(fd, dname, 0);
}




/*
 * You need to implement this function, see fileman.h for details 
 */
void fileman_tree(int fd, char* dname){




}

