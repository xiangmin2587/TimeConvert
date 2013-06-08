#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//------------------------------------------------------------------------
// Convert POSIX time to z/OS time-of-day (TOD) clock format
//------------------------------------------------------------------------
// input:
//   GMT time from OSSTime or a timespec structure.
// output:
//   Input time in time-of-day (TOD) clock format.
//------------------------------------------------------------------------
int main(int argc, char ** argv)
{
	int i;
    for (i=0; i < argc; i++)
        printf("Argument %d is %s.\n", i, argv[i]);
	if(argc >= 4) {
		unsigned long long sectm;
		unsigned long long millitm;
		unsigned long long microtm;
		unsigned long long baseStck;
		unsigned long long microSecs;
		sscanf(argv[1], "%llu", &sectm);
		sscanf(argv[2], "%llu", &millitm);
		sscanf(argv[3], "%llu", &microtm);
		printf("sectm is %llu, millitm is %llu, microtm is %llu", sectm, millitm, microtm);


		// The z/OS time-of-day (TOD) clock is a 64 bit counter
		// that started Jan 1, 1900 and is incremented
		// by adding 1 to bit position 51 every microsecond.
		// The POSIX Epoch is Jan 1, 1970.
		// The TOD counter value for
		// Jan 1, 1970 is 0x7D91048BCA000000

		baseStck = 0x7D91048B;
		baseStck = baseStck << 32;
		baseStck  += 0xCA000000;
		microSecs = sectm;
		printf("The microSecs before add the baseStck is :%llu\n\n", microSecs);
		microSecs *= 1000000;
		printf("The microSecs before add the baseStck is :%llu\n\n", microSecs);
		microSecs += millitm * 1000;
		printf("The microSecs before add the baseStck is :%llu\n\n", microSecs);
		microSecs += microtm;
		printf("The microSecs before add the baseStck is :%llu\n\n", microSecs);
		// Shift the microseconds counter left 12 bits to align
		// its low order bit with the TOD microseconds bit.
		microSecs = microSecs << 12;
		if (microSecs)
		{
			microSecs += baseStck;
		}
		
		printf("After convert, the z/OS time-of-day (TOD) is: %llu \n\n", microSecs);
	} else {
		printf("Please input GMT time from OSSTime or a timespec structure you want to convert, when you run the test");
	}
	
	return 0;
}




