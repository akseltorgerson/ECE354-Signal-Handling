////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      sendsig.c, division.c
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>

// create global variables for time length and number of SIGUSR1 signals
int timer = 3;
int numOfSIGUSR1 = 0;

/* This is the handler for SIGALRM. This handler gets the current system
*  date and time and then prints it as well as the PID. It then sets 
*  another alarm for 3 seconds.
*/
void handler_SIGALRM() {
    // declare a variable for current time
    time_t currTime;
    time(&currTime);

    // get the PID
    int pid = getpid();

    // print it out to console
    printf("PID: %d | Current Time: %s", pid, ctime(&currTime));

    // set another alarm
    alarm(timer);
}

/* This is the handler for SIGUSR1. When it recieves a user signal
*  it prints a messasge, and increases the total value of signals
*  sent by the user.
*/
void handler_SIGUSR1() {
    // prints a message to console
    printf("SIGUSR1 caught!\n");

    // inc the total count of user signals
    numOfSIGUSR1++;
}

/* This is the handler for SIGINT. When an interrupt signal is recieved
*  a message will be printed to console, and it will print the number
*  of user signals recieved through the duration of the program. Then the
*  program will terminate gracefully.
*/
void handler_SIGINT() {
    // print a message to console
    printf("\nSIGINT received.\n");
    printf("SIGUSR1 was recieved %d times. Exiting now.\n", numOfSIGUSR1);

    // exit gracefully
    exit(0);
}

int main() {
    // create a new sigaction and clear it to 0
    struct sigaction sigalrm;
    memset (&sigalrm, 0, sizeof(sigalrm));

    // update the sa_handler to handler created above
    sigalrm.sa_handler = handler_SIGALRM;

    // bind the signal SIGALRM to our handler
    if (sigaction(SIGALRM, &sigalrm, NULL) != 0) {
        printf("Error binding to signal: SIGALRM\n");
        return -1;
    }

    // create a new sigaction and clear it to 0
    struct sigaction sigusr1;
    memset (&sigusr1, 0, sizeof(sigusr1));

    // update the sa_handler to the handler created above
    sigusr1.sa_handler = handler_SIGUSR1;

    // bind the signal SIGUSR1 to our handler
    if (sigaction(SIGUSR1, &sigusr1, NULL) != 0) {
        printf("Error binding to signal: SIGUSR1.\n");
        return -1;
    }

    // create a new sigaction and clear it to 0
    struct sigaction sigint;
    memset (&sigint, 0, sizeof(sigint));

    // update the sa_handler to the handler created above
    sigint.sa_handler = handler_SIGINT;

    // bind the signal SIGINT to our handler
    if (sigaction(SIGINT, &sigint, NULL) != 0) {
            printf("Error binding to signal: SIGINT.\n");
            return -1;
    }

    // print message to console
    printf("Pid and time will be printed every 3 seconds.\n");
    printf("Enter ^C to end the program.\n");

    // set an initial alarm
    alarm(timer);

    // create an infinite loop
    while (1) {}

    // although the program should never get here, return 0 for good measure
    return 0;
}
