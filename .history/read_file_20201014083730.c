#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LINE_SIZE 250
#define LINE_NUMBER 3
#define ITEMS_LINE 3



char *read_from_file(const char *filename){
    
    FILE *file = fopen(filename,"r");
    
    long int size = 0;
    if(!file){
        fprintf(stderr, "Error: Could not open file '%s'.\n",filename);
        exit(1);
    }
    int rows;
    int cols;
    char line[MAX_FILE_LINE_SIZE];
    char matrixBuffer[MAX_FILE_LINE_SIZE];
    int LineNo = 0;

    while(LineNo < LINE_NUMBER && fgets(line, MAX_FILE_LINE_SIZE, file)){
        if(line[0]!='#'){
            int DimFound = sscanf(line, "%s %d %d", matrixBuffer, &rows, &cols);
            fprintf("%s", &line);
            if(DimFound == ITEMS_LINE){
                LineNo++;
            }else{
                fprintf(stderr, "Uknown format: %s\n", line);
            }
        }
    }
    printf("There are %c rows and %c colums\n", rows, cols);
    

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);


    char *result = (char*) malloc(size);
    if(!result){
        fputs("Memory Error\n", stderr);
        fclose(file);
        return NULL;
    }

    if(fread(result, 1, size, file) != size){
        fputs("Read Error\n", stderr);
        fclose(file);
        return NULL;
    }
    fclose(file);
    return result;

}

int main(int argc, char **argv){
    if(argc <2){
        fputs("Need input argument\n", stderr);
        return -1;
    }

    char *result = read_from_file(argv[1]);

    if(!result){
        return -1;
    }

    /*printf("%s", result);*/
    free(result);

    return 0;

}
