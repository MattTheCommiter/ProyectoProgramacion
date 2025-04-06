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

#include <stdio.h>
#include <stdlib.h>

 /**
  * @brief this structure will be used for the definition of sets accross the game
  */
struct _Set{
    int n_ids;                          /*!<Number of elements in the set*/
    Id ids[MAX_ELEMENTS_IN_SET];        /*!<Id of elements in the set*/
};

/**This function allocates memory for a new Set structure and initializes its fields. */
Set *set_create(){  
    Set *s;
    int i;
    if(!(s = (Set *)calloc(sizeof(Set), 1))){
        return NULL;
    }
    /*sets all positions in the set to NO_ID*/
    for(i=0;i<MAX_ELEMENTS_IN_SET;i++){
        s->ids[i] = NO_ID;
    }
    /*initialize the number of elements to 0*/
    s->n_ids = 0;
    return s;
}

/**This function frees the memory allocated for the Set structure */
Status set_destroy(Set *s){
    if(s == NULL) return ERROR;
    free(s);
    return OK;
}

/**This function adds the specified element to the set if it is not already present
 * and if the set has not reached its maximum capacity */
Status set_add(Set *s, Id elementId){
    if(!s || elementId == NO_ID) return ERROR;

    /*ensure the set has not reached its maximum capacity*/
    if(s->n_ids == (MAX_ELEMENTS_IN_SET)){
        return ERROR;
    }
    /*If the element is already in the set, return OK*/
    if(set_belongs(s, elementId)){
        return OK;
    }
    /* Add the element to the set and increase the number of elements*/
    s->ids[s->n_ids] = elementId;
    s->n_ids++;
    return OK;
}

/** This function removes the specified element from the set. If the element is not
 * present in the set, it returns ERROR. If the set pointer is NULL or the element ID
 * is NO_ID, it returns ERROR */
Status set_del(Set *s, Id elementId){
    int pos = set_get_pos_from_Id(s, elementId);
    if(!s || elementId == NO_ID) return ERROR;

    if(!set_belongs(s, elementId) || set_is_empty(s)){
        return ERROR;
    }

    s->n_ids--;
    /* Move the last element to the position of the removed element*/
    s->ids[pos] = s->ids[s->n_ids];
    s->ids[s->n_ids] = NO_ID;
    return OK;
}

/**This function prints out the IDs of the elements contained in the set. If the set
 * pointer is NULL, it returns -1. The function prints out each ID and returns the
 * number of elements */
int set_print(Set *s){
    int i;
    if(!s) return -1;
    
    printf("\nThe id's of the elements of the set are: ");
    for(i=0;i<s->n_ids;i++){
        if(!(printf("%ld ", s->ids[i]))){
            return -1;
        }
    }
    printf("\n");

    return (i);
}

/**This function checks if the specified element ID is present in the set.
 * It iterates through the elements in the set and returns TRUE if the element
 * is found, otherwise it returns FALSE */
Bool set_belongs(Set *s, Id elementId){
    int i;
    Bool found=FALSE;
    if(!s || elementId == NO_ID) return FALSE;

    for(i=0;i<s->n_ids && !found;i++){
        if(s->ids[i] == elementId){
            found=TRUE;
        }
    }

    return found;
}

/**This function determines whether the provided set is empty.
 * A set is considered empty if it is either NULL or contains no elements. */
Bool set_is_empty(Set *s){
    if(!s){
        return TRUE;
    }
    if (s->n_ids != 0)
    {
        return FALSE;
    }
    return TRUE;
}

/**This function determines whether the provided set is full.
 * A set is considered full if it is either NULL or contains the maximum number of elements allowed */
Bool set_is_full(Set *s){
    if(!s || s->n_ids == MAX_ELEMENTS_IN_SET){
        return TRUE;
    }
    return FALSE;
}

/** This function returns the number of elements contained in the given set.
 * If the set is NULL, it returns -1. */
int set_get_num_elements(Set *s){
    if(!s) return -1;

    return s->n_ids;
}

/**This function returns the ID located at the specified position within the provided set. */
Id set_get_Id_in_pos(Set *s, int pos){
    if(!s || pos<0 || pos>(s->n_ids - 1) || (!s->n_ids)){
        return -1;
    }

    return s->ids[pos];
}

/**This function returns the position of the specified ID within the given set. */
int set_get_pos_from_Id(Set *s, Id elementId){
    int i;
    if(!s  || elementId == NO_ID || !set_belongs(s, elementId)){
        return -1;
    }
    for(i=0;i<s->n_ids;i++){
        if(s->ids[i] == elementId){
            return i;
        }
    }
    return -1;
}