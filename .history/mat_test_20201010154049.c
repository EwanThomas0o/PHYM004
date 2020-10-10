/* Title: Direct Matrix Calculations
Author: Ewan-James Thomas
Address: 35 Monkswell Road EX4 7AU
License: Public Domain
*/

static const char * VERSION = "0.0.1";
static const char * REV_DATE = "9-October-2020";

/*
 Date         Version  Comments
 ----         -------  --------
09-Oct-2020     0.0.1  Build start -> taking input from command line
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h> /* For command line input */


int main(int argc, char **argv){
    int option;
    
    while ((option = getopt(argc, argv, "ftmdai")) != -1){
        /* code */
        switch(option){
            case 'f' :
                printf("You want the frobenius norm\n");
                break;
            case 't' :
                printf("You want the transpose\n");
                break;
            case 'm' :
                printf("You want to multiply two matricies\n");
                break;
            case 'd' :
                printf("You want the Determinant\n");
                break;
            case 'a' :
                printf("You want the adjoint\n");
                break;
            case 'i' :
                printf("You want the inverse\n");
                break;
                
            default:
                printf("Error, please choose a valid input\n");
        }

    }
    
}
