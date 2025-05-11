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
    char name[WORD_SIZE];        /*!< Name of the object*/
    char description[WORD_SIZE]; /*!< The description of the object to inspect*/
    char gdesc[GDESCTAM];        /*!< The graphical description of the object*/
    int health;                  /*!< Amount o fhealth object gan give or take from player */
    Bool movable;                /*!< Whether the object can be moved between spaces*/
    Id dependency;               /*!< Id of which object this object is dependent on to be picked up, if any */
    Id open;                     /*!< Id of the link this object can open when used, if any */
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
    /*Initialization of an empty object*/
    newObject->id = id;
    newObject->name[0] = '\0';
    newObject->description[0] = '\0';
    newObject->movable = FALSE;
    newObject->health = NO_HP;
    newObject->open = NO_ID;
    newObject->dependency = NO_ID;

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
    /*Valid parameters*/
    if (!object)
        return ERROR;

    /*check each print statement*/
    if (fprintf(stdout, "--->Object ID: %ld\n", object->id) < 0)
    {
        return ERROR;
    }
    if (fprintf(stdout, "--->Object name: %s\n", object->name) < 0)
    {
        return ERROR;
    }
    if (fprintf(stdout, "-->Object description: %s\n", object->description) < 0)
    {
        return ERROR;
    }
    if (fprintf(stdout, "-->Object health: %d\n", object->health) < 0)
    {
        return ERROR;
    }

    if (object->movable == TRUE)
    {
        if (fprintf(stdout, "-->Object is movable.\n") < 0)
            return ERROR;
    }
    else
    {
        if (fprintf(stdout, "-->Object is not movable.\n") < 0)
            return ERROR;
    }

    if (object->dependency != NO_ID)
    {
        if (fprintf(stdout, "-->Object that depends on this one: %ld\n", object->dependency) < 0)
        {
            return ERROR;
        }
    }
    else
    {
        if (fprintf(stdout, "-->Object has no dependencies.\n") < 0)
        {
            return ERROR;
        }
    }

    if (object->open != NO_ID)
    {
        if (fprintf(stdout, "-->Object opens link with id %ld\n", object->open) < 0)
        {
            return ERROR;
        }
    }
    else
    {
        if (fprintf(stdout, "-->Object opens no links.\n") < 0)
        {
            return ERROR;
        }
    }

    return OK;
}

Status object_set_description(Object *object, char *desc)
{
    if (!object || !desc)
    {
        return ERROR;
    }
    strcpy(object->description, desc);
    return OK;
}

char *object_get_description(Object *object)
{
    if (!object)
    {
        return NULL;
    }
    return object->description;
}

Status object_set_health(Object *object, int health)
{
    if (!object)
        return ERROR;

    object->health = health;

    return OK;
}

Status object_set_open(Object *object, Id link)
{
    if (!object)
        return ERROR;

    object->open = link;

    return OK;
}

Status object_set_dependency(Object *object, Id dep)
{
    if (!object)
        return ERROR;

    object->dependency = dep;

    return OK;
}

Status object_set_movable(Object *object, Bool movable)
{
    if (!object || (movable != TRUE && movable != FALSE))
        return ERROR;

    object->movable = movable;

    return OK;
}

Id object_get_dependency(Object *object)
{
    if (!object)
        return NO_ID;

    return object->dependency;
}

Bool object_get_movable(Object *object)
{
    if (!object)
        return NO_ID;

    return object->movable;
}

Id object_get_open(Object *object)
{
    if (!object)
        return NO_ID;

    return object->open;
}

int object_get_health(Object *object)
{
    if (!object)
        return -1;

    return object->health;
}

Status object_set_gdesc(Object *object, char *gdesc)
{
    if (!object || !gdesc)
    {
        return ERROR;
    }
    strncpy(object->gdesc, gdesc, GDESCTAM - 1);
    object->gdesc[GDESCTAM - 1] = '\0';
    return OK;
}

char *object_get_gdesc(Object *object)
{
    if (!object)
    {
        return NULL;
    }
    return object->gdesc;
}