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

Status set_destroy(Set *s){
    if(!s) return ERROR;
    free(s);
    return OK;
}

Status set_add(Set *s, Id elementId){
    if(!s) return ERROR;

    int i;
    /*Nos aseguramos de que no se haya alcanzado el tamaño máximo*/
    if(s->n_ids == (MAX_ELEMENTS_IN_SET)){
        return ERROR;
    }
    /*Si el elemento ya está en el set, devolvemos OK*/
    for(i=0;i<s->n_ids;i++){
        if(elementId == s->ids[i]){
            return OK;
        }
    }
    /*Añadimos el elemento al set y aumentamos el número de elementos de este*/
    s->ids[s->n_ids] = elementId;
    s->n_ids++;
    return OK;
}

Status set_del(Set *s, Id elementId){
    if(!s) return ERROR;
    int i,j, found=0;

    for(i=0;i<s->n_ids && !found;i++){
        if(s->ids[i] == elementId){
            found=1;
        }
    }
    if(found){
        for(j=i;j<s->n_ids;j++){
            s->ids[j-1] = s->ids[j];
        }
        s->ids[--j] = '\0';
        s->n_ids--;
        return OK;
    }else{
        return ERROR;
    }
}

void set_print(Set *s){
    if(!s) return;
    
    int i;

    printf("\nThe id's of the elements of the set are: ");
    for(i=0;i<s->n_ids;i++){
        printf("%ld", s->ids[i]);
    }
}