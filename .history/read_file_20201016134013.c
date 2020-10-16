#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LINE_SIZE 250
#define LINE_NUMBER 3
#define ITEMS_LINE 2



double *read_from_file(const char *filename){
    
    FILE *file = fopen(filename,"r");
    
    long int size = 0;
    if(!file){
        fprintf(stderr, "Error: Could not open the file '%s'.\n",filename);
        exit(1);
    }

    int rows;
    int cols;
    char line[MAX_FILE_LINE_SIZE];
    char newLine[MAX_FILE_LINE_SIZE];

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
    rewind(file);
    double *matrix = malloc(rows*cols*sizeof(double)); /*We now have an array that is 12 double elements long*/
    while(fgets(newLine, MAX_FILE_LINE_SIZE, file)){
        if(newLine[0] != '#' || newLine[0] != 'm' || newLine[0] != 'e'){
            for(size_t i = 0; i < rows; ++i){
                for (size_t j = 0; j < cols; ++j){
                    fscanf(file, "%lg", &matrix[(cols*i)+j]);
                    fprintf(stdout, "%lg\n", matrix[(cols*i)+j]);
                } 
            }
        }
    }
    
    rewind(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);


    double *result = (double*) malloc(size);
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
    return matrix;

}

int main(int argc, char **argv){
    if(argc <2){
        fputs("Need input argument\n", stderr);
        return -1;
    }

    double *result = read_from_file(argv[1]);

    if(!result){
        return -1;
    }

    /*printf("%lf", result[0]);*/
    free(result);


    return 0;

}
