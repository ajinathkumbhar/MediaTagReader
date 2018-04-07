#include<stdio.h>
#include<stdint.h>
#include <math.h>

main() {

char buf[32];
int num;
int shifter=0;
int test;
int result=0;
printf("Enter 1 byte num i.e. < 256  : ");
scanf("%d",&num);
printf("%x %d %c\n",num,num,num);

for (shifter=0; shifter<=31;shifter++) {
	if ( shifter ==7 || shifter ==15 || 
 	     shifter ==23 || shifter ==31) {
		//printf(" shifter=%d found 8 series bit. so skip ... \n",shifter);
		buf[shifter]='x';
		continue;	
	}
	
	if ( num & 1 << shifter) {
		//printf(" %d bit set found\n",shifter);
		buf[shifter]='1';
		result += pow(2,shifter);
		printf(" %d -- pow(2,%d):%d  result: %d\n",shifter,shifter,(int)pow(2,shifter),result);
	} else { 
		//printf(" %d bit not set found\n",shifter);
		buf[shifter]='0';
	}

}
test=31;
while (test >= 0) {
     printf("%c",buf[test]);
     test--;
	if ( test == 7 || test ==15 || 
 	     test == 23 || test ==31) 
		printf(" ");
}
printf("  --- : %d\n",result);
}
