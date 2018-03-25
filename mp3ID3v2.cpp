/*
ID3v2/file identifier   "ID3"
ID3v2 version           $03 00
ID3v2 flags             %abc00000
ID3v2 size              4 * %0xxxxxxx

*/

#include <stdio.h>

int main () {
   FILE *fp;
   int c,i,byteCount;
   i=1;
   byteCount=3;
  
   fp = fopen("testContent/testsample.mp3","r");
    
   if ( fp == NULL ) {
	printf("File not found or file open error\n");
        return -1;
   }
   while(i <= byteCount) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         break ;
      }
      printf("%c", c);
      i++;
   }
   printf("\n");
   fclose(fp);
   
   return(0);
}

