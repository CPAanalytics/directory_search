#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#define LINELEN 512

FILE *fp;
DIR *dirptr;
struct dirent *direntptr;

int search_file(FILE *file, char *keyword);

int main(int argc, char *argv[]) {
	if (argc!=4){
		printf("incorrect command structure provided");
		return 0;
	}
	char *extension = argv[1];
	char *directory = argv[2];
	char *keyword = argv[3];
	int linenum;

	dirptr = opendir(directory);
	if (dirptr==NULL){
		printf("directory not found");
	}
	while((direntptr=readdir(dirptr))!=NULL){
		char directorycpy[100];
		strcpy(directorycpy,directory);
		if(strstr(direntptr->d_name,extension)!=NULL){
			strcat(directorycpy,direntptr->d_name);
			if((fp = fopen(directorycpy,"r"))==NULL){
				printf("could not open file");
			}
			if ((linenum = search_file(fp,keyword))!=0){
				printf("keyword found linenum %d in %s",linenum,directorycpy);
			}
		}
	}

return 0;
}

int search_file(FILE *file, char *keyword){
	int linenum = 1;
	char line[LINELEN];
	while(fgets(line,LINELEN,file)!=NULL){
		if(strstr(line,keyword)!=NULL){
			return linenum;
		}
		linenum++;
	}
	return 0;
}
