#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#define VERSION 1.0


int main (){
	char *operations[] ={"Exit", "Create new list", "Select list", "Add task", "See tasks"};
	int operation_size = sizeof(operations)/sizeof(char*);
	int operation;
	int lists_size; 
	struct list *lists[10] = {NULL};
	struct list *active_list = NULL;
	
	load_lists("lists.txt",lists);
	
	fprintf(stdout, "Todo Lists V.%.1f\n", VERSION);

	while (operation != '0'){
		
		lists_size = sizeof(lists)/sizeof(struct list*);
		
		print_header("OPERATIONS");
		print_array(operations, operation_size);
		fprintf(stdout, "Select operation: ");
		scanf("%d", &operation);
		getchar();

		switch(operation){
			case 0:
				print_header("EXITING");
				write_lists("lists.txt",lists,lists_size);
				free_list(lists, lists_size);
				return 0;
			case 1:	
				create_new_list(lists, lists_size);
				break;
			case 2:
				active_list = select_list(lists, lists_size);
				break;
			case 3:
				add_task(active_list);
				break;
			case 4:
				see_tasks(active_list);
		}
	}


}


