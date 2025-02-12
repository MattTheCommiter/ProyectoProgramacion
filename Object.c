/**
 * @file Object.c
 * @author Alvaro
 * @brief This file contains the fundamentals about the 'Object' data type
 * its functions and structure.
 * @version 0.1
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object.h"

struct _Object
{
    long id;
    char name[WORD_SIZE + 1];
};

Object *object_create(Id id)
{
    Object *newObject = NULL;
    /* Error control*/
    if (id == NO_ID)
        return NULL;
    newObject = (Object *)malloc(sizeof(Object));
    if (!newObject)
        return NULL;
    /*Initialization of an empty space*/
    newObject->id = id;
    newObject->name[0] = '\0';
    return newObject;
}

Status object_destroy(Object *object)
{
    /*Error checking*/
    if (!object)
        return ERROR;
    free(object);
    object = NULL;
    return OK;
}

Id object_get_id(Object *object)
{
    /*Error checking*/
    if (!object)
        return NO_ID;
    return object->id;
}

char *object_get_name(Object *object)
{
    /*Error checking*/
    if (!object)
        return NULL;
    return object->name;
}

Status object_set_id(Object *object, Id id)
{
    /*Error checking*/
    if (!object)
        return ERROR;
    object->id = id;
    return OK;
}

Status object_set_name(Object *object, char *name)
{
    /*Error checking*/
    if (!object)
        return ERROR;
    strcpy(object->name, name);
    return OK;
}

Status object_print(Object *object)
{
    /*Error checking*/
    if (!object)
        return ERROR;
    fprintf(stdout, "--->Object (Id: %ld ; Name: %s)\n", object->id, object->name);
    return OK;
}