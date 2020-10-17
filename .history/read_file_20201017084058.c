#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

#define MAX_FILE_LINE_SIZE 250
#define LINE_NUMBER 3
#define ITEMS_LINE 2

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
    
    long int size = 0;
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
                fprintf(stderr, "Uknown format: %s\n", line);
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

int main(int argc, char **argv){
    
        if(argc < 3){
        fputs("Need input argument\n", stderr);
        return -1;
    }
    
    int option;

    Matrix *matrix = read_from_file(argv[2]);
    if(!matrix){
        return -1;
    }
        /* Checks for flags */
    while ((option = getopt(argc, argv, "ftmdai")) != -1){
        switch(option){
            case 'f' :
                printf("You want the frobenius norm: %lg\n", frobenius_norm(matrix));
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
    free(matrix);


    return 0;

}
