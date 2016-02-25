//Jasmine Emerson
//CS 360
//Assignment 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define buffer 16

int ok (int fd, char *word){
	char* want = word;
	for(int i = strlen(want); i < 15; i++){ //pad want so it contain spaces
		want[i] = ' ';
	}
	want[15]= '\0'; 
	char have[buffer];
	int bot = 0;
	int mid = 0;
	int top = lseek(fd, 0, SEEK_END)/16; ///set top to last line number + 1
	while(bot < top){
		mid =(bot+top)/2;
		lseek(fd, mid*16, SEEK_SET);
		read(fd, have, 16);
		have[15]= '\0';
		int cmp = strcmp(want, have);
		if(cmp == 0){ //strings are equal
			return 1;
		} 
		else if(cmp<0){
			top=mid;
		}
		else {
			bot=mid+1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	int fd = open("webster", O_RDONLY);
	if (fd) {
		char *word = argv[1];
		if (ok(fd, word) == 1){
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	} else {
		fprintf(stderr,"Can't open dictionary.\n");
		exit(1);
	}
}
