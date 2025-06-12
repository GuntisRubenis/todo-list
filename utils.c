#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void flush_buffer(){
	while (getchar() != '\n')
		;
}

char *get_date(){
	static char date[11];
	int m, d, y;
	flush_buffer();
	fgets(date, sizeof(date), stdin);
	while(sscanf(date, "%2d-%2d-%4d", &m,&d,&y) != 3){
		fprintf(stderr, "Incorrect date format, expected (mm-dd-yyy):");
		fgets(date, sizeof(date), stdin);

	}
	//remove_newline(date);

	return date;
}

/*this need to have logic update */
int days_left(char *date){
	int n_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int m = 0,d = 0,y = 0,fm = 0,fd = 0,fy= 0;
	int year_diff;
	int tot_d_to = 0, tot_d_now = 0;

	time_t now = time(NULL);
	struct tm *local = localtime(&now);
	char local_str[11];
	strftime(local_str, sizeof(local_str), "%m-%d-%Y", local);

	if (sscanf(date, "%2d-%2d-%4d", &m,&d,&y) != 3){
		fprintf(stdout,"incorrect date format");
		return -1;
	}
	
	if (sscanf(local_str, "%2d-%2d-%4d", &fm,&fd,&fy) != 3){
		fprintf(stdout,"incorrect date format");
		return -1;
	}

	
	year_diff = y - fy;
	fprintf(stdout, "year_diff: %d\n",year_diff);
	fprintf(stdout, "fm:%d fd:%d fy:%d\n", fm, fd, fy);
	fprintf(stdout, "fm:%d fd:%d fy:%d\n", m, d, y);

	for(int i = 0; i < (int) sizeof(n_days); i++){
		if (i == (m-1))
			break;
		tot_d_to += n_days[i];
	}
	tot_d_to = tot_d_to + d + (360 *year_diff);

	for(int i = 0; i < (int) sizeof(n_days); i++){
		if (i == (fm-1))
			break;
		tot_d_now += n_days[i];
	}

	tot_d_now += fd;

	fprintf(stdout, "tot_d_to: %d\n",tot_d_to);
	fprintf(stdout, "tot_d_now:%d\n", tot_d_now);
	return (tot_d_to - tot_d_now); 
}
