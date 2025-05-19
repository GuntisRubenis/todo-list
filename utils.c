#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void check_malloc(void * p){
	if (p == NULL){
		fprintf(stderr, "Error allocating memorry\n");
		exit(EXIT_FAILURE);
	}
}

void remove_newline(char *str){
	for (int i = 0;;i++){
		if (str[i] == '\n'){
			str[i] = '\0';
			break;
		}
	}
}

void print_array(char *array[], int size){
	for (int i = 0; i < size; i++){
		fprintf(stdout, "%d. %s\n",i, array[i]);
	}
}

void print_header(char *str){
	char *pattern = "###########";
	fprintf(stdout, "\n%s%s%s\n\n", pattern, str, pattern);
}


