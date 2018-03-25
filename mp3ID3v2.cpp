

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct id3v2header {
char id[3];
char version[2];
char flag;
int size;
};


int isID3V2Tag(FILE *IDfp);
int readID3V2TagHeader(FILE*, id3v2header*);
char * readTag(FILE *fp);



// Error Code
enum id3v2_error_code {
ID3V2_STATUS_FAIL=-1,
ID3V2_STATUS_SUCCESS,
ID3V2_STATUS_FILE_NOT_FOUND,
ID3V2_STATUS_INVALID_TAG,
ID3V2_STATUS_ID3_TAG_FOUND,
ID3V2_STATUS_MALLOC_ERROR,
ID3V2_STATUS_READ_HEADER_FAILED,
ID3V2_STATUS_EOF_ERROR,
ID3V2_STATUS_UNKNOWN,
};


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



