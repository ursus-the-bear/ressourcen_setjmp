#include <msp430.h> 
#include <stdio.h>

// what info am I keeping per thread
typedef struct _thread {
	void (*funcPtr)();
} thread_t;

char output [10];
unsigned int outputPos;

// one function
void function1 () {
	output [outputPos++] = '1';
}
// one function
void function2 () {
	output [outputPos++] = '2';
}
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // variable you use to test
    unsigned int i;

    // array to hold the functions
    thread_t threadList [10];
    for (i = 0; i < 10; i++)
    	if ((i % 2) == 0)
    		threadList [i].funcPtr = &function2;
    	else
    		threadList [i].funcPtr = &function1;

    // clear the output array
    for (i = 0; i < 10; i++)
    	output [i] = ' ';
    outputPos = 0;

    // this fills output with 1 / 2
    for (i = 0; i < 5; i++) {
    	function1();
    	function2();
    }

    // clear the array again
    for (i = 0; i < 10; i++)
    	output [i] = ' ';
    outputPos = 0;

    // now fill the array with pointers
    for (i = 0; i < 10; i++)
    	threadList [i].funcPtr();


	return 0;
}
