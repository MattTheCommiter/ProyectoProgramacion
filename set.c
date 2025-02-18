/**
 * @brief It implements the set module
 *
 * @file set.c
 * @author Matteo Artuñedo
 * @version 0
 * @date 18-02-2025
 * @copyright GNU Public License
 */

 #include "set.h"

 #define MAX_ELEMENTS_IN_SET 100
 /**
  * @brief this structure will be used for the definition of sets accross the game
  */
struct _Set{
    int n_ids;      /*!<Number of elements in the set*/
    Id ids[MAX_ELEMENTS_IN_SET];        /*!<Id of elements in the set*/
};

Set *set_create(){  
    Set *s;
    if(!(s = (Set *)calloc(sizeof(Set), 1))){
        return NULL;
    }
    s->n_ids = 0;
    return s;
}

Status *set_destroy(Set *s){
    if(!s) return ERROR;
    free(s);
    return OK;
}

Status set_add(Set *s, Id elementId);

Status set_del(Set *s, Id elementId);

void set_print(Set *s){
    if(!s) return;
    printf("\nThe id's of the elements of the set are: ");
    for(int i=0;i<s->n_ids;i++){
        printf("%ld", s->ids[i]);
    }
}