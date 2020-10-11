#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LINE_SIZE 250



char *read_from_file(const char *filename){
    
    FILE *file = fopen(filename,"r");
    
    long int size = 0;
    if(!file){
        fprintf(stderr, "Error: Could not open file '%s'.\n",filename);
        exit(1);
    }

    unsigned int rows = 0;
    unsigned int cols = 0;
    char line[MAX_FILE_LINE_SIZE];

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

    while(fgets(line, MAX_FILE_LINE_SIZE, file)){
        if(line[0]=='m'){
            sscanf(line, "%*[^ ] %u %u", &rows, &cols);
        }
    }
    printf("There are %u rows and %u cols\n", rows, cols);

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

    printf("%s", result);
    free(result);

    return 0;

}
