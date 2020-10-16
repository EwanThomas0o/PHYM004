#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char **argv){
    if(argc <2){
        fputs("Need input argument\n", stderr);
        return -1;
    }

    Matrix *matrix = read_from_file(argv[1]);
    if(!matrix){
        return -1;
    }

    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            printf("%lg\n", matrix->data[(matrix->cols*i)+j]);
        }
    }
    free(matrix);


    return 0;

}
