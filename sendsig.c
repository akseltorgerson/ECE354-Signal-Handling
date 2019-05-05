////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      intdate.c, division.c
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
#include <sys/types.h>

/* This program allows you to send either a SIGUSR1 or
*  SIGINT signal to another program given the PID.
*/
int main(int argNum, char *argValue[]) {
    // if there are incorrect number of arguments print a usage message
        if (argNum != 3) {
        printf("Usage: <signal type> <pid>\n");
        return -1;
    }

    // if the signal type flag is not proper length
    if (strlen(argValue[1]) != 2) {
        // print a usage message and return -1
        printf("Usage: <signal type> <pid>\n");
        return -1;
    }

    // get the PID from the command line arguments
    int pid = atoi(argValue[2]);
    // get the signal type desired from the command line args
    char sig = argValue[1][1];

    // if the signal is an interrupt
    if (sig == 'i') {
        // kill the process using that signal and get the return value
        int success = kill(pid, SIGINT);

        // if the return value isn't 0
        if (success) {
            // print an error message to the console
            printf("ERROR sending signal: SIGINT\n");
        }
    // if the signal desired is a user signal
    } else if (sig == 'u') {
        // kill the process usuing that signal and get the return value
        int success = kill(pid, SIGUSR1);

        // if the return value isn't 0
        if (success) {
            // print an error message to the console
            printf("ERROR sending signal: SIGUSR1\n");
        }
    // if the signal flag is not one of the two above
    } else {
        // print a usage message and return -1
        printf("Usage: <signal type> <pid>\n");
        return -1;
    }

    // return 0 if everything functions correctly
    return 0;
}
