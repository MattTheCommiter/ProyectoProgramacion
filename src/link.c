#include "link.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Link
 * 
 * This struct stores all the information relative to a link
*/
struct _Link {
    Id link_id;                 /*!< Id of the link, it must be unique */
    char name[WORD_SIZE + 1];   /*!< Name of the link, static */
    Id origin_id;               /*!< Id of the origin space it connects */
    Id destination_id;          /*!< Id of the destination space it connects */
    Direction direction;        /*!< Direction the link points towards */
    Bool is_open;               /*!< Whether link is open/unlocked or not */
};

Link *link_create(Id link_id) {
    Link *new_link = NULL;

    /* error checks */
    if (link_id == NO_ID) return NULL;

    /* memory allocation */
    if (!(new_link = (Link *) malloc(sizeof(Link)))) return NULL;


    /* variable initializations */
    new_link->link_id = link_id;
    new_link->name[0] = '\0';
    new_link->destination_id = NO_ID;
    new_link->origin_id = NO_ID;
    new_link->direction = UNKNOWN_DIR;
    new_link->is_open = FALSE;

    /* correct exit */
    return new_link;   
}

void link_destroy(Link *l) {
    if (l) free(l);
}

Status link_set_name(Link *l, char *name) {
    if (!l || !name) return ERROR;

    if (!(strcpy(l->name, name))) return ERROR;

    return OK;
}

Status link_set_destination_id(Link *l, Id dest_id) {
    /* error checks */
    if (l == NULL || dest_id == NO_ID) return ERROR;

    /* variable assignment */
    l->destination_id = dest_id;

    /* correct exit */
    return OK;
}

Status link_set_origin_id(Link *l, Id orig_id) {
    /* error checks */
    if (l == NULL || orig_id == NO_ID) return ERROR;

    /* varibale assignment */
    l->origin_id = orig_id;

    /* correct exit */
    return OK;
}

Status link_set_direction(Link *l, Direction dir) {
    /* error checks */
    if (l == NULL || dir == UNKNOWN_DIR) return ERROR;

    /* variable assignment */
    l->direction = dir;

    /* correct exit */
    return OK;
}

Status link_set_is_open(Link *l, Bool open) {
    /* error checks */
    if (l == NULL) return ERROR;

    /* variable assignment */
    l->is_open = open;

    /* correct exit */
    return OK;
}

const char *link_get_name(Link *l) {
    if (!l) return NULL;

    return l->name;
}

Id link_get_destination_id(Link *l) {
    /* error checks */
    if (l == NULL) return NO_ID;

    /* correct exit */
    return l->destination_id;
}

Id link_get_origin_id(Link *l) {
    /* error checks */
    if (l == NULL) return NO_ID;

    /* correct exit */
    return l->origin_id;
}

Id link_get_id(Link *l) {
    /* error checks */
    if (l == NULL) return NO_ID;

    /* correct exit */
    return l->link_id;
}

Bool link_get_is_open(Link *l) {
    /* error checks */
    if (l == NULL) return FALSE;

    /* correct exit */
    return l->is_open;
}

Direction link_get_direction(Link *l) {
    /* error checks */
    if (l == NULL) return NO_ID;

    /* correct exit */
    return l->direction;
}

void link_print(Link *l) {

    /* check link existence */
    if (l == NULL) {
        fprintf(stdout, "-->Link does not exist.\n");
        return; /* early return */
    } else {
        fprintf(stdout, "-->Link information - %s - (%p):\n", l->name, l);
    }

    fprintf(stdout, " --->Link id: %ld\n", l->link_id);                   /* print link id*/
    fprintf(stdout, " --->Link destination: %ld\n", l->destination_id);   /* print link destination id */   
    fprintf(stdout, "Link origin: %ld\n", l->origin_id);             /* print link origin id */

    /* print link direction */
    switch (l->direction) {
        case 0: 
            fprintf(stdout, "--->Link direction: UNKNOWN.\n");
            break;
        case 1: 
            fprintf(stdout, "--->Link direction: NORTH.\n");
            break;
        case 2: 
            fprintf(stdout, "--->Link direction: SOUTH.\n");
            break;
        case 3: 
            fprintf(stdout, "--->Link direction: EAST.\n");
            break;
        case 4: 
            fprintf(stdout, "--->Link direction: WEST.\n");
            break;
        default:
            fprintf(stdout, "--->Link direction not defined.\n");
            break;
    }

    /* print whether link is open or not */
    if (l->is_open) {
        fprintf(stdout, "--->Link is open.\n");
    } else {
        fprintf(stdout, "--->Link is closed.\n");
    }
}
