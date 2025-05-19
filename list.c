#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "utils.h"
#include <string.h>

enum priority_ind{LOW, MEDIUM, HIGH};

struct task{
	struct task *next;
	struct task *prev;
	char due_date[11];
	int days_left;
	char desc[100];
	enum priority_ind priority; 
	
};

struct list{
	char list_name[100];
	struct task *first;
	struct task *last;
	int task_count;

};

struct task_data{
	char due_date[11];
	int days_left;
	char desc[100];
	enum priority_ind priority; 

};

struct list_data{
	char list_name[100];
	int task_count;

};

void create_new_list(struct list *lists[], int size){
	struct list *new_list;

	print_header("CREATING NEW LIST");
	
	new_list = malloc(sizeof(struct list));
	check_malloc(new_list);

	fprintf(stdout, "Enter list name: ");
	fgets(new_list->list_name, sizeof(new_list->list_name), stdin);
	remove_newline(new_list->list_name);
	new_list->first = NULL;
	new_list->last = NULL;
	new_list->task_count = 0;

	for (int i = 0 ; i < size; i++){
		if (lists[i] == NULL){
			lists[i] = new_list;
			break;
		}
	}
}


void print_lists(struct list *lists[],int size){
	for (int i = 0; i < size; i++){
		if (lists[i] != NULL){
			fprintf(stdout, "%d. %s\n", i+1, lists[i]->list_name);
		}
	}
}
bool is_empty_list(struct list *lists[],int size){
	for (int i = 0; i < size; i++){
		if (lists[i] != NULL){
			return false;
		}
	}
	return true;
}
struct list *select_list(struct list *lists[], int size){
	int list_number = 0;
	print_header("SELECT LIST");
	print_lists(lists, size);
	
	if(is_empty_list(lists, size)){
		fprintf(stdout, "List is empty, nothing to select\n");
		return NULL;
	}

	for(;;){
		fprintf(stdout, "Enter number of the list: ");
		scanf("%d", &list_number);
		list_number -= 1;
		if(lists[list_number] != NULL){
			fprintf(stdout, "%s selected\n", lists[list_number]->list_name);
			return lists[list_number];
		}
		else{
			fprintf(stdout, "Entered list not found\n");
			continue;
		}
	}
}


void add_task(struct list *list){
	print_header("ADD TASK");
	if (list == NULL){
		fprintf(stdout, "Select list before adding task\n");
		return;
	}

	struct task *new_task = malloc(sizeof(struct task));
	check_malloc(new_task);
	
	fprintf(stdout, "Enter the task: ");
	fgets(new_task->desc, sizeof(new_task->desc), stdin);
	remove_newline(new_task->desc);

	fprintf(stdout, "Select priority (0:LOW, 1:Medium, 2: High): ");
	scanf("%u", &new_task->priority);
	
	new_task->next = list->first;
	new_task->prev = NULL;
	
	if (list->first == NULL){
		list->first = new_task;
		list->last = new_task;
	}else{
		list->first->prev = new_task;
		list->first = new_task;
	}
	list->task_count++;
}

void see_tasks(struct list *list){
	if (list == NULL){
		fprintf(stdout, "Select list before adding task\n");
		return;
	}
	struct task *iter = list->first;
	print_header(list->list_name);
	fprintf(stdout, "%-50s %-10s %-10s %-10s\n", "Task", "Priority", "Due date", "Days left");
	while(iter != NULL){
		fprintf(stdout, "%s\n", iter->desc);
		iter = iter->next;
	}
}

void check_file(FILE *fp, char *file_name ){
	if (fp == NULL){
		fprintf(stderr, "Error opening file %s\n", file_name);
		exit(EXIT_FAILURE);
	}
}


void write_lists(char *file_name, struct list *lists[], int lists_size){

	struct list_data list_data;
	struct task_data task_data;
	FILE *fp = fopen(file_name, "wb");
	check_file(fp, file_name);
	
	for (int i = 0; i < lists_size; i++){
		
		if (lists[i] == NULL)
			continue;

		strcpy(list_data.list_name, lists[i]->list_name);
		list_data.task_count = lists[i]->task_count;
		fwrite(&list_data,sizeof(struct list_data), 1, fp);
		
		struct task *tasks = lists[i]->first; 
	
		while (tasks != NULL){
			strcpy(task_data.desc, tasks->desc);
			strcpy(task_data.due_date, tasks->due_date);
			task_data.days_left = tasks->days_left;
			task_data.priority = tasks->priority;
			fwrite(&task_data, sizeof(struct task_data), 1, fp);
			
			tasks = tasks->next;
		}
		
	}

		fclose(fp);

}

struct list *create_list(struct list_data *list_data){
	struct list *new_list;	
	new_list = malloc(sizeof(struct list));
	check_malloc(new_list);

	strcpy(new_list->list_name, list_data->list_name);
	new_list->first = NULL;
	new_list->last = NULL;
	new_list->task_count = list_data->task_count;

	return new_list;
	
}

void add_task_d(struct list *list, struct task_data *task_data){
	if (list == NULL){
		fprintf(stderr, "Empty list..\n");
		return;
	}

	struct task *new_task = malloc(sizeof(struct task));
	check_malloc(new_task);
	
	strcpy(new_task->desc, task_data->desc);
	new_task->priority = task_data->priority;
	strcpy(new_task->due_date, task_data->due_date);
	new_task->days_left = task_data->days_left;

	new_task->next = list->first;
	new_task->prev = NULL;
	
	if (list->first == NULL){
		list->first = new_task;
		list->last = new_task;
	}else{
		list->first->prev = new_task;
		list->first = new_task;
	}
}


void load_lists(char *file_name, struct list *lists[]){
	struct list *new_list;
	struct task *new_task;
	struct list_data list_data;
	struct task_data task_data;
	int list_counter = 0;
	FILE *fp = fopen(file_name, "rb");
	
	check_file(fp, file_name);
	fprintf(stdout, "Loading list data\n");	
	while(fread(&list_data, sizeof(struct list_data), 1, fp) == 1){
		new_list = create_list(&list_data);
		fprintf(stdout, "List name: %s\n", new_list->list_name);
		fprintf(stdout, "Task count: %d\n", new_list->task_count);
		for (int i = 0; i < new_list->task_count; i++){
			
			if(fread(&task_data, sizeof(struct task_data), 1, fp) != 1){
				fprintf(stderr, "Error reading %s data\n", new_list->list_name);
				return;
			}
			add_task_d(new_list, &task_data);
		}
	
		lists[list_counter] = new_list;
		list_counter++;

	}
	fclose(fp);
}
