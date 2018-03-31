#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3ID3v2.h"

#define ID3V2_HEADER_IN_BYTES 10

/****************

  4.2.1 TIT2 Title/songname/content description
  4.2.2 TPE1 Lead performer(s)/Soloist(s)
  4.2.1 TALB Album/Movie/Show title
  4.2.2 TCOM Composer
  4.2.3 TCON Content type




Frame ID       $xx xx xx xx (four characters)
Size           $xx xx xx xx
Flags          $xx xx
endchar   null + size


" --------------- size -------------"
*/







/********************************
* func : int readID3v2Frame(FILE *fp) 
*
*********************************/
int readID3v2Frame(FILE *fp) {
	int NextFrame = ID3V2_HEADER_IN_BYTES;
	//int Nextdata;
	int count=0;
	char id[4];
	int readByte;
	//char d[100];
	//char e[100];
	id3v2Frame * frameTitle;

	frameTitle = (id3v2Frame *) malloc(sizeof(id3v2Frame));
	frameTitle->head = (id3v2Frameheader *)malloc(sizeof(id3v2Frameheader));
    frameTitle->data = (char *) malloc(sizeof(100));

	//skip 10 byte of mp3ID3v2 tag header
	fseek(fp, NextFrame, SEEK_SET);
	readID3v2FrameHeader(fp,frameTitle->head);
    
	// print 1st frame header
    snprintf(id, 5, "%s", frameTitle->head->id);
	printf("Frame Tag  : %s\n",id);
	printf("sizeHex    : %02x %02x %02x %02x\n",frameTitle->head->dataSize[0],frameTitle->head->dataSize[1],frameTitle->head->dataSize[2],frameTitle->head->dataSize[3]);
	printf("sizeInt    : %d\n",frameTitle->head->dataSize[3]);
	printf("flag       : %02x %02x \n",frameTitle->head->flag[0],frameTitle->head->flag[1]);
	
	fseek(fp,20, SEEK_SET);
	readByte = fread(frameTitle->data, sizeof(char),frameTitle->head->dataSize[3], fp);
    
	printf("data       : ");
	for(count=0;count <=42 ; count++) 
		printf("%c",frameTitle->data[count]);
	printf("\n");

}

/********************************
* func : int readID3v2FrameHeader(char *fAdd,id3v2Frameheader * frameHead);
*
*********************************/
int readID3v2FrameHeader(FILE *fAdd,id3v2Frameheader * frameHead) {
 	int readByte;

	readByte = fread(frameHead, sizeof(frameHead), 1, fAdd);
return 1;
}





/********************************
* func : int main(int argc,char* argv[])
*
*********************************/
int main(int argc,char* argv[])
{
   FILE *fp;
   int status = ID3V2_STATUS_UNKNOWN;
  
   if(argc !=2 ) {
	printf("Usage:\n");
	printf("\t%s file.mp3\n",argv[0]);
	return ID3V2_STATUS_FAIL;
   }
      
   fp = fopen(argv[1],"r");
   if ( fp == NULL ) {
        status = ID3V2_STATUS_FILE_NOT_FOUND;
   }

   // check id3v2 compataible
   if (status == ID3V2_STATUS_UNKNOWN) {
	   status = isID3V2Tag(fp);
   }

	printStatus(status);

	if (status == ID3V2_STATUS_ID3_TAG_FOUND) {
		readID3v2Frame(fp);
	

	}


   printf("\n");
   
   if (status != ID3V2_STATUS_FILE_NOT_FOUND )
	   fclose(fp);
   
   return(0);
}

/********************************
* func : isID3V2Tag(FILE *IDfp)
* param: IDfp - file pointer
* return: 0 if not id3v2 else return 1 for ID3v2
*********************************/
int isID3V2Tag(FILE *IDfp) {
	int ret;
	char id[3];

	id3v2header * ptrId3v2Header = NULL;
	ptrId3v2Header = (id3v2header *)malloc(sizeof(id3v2header));
	if ( ptrId3v2Header == NULL )
		return ID3V2_STATUS_MALLOC_ERROR;

	ret = readID3V2TagHeader(IDfp,ptrId3v2Header);
	if (ret != ID3V2_STATUS_SUCCESS) {
		return ID3V2_STATUS_READ_HEADER_FAILED;	
	}
	
 	if (strncmp(ptrId3v2Header->id,"ID3",3) == 0) {
		snprintf (id, 4, "%s", ptrId3v2Header->id );
		printf("\n----------------------------\n");
		printf("id      : %s\n",id);
		printf("version : %02x %02x\n",ptrId3v2Header->version[0], ptrId3v2Header->version[1]);
		printf("flag    : %c\n",ptrId3v2Header->flag);
		printf("size    : %d\n",ptrId3v2Header->size);
		printf("----------------------------\n\n");

		ret = ID3V2_STATUS_ID3_TAG_FOUND;
        } else 
		ret = ID3V2_STATUS_INVALID_TAG;
	
return ret;	
}


/********************************
* func : readID3V2TagHeader(FILE *fp,id3v2header * buf)
* param: IDfp - file pointer
* return: char * - pointer to Header

ID3v2/file identifier   "ID3"
ID3v2 version           $03 00
ID3v2 flags             %abc00000
ID3v2 size              4 * %0xxxxxxx


*********************************/
int readID3V2TagHeader(FILE *fp,id3v2header * buf) {

	int readBytes=0;
	readBytes = fread(buf, sizeof(id3v2header), 1, fp);
	return readBytes ? ID3V2_STATUS_SUCCESS : ID3V2_STATUS_READ_HEADER_FAILED; 

}


/********************************
* func : void printStatus(int status);
* param: status - type enum id3v2_error_code
* return: void
*********************************/

void printStatus(int status) {
	switch(status) {
		case ID3V2_STATUS_FAIL:
			printf("Failed to read id3v2 tag\n");
			 	break;
		case ID3V2_STATUS_SUCCESS:
			printf("ID3V2 tag read success\n");
			 	break;
		case ID3V2_STATUS_FILE_NOT_FOUND:
			printf("mp3 file not found\n");
			 	break;
		case ID3V2_STATUS_INVALID_TAG:
			printf("Invalid tag\n");
			 	break;
		case ID3V2_STATUS_ID3_TAG_FOUND:
			printf("ID3V2 tag found\n");
			 	break;
		case ID3V2_STATUS_MALLOC_ERROR:
			printf("Memroy allocation failed\n");
			 	break;
		case ID3V2_STATUS_READ_HEADER_FAILED:
			printf("failed to read ID3v2 header\n");
			 	break;
		case ID3V2_STATUS_EOF_ERROR:
			printf("Failed to read id3v2 tag\n");
			 	break;
		default:
			printf("Unknown error");
	}

}

