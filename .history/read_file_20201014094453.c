#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LINE_SIZE 250
#define LINE_NUMBER 3
#define ITEMS_LINE 2



char *read_from_file(const char *filename){
    
    FILE *file = fopen(filename,"r");
    
    long int size = 0;
    
    if(!file){
        fprintf(stderr, "Error: the file '%s' could not be opened.\n",filename);
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


    char *text = (char*) malloc(size);
    if(!text){
        fprintf(stderr, "Memory Error\n");
        fclose(file);
        return NULL;
    }

    if(fread(text, 1, size, file) != size){
        fprintf(stderr, "Read Error\n");
        fclose(file);
        return NULL;
    }
    fclose(file);
    return text;

}

int main(int argc, char **argv){
    if(argc <2){
        fputs("Need input argument\n", stderr);
        return -1;
    }

    char *matrix = read_from_file(argv[1]);

    if(!text){
        return -1;
    }

    /*printf("%s", text);*/
    free(text);

    return 0;

}
