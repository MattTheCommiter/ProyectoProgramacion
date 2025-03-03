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
    int n_ids;                          /*!<Number of elements in the set*/
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

Status set_destroy(Set *s){
    if(s == NULL) return ERROR;
    free(s);
    return OK;
}

Status set_add(Set *s, Id elementId){
    if(!s || elementId == NO_ID) return ERROR;

    /*Nos aseguramos de que no se haya alcanzado el tamaño máximo*/
    if(s->n_ids == (MAX_ELEMENTS_IN_SET)){
        return ERROR;
    }
    /*Si el elemento ya está en el set, devolvemos OK*/
    if(set_belongs(s, elementId)){
        return OK;
    }
    /*Añadimos el elemento al set y aumentamos el número de elementos de este*/
    s->ids[s->n_ids] = elementId;
    s->n_ids++;
    return OK;
}

Status set_del(Set *s, Id elementId){
    if(!s || elementId == NO_ID) return ERROR;

    if(!set_belongs(s, elementId)){
        return ERROR;
    }

    int pos = set_get_pos_from_Id(s, elementId);
    s->n_ids--;
    s->ids[pos] = s->ids[s->n_ids];
    s->ids[s->n_ids] = NO_ID;
    return OK;
}

int set_print(Set *s){
    if(!s) return -1;
    
    int i;

    printf("\nThe id's of the elements of the set are: ");
    for(i=0;i<s->n_ids;i++){
        if(!(printf("%ld ", s->ids[i]))){
            return -1;
        }
    }
    printf("\n");

    return (i);
}

Bool set_belongs(Set *s, Id elementId){
    if(!s  || elementId == NO_ID) return ERROR;

    Bool found=FALSE;

    for(int i=0;i<s->n_ids && !found;i++){
        if(s->ids[i] == elementId){
            found=TRUE;
        }
    }

    return found;
}

Bool set_is_empty(Set *s){
    if (!s || s->n_ids)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

int set_get_num_elements(Set *s){
    if(!s) return -1;

    return s->n_ids;
}

Id set_get_Id_in_pos(Set *s, int pos){
    if(!s || pos<0 || pos>(s->n_ids - 1) || (!s->n_ids)){
        return -1;
    }

    return s->ids[pos];
}

int set_get_pos_from_Id(Set *s, Id elementId){
    if(!s  || elementId == NO_ID || !set_belongs(s, elementId)){
        return -1;
    }
    for(int i=0;i<s->n_ids;i++){
        if(s->ids[i] == elementId){
            return i;
        }
    }
}