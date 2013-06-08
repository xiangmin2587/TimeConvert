#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//------------------------------------------------------------------------
// Convert z/OS time-of-day (TOD) clock format to POSIX time format
//------------------------------------------------------------------------
// input:
//   time-of-day (TOD) clock format.
// output:
//   GMT time from OSSTime or a timespec structure.
//   The z/OS time-of-day (TOD) clock is a 64 bit counter
//   that started Jan 1, 1900 and is incremented
//   by adding 1 to bit position 51 every microsecond.
//   The POSIX Epoch is Jan 1, 1970.
//   The TOD counter value for
//   Jan 1, 1970 is 0x7D91048BCA000000
int main(int argc, char ** argv)
{
	int i;
    for (i=0; i < argc; i++)
        printf("Argument %d is %s.\n", i, argv[i]);
	if(argc >= 2) {
		unsigned long long microSecs = 0;
		sscanf(argv[1], "%llu", &microSecs);
		printf("The input microSecs is :%llu\n\n", microSecs);
		unsigned long long baseStck = 0x7D91048B;
		baseStck = baseStck << 32;
		baseStck  += 0xCA000000;
		
		microSecs = microSecs - baseStck;
		
		microSecs = microSecs >> 12;
		
		printf("The microSecs after minus the baseStck is :%llu\n\n", microSecs);
		unsigned long long sectm = microSecs / 1000000;
		unsigned long long microtm = (microSecs %1000000);

		time_t day = (time_t)sectm;
		printf("After convert, the POSIX time format is:%llu %llu %llu\n\n", sectm, microtm/1000, microtm%1000);
		printf("After convert, the time format is:%s %llu \n\n", ctime(&day), microtm);
	} else {
		printf("Please input z/OS time-of-day (TOD) clock format you want to format as main parameters, when you run the test");
	}
	
	return 0;
}




