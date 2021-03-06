/* Title: Direct Matrix Calculations
Author: Ewan-James Thomas
Address: 35 Monkswell Road EX4 7AU
License: Public Domain
*/

static const char * VERSION = "0.0.3";
static const char * REV_DATE = "11-October-2020";

/*
 Date         Version  Comments
 ----         -------  --------
09-Oct-2020     0.0.1  Build start -> taking input from command line.
10-Oct-2020     0.0.2  Added "getopt" functionality, Trying to get_matrix...
11-Oct-2020     0.0.3  Continued work on get_matrix function
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h> /* For command line input */


double** get_matrix(const char *filename);

int main(int argc, char **argv){
    int option;
    
    /* Checks for flags */
    while ((option = getopt(argc, argv, "ftmdai")) != -1){
        /* code */
        switch(option){
            case 'f' :
                printf("You want the frobenius norm\n");
                /* For each case we will call a function that does what the user specifies */
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
                printf("Error: Options '-%c' is not a valid input\n", optopt);
        }
    }
}

double** get_matrix(const char *filename){
    double **array;

    FILE * pToFile;
    pToFile = fopen(filename, "r");
    
    if (!pToFile)
    {
        printf("Error opening file\n");
        exit(1);
    }
    

    
}
