/* Title: Direct Matrix Calculations
Author: Ewan-James Thomas
Address: 35 Monkswell Road EX4 7AU
License: Public Domain
*/

static const char * VERSION = "0.2.0";
static const char * REV_DATE = "17-October-2020";

/*
 Date         Version  Comments
 ----         -------  --------
09-Oct-2020     0.0.1  Build start -> taking input from command line.
10-Oct-2020     0.0.2  Added "getopt" functionality, Trying to get_matrix...
11-Oct-2020     0.0.3  Continued work on get_matrix function
14-Oct-2020     0.0.4  Contintues work on get_matrix function
16-Oct-2020     0.1.0  Code can now read in matrix and produce the frobenius norm
17-Oct-2020     0.2.0  Code can now display transpose of matrix to stdout
18-Oct-2020     0.2.1  Work started in implementing product function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

#define MAX_FILE_LINE_SIZE 250
#define LINE_NUMBER 3
#define ITEMS_LINE 2
#define MAX_FILES 2

typedef struct
{   
    int rows;
    int cols;
    double *data;
} Matrix;
    

Matrix *read_from_file(const char *filename){
    
    char line[MAX_FILE_LINE_SIZE];
    char newLine[MAX_FILE_LINE_SIZE];
    
    FILE *file = fopen(filename,"r");
    
    if(!file){
        fprintf(stderr, "Error: Could not open the file '%s'.\n",filename);
        exit(1);
    }

    Matrix *m = (Matrix *) malloc(sizeof(Matrix));

     /* We will use rows and cols to malloc a matrix*/ 
    while(fgets(line, MAX_FILE_LINE_SIZE, file)){
        if(line[0]=='m'){
            int DimFound = sscanf(line, "%*s %d %d", &m->rows, &m->cols);
            if(DimFound != ITEMS_LINE){
                fprintf(stderr, "Unknown format: %s\n", line);
                break;
            }
        }
    }
    rewind(file);
    
    m->data = (double *) malloc(m->rows*m->cols*sizeof(double));

    if(!m){
        fprintf(stderr, "Memory Error\n");
        fclose(file);
        return NULL;
    }

    /*Skipping commented lines, we'll now assign values to the matrix which is maped onto an array*/
    while(fgets(newLine, MAX_FILE_LINE_SIZE, file)){
        if(newLine[0] != '#' && newLine[0] != 'e'){
            for(size_t i = 0; i < m->rows; ++i){
                for (size_t j = 0; j < m->cols; ++j){
                    fscanf(file, "%lg", &m->data[(m->cols*i)+j]);
                    /*printf("%lg\n", m->data[(m->cols*i)+j]);*/
                } 
            }
        }
    }

    fclose(file);
    return m;

}

double frobenius_norm(Matrix *matrix){
    double sum = 0;
    for(int i = 0; i<matrix->cols; i++){
        for(int j = 0; j < matrix->rows; j++){
            sum += pow(matrix->data[matrix->cols*i + j], 2);
        }
    }
    return sqrt(sum);
}

void transpose(Matrix *matrix){
    for(int i = 0; i < matrix->cols; i++){
        for(int j = 0; j < matrix->rows; j++){
            printf("%lg\t", matrix->data[matrix->cols*j+i]);
        }
        printf("\n");
    }


}

int main(int argc, char **argv){
    
    Matrix *mats[MAX_FILES];
    
        if(argc == 3){
            mats[0] = read_from_file(argv[argc-1]);
        }

        if(argc == 4){
            mats[0] = read_from_file(argv[argc-1]);
            mats[1] = read_from_file(argv[argc-2]);

        }
    
    int option;

        /* Checks for flags */
    while ((option = getopt(argc, argv, "ftmdai")) != -1){
        switch(option){
            case 'f' :
                printf("You want the frobenius norm: %lg\n", frobenius_norm(mats[0]));
                break;
            case 't' :
                printf("You want the transpose\n");
                transpose(mats[0]);
                break;
            case 'm' :
                printf("You want to multiply the two matricies\n");
                for(int i = 0; i < mats[0]->cols; i++){
                    for(int j = 0; j < mats[0]->rows; j++){
                        printf("%lg\t", mats[0]->data[mats[0]->cols*i+j]);
                    }
                    printf("\n");
                }
                printf("\nand\n");
                
                for(int i = 0; i < mats[1]->cols; i++){
                    for(int j = 0; j < mats[1]->rows; j++){
                        printf("%lg\t", mats[1]->data[mats[1]->cols*i+j]);
                    }
                    printf("\n");
                }


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

    return 0;

}
