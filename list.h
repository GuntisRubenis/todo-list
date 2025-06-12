#ifndef LIST_H
#define LIST_H


struct task;
struct list;


void create_new_list(struct list *lists[], int size);
void print_lists(struct list *lists[],int size);
struct list *select_list(struct list *lists[], int size);
void add_task(struct list *list);
void see_tasks(struct list *list);
void write_lists(char *file_name, struct list *lists[], int lists_size);
void load_lists(char *file_name, struct list *lists[]);
void free_list(struct list *lists[], int size);

#endif

