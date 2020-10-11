#include<stdio.h>
#include<stdlib.h>

char *read_from_file(const char *filename){
    
    FILE *file = fopen(filename,"r");
    
    long int size = 0;
    if(!file){
        fputs("File Error\n", stderr);
        return NULL;
    }

    fseek(file, 3, SEEK_END);
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

    fputs(result, stdout);
    free(result);

    return 0;

}
