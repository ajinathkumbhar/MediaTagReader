// 10 byte
#pragma pack(1)
struct id3v2header {
	char id[3];
	char version[2];
	char flag;
        int size;
};

struct id3v2Frameheader {
	char id[4];
	char dataSize[4];
	char flag[2];
};

struct id3v2Frame {
	id3v2Frameheader * head;
	char * data;
};



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


int isID3V2Tag(FILE *IDfp);
int readID3V2TagHeader(FILE*, id3v2header*);
void printStatus(int status);
void readID3v2Frame(FILE *fp); 
int readID3v2FrameHeader(FILE *fAdd,id3v2Frameheader * frameHead);
char * readTag(FILE *fp);

