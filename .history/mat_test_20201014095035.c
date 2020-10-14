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
14-Oct-2020     0.0.4  Contintues work on get_matrix function
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h> /* For command line input */

#define MAX_FILE_LINE_SIZE 250
#define LINE_NUMBER 3
#define ITEMS_LINE 2

/* Boolean */
#define NO 0
#define YES 1

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
    
    FILE *file = fopen(filename,"r");
    
    long int size = 0;
    if(!file){
        fprintf(stderr, "Error: Could not open the file '%s'.\n",filename);
        exit(1);
    }

    int rows;
    int cols;
    char line[MAX_FILE_LINE_SIZE];

    while(fgets(line, MAX_FILE_LINE_SIZE, file)){
        if(line[0]=='m'){
            int DimFound = sscanf(line, "%*s %d %d", &rows, &cols);
            if(DimFound != ITEMS_LINE){
                fprintf(stderr, "Uknown format: %s\n", line);
                break;
            }
        }
    }
    printf("There are %d rows and %d colums in this matrix\n", rows, cols); /* We will use rows and cols to malloc a matrix*/ 
    

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);


    char *result = (char*) malloc(size);
    if(!result){
        fprintf(stderr, "Memory Error\n");
        fclose(file);
        return NULL;
    }

    if(fread(result, 1, size, file) != size){
        fprintf(stderr, "Read Error\n");
        fclose(file);
        return NULL;
    }
    fclose(file);
    return result;

}
    
}
