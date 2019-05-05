////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      sendsig.c, intdate.c
// Semester:         CS 354 Spring 2019
//
// Author:           Aksel Torgerson
// Email:            atorgerson@wisc.edu
// CS Login:         aksel
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
//
// Online sources:   None
//
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global var for number of division operations performed
int divNum = 0;

/* This is the handler method for SIGFPE. It prints an 
*  error message to the console, the number of succesful operations,
*  and then terminates the program gracefully.
*/
void handler_SIGFPE() {
    // print message to console
    printf("Error: a division by 0 operation was attempted.");
    printf("\nTotal number of operations completed successfully: %d\n", divNum);
    printf("The program will be terminated.\n");
    // exit gracefully
    exit(0);
}

/* This is the handler method for SIGINT. It prints the 
*  number of succesful operations, and then terminates 
*  the program gracefully.
*/
void handler_SIGINT() {
    printf("\nTotal number of operations successfully completed: %d\n", divNum);
    printf("The program will be terminated.\n");
    // exit gracefully
    exit(0);
}

/* Main method for division. Sets up the handlers and
*  binds them to the correct signals. Then takes input
*  from the user and performs the division.
*/
int main() {
    // set up and clear the sigaction structure for SIGFPE
    struct sigaction sigfpe;
    memset (&sigfpe, 0, sizeof(sigfpe));

    // set the sa_handler to the handle method above
    sigfpe.sa_handler = handler_SIGFPE;

    // bind the signal handler for SIGFPE
    if (sigaction(SIGFPE, &sigfpe, NULL) != 0) {
        // if the return values indicate a failure
        printf("Error binding to signal: SIGFPE\n");
        // return -1 to indicate failure
        return -1;
    }

    // set up and clear the sigaction structure for SIGINT
    struct sigaction sigint;
    memset (&sigint, 0, sizeof(sigint));

    // set the sa_handler to the handle method above
    sigint.sa_handler = handler_SIGINT;

    // bind the signal handler for SIGINT
    if (sigaction(SIGINT, &sigint, NULL) != 0) {
    // if the return values indicate a failure
        printf("Error binding to signal: SIGINT\n");
        // return -1 to indicate failure
        return -1;
    }

    // create buffer var with desired buffer size
    int BUFFER = 100;

    // create two char arrays of buffer length for input one and two
    char inputOne[BUFFER];
    char inputTwo[BUFFER];

    // declare variables to be used for input one and two
    int firstInt, secondInt;

    // delcare variables to be used for result and remainder
    int result, remainder;

    // use a loop to continually let the user create input
    while (1) {
        // prompt for first int
        printf("Enter first integer: ");

        // use fgets to get user input
        fgets(inputOne, BUFFER, stdin);

        // convert it from a string to integer
        firstInt = atoi(inputOne);

        // prompt for second int
        printf("Enter second integer: ");

        // use fgets to get user input
        fgets(inputTwo, BUFFER, stdin);

        // convert it from a string to integer
        secondInt = atoi(inputTwo);

        // integer division will return an integer
        result = firstInt / secondInt;

        // to get remainder use modulo operator
        remainder = firstInt % secondInt;

        // print results
        printf("%d / %d is %d with a remainder of %d\n", firstInt, secondInt,
            result, remainder);

        // increase number of division operations performed
        divNum++;
  }

  // program should never get here but return 0 for good measure
  return 0;
}

