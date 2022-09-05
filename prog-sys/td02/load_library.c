#include "load_library.h"

void (*function)(int [], int);
void* plib;

void load_library(char *library_name){
    plib = dlopen(library_name,RTLD_LAZY);

	if(plib != NULL){
        dlerror();
        function = dlsym(plib, "sort");
    }
    
    else{
        printf("la librairie %s n'a pas ouvert!\n", library_name);
        exit(1);
    }

}

void sort(int t[], int size){
    function(t, size);
    dlclose(plib);
}