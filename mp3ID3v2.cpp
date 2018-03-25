/*
ID3v2/file identifier   "ID3"
ID3v2 version           $03 00
ID3v2 flags             %abc00000
ID3v2 size              4 * %0xxxxxxx

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isID3V2Tag(FILE *IDfp);
int readID3V2TagHeader(FILE*, char*);
char * readTag(FILE *fp);

struct id3v2header {
char id[3];
char version[2];
char flag;
int size;
};



int main () {
   FILE *fp;
   int c,i,byteCount;
   i=1;
   byteCount=3;
   int status = -1;
  
   fp = fopen("testContent/testsample.mp3","r");
    
   if ( fp == NULL ) {
	printf("File not found or file open error\n");
        return -1;
   }

   // check id3v2 compataible
   status = isID3V2Tag(fp);
   if (status == -1) {
	printf("ID3v2 incompataible tag .... try with another mp3 file\n"); 
	return -1; 
   } 

   printf("ID3v2 Tag Found !!! \n");
	
   
   printf("\n");
   fclose(fp);
   
   return(0);
}


/********************************
* func : isID3V2Tag(FILE *IDfp)
* param: IDfp - file pointer
* return: 0 if not id3v2 else return 1 for ID3v2
*********************************/
int isID3V2Tag(FILE *IDfp) {
	int headerSize=10;
	char * ptrId3v2Header = NULL;
	ptrId3v2Header = (char *)malloc(headerSize);
	int ret = -1;
	if ( ptrId3v2Header == NULL ) {
		printf("failed to allocate memory for ptrId3v2Header\n");
		return ret;
	}

	ret = readID3V2TagHeader(IDfp,ptrId3v2Header);
	if (ret == -1) {
		printf("readID3V2TagHeader failed\n");
		return ret;	
	}
	
	printf("content of ptrId3v2Header : \n");
	printf("%s\n",ptrId3v2Header);  
	
	if (strncmp(ptrId3v2Header,"ID3",3) == 0) {
		printf("id3 check done \n");
		ret = 0;
        } else 
		ret = -1;
	
return ret;	
}


/********************************
* func : readID3V2TagHeader(FILE *IDfp)
* param: IDfp - file pointer
* return: char * - pointer to Header
*********************************/
int readID3V2TagHeader(FILE *fp,char * buf) {

int headerSize=10;
int i = 0;

	if ( buf == NULL ) {
		printf("buffer add null\n");
		return -1;
	}


	while(i < headerSize) {
		buf[i] = fgetc(fp);
		if( feof(fp) ) { 
		break ;
		}
		//printf("%c", c);
		i++;
	}

return 0;

}



