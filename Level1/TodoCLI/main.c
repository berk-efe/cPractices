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

int load_db(FILE *db);
int task_count(void);

int main(void){
    printf("TODO\n\n");

    FILE *dbptr = fopen("db.csv", "r");
    if(dbptr == NULL){
        printf("Unable to open file.\n");
    }

    load_db(dbptr);

    for (int i=0; i<16; i++){
        Task *task = DB[i];
        if(task != NULL){
            printf("[%d] %d. -> %s\n", task->done, task->id, task->desc);
        }
    }

    return 0;
}

int load_db(FILE *db){
    
    int task_id;
    int task_bool;
    char *task_desc = malloc(256 * sizeof(char));
    
    fscanf(db, "%*[^\n]\n");
    
    while(fscanf(db, "%d,%d,%[^\n]s", &task_id, &task_bool, task_desc) == 3){
        Task *task = malloc(sizeof(Task));
        if(task == NULL){
            printf("Allocation error.");
            return 1;
        }
        
        
        task->id = task_id;
        task->done = task_bool;
        strcpy(task->desc, task_desc);

        DB[task_id] = task;
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
