#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    int id;
    bool done;
    char desc[256];

}Task;

Task *DB[16] = { NULL };

int load_db(void);
int task_count(void);
int add_new_task(void);
int create_task(int id, int done, char *desc);
int print_db(void);
int save_db(void);
int print_menu(void);
int toggle_done_status(void);

int get_int_input(char *label);

int main(void){
    printf("TODO\n\n");



    // LOAD FILE
    if(load_db()){
        printf("Couldnt load the db.");
        return 2;
    }

    int cont;
    // PRINT THE DB
    print_db();
    printf("\n");
    if(print_menu() == 66){
        return 0;
    }

    return 0;
}

int load_db(void){
    
    FILE *db = fopen("db.csv", "r");
    if(db == NULL){
        printf("Unable to open file.\n");
        return 1;
    }

    int task_id;
    int task_bool;
    char *task_desc = malloc(256 * sizeof(char));
    if(task_desc == NULL){
        printf("Allocation error.");
        return 3;
    }
    
    fscanf(db, "%*[^\n]\n");
    
    while(fscanf(db, "%d,%d,%[^\n]s", &task_id, &task_bool, task_desc) == 3){
        if(create_task(task_id, task_bool, task_desc) != 0){
            printf("Couldnt create task.");
            return 4;
        }

    }
    
    free(task_desc);
    fclose(db);

    return 0;
}

int task_count(void){
    int count = 0;

    for(int i=0; i<16; i++){
        if(DB[i] != NULL){
            count++;
        }
    }

    return count;
}

int add_new_task(void){
    if(task_count() >= 16){
        printf("Too many tasks");
        return 5;
    }

    char desc[128];
    printf("Enter task: ");
    if (fgets(desc, sizeof(desc), stdin)) {
        // switch \n with \0
        char *p = strchr(desc, '\n');
        if (p) *p = '\0';
        
    } else {
        printf("Input error.\n");
        return 6;
    }
    
    printf("%s\n", desc);
    
    
    int end_of_the_db = task_count();
    if(create_task(end_of_the_db, 0, desc) != 0){
        printf("Couldnt create task.");
        return 4;
    }
    
    return 0;
}

int create_task(int id, int done, char *desc){
    Task *task = malloc(sizeof(Task));
    if(task == NULL){
        printf("Allocation error.");
        return 3;
    }

    task->id = id;
    task->done = done;
    strcpy(task->desc, desc);

    DB[id] = task;

    if(save_db() != 0) return 7;

    return 0;
}

int delete_task(){
    int id;

    // check if there is any task at all
    if(task_count() < 1){
        printf("Not enough tasks.");
        return 9;
    }

    printf("Task id(up to %d): ", task_count());
    scanf("%d", &id);

    if(id <= task_count()-1){

        free(DB[id]);
        DB[id] = NULL;

    }else {
        printf("Option out of range.");
        return 8;
    }

}

int print_db(void){
    for (int i=0; i<16; i++){
        Task *task = DB[i];
        if(task != NULL){
            printf("[%d] %d. -> %s\n", task->done, task->id, task->desc);
        }
    }

    return 0;
}

int save_db(void){
    FILE *fptr = fopen("db.csv", "w");
    if(fptr == NULL){
        printf("Unable to open file.");
        return 1;
    }

    fprintf(fptr, "id,tick,task_desc\n");

    for(int i=0; i<task_count(); i++){
        Task *task = DB[i];
        fprintf(fptr, "%d,%d,%s\n", task->id, task->done, task->desc);

    }

    fclose(fptr);

    return 0;
}

int print_menu(void){
    // 1 Add new task
    // 2 Remove existing task
    // 3 Toggle done status of existing task
    
    // 4 Help
    // 5 Quit

    printf("[1] Add new task\n");
    printf("[2] Remove existing task\n");
    printf("[3] Toggle done status of existing task\n");

    printf("[4] Help\n");
    printf("[5] Quit\n");
    printf("\n");

    int opt;
   
    opt = get_int_input("Select Option (1-5): ");

    if(1 <= opt <= 5){

        switch (opt)
        {
        case 1:
            add_new_task();
            
            break;

        case 3:
            toggle_done_status();
            break;

        case 5:
            return 66; // quit
        
        default:
            break;
        }

    }else {
        printf("Option out of range.");
        return 1;
    }

    return 0;

}

int toggle_done_status(void){
    // get id of task
    if(task_count() < 1){
        printf("Not enough tasks.");
        return 9;
    }

    int opt;
    char buffer[64];

    sprintf(buffer, "Id of the task to toggle(0-%d): ", task_count()-1);
    opt = get_int_input(buffer);

    DB[opt]->done = !DB[opt]->done;
    save_db();

    return 0;
}


int get_int_input(char *label){

    char input[16];
    int opt = 0;

    printf(label);
    if (fgets(input, sizeof(input), stdin)) {
        opt = atoi(input);
    } else {
        printf("Input error.\n");
        return -1;
    }

    return opt;

}
