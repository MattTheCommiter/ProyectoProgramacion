/**
 * @file object.c
 * @author Alvaro
 * @brief This file contains the fundamentals about the 'Object' data type
 * its functions and structure.
 * @version 0.1
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Structure where the information about the game`s object is stored
 * @author Alvaro Inigo
 * @date 08-02-2025
 */
struct _Object
{
    long id;                     /*!< Id number of the object, it must be unique*/
    char name[WORD_SIZE ];       /*!< Name of the object*/
    char description[WORD_SIZE]; /*!< The description of the object to inspect*/
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
    if (fprintf(stdout, "--->Object (Id: %ld ; Name: %s)\n", object->id, object->name))
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

Status object_set_description(Object *object, char *desc){
    if(!object || !desc)
    {
        return ERROR;
    }
    strcpy(object->description, desc);
    return OK;
}   

char *object_get_description(Object *object){
    if(!object)
    {
        return NULL;
    }
    return object->description;
}