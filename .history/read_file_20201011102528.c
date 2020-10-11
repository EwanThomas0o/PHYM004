#include<stdio.h>
#include<stdlib.h>

#define MAX_FILE_LINE_SIZE 250



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

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    while(fgets(line, sizeof(line), file)){
        if(line[0]='m'){
            sscanf(line, "%*s, %i, %i", &rows, &cols);
        }
        printf("There are %i rows and %i cols", rows, cols);
    }
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

    printf("%s", result);
    free(result);

    return 0;

}
