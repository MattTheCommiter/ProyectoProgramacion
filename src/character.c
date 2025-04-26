/**
 * @file character.c
 * @author Alvaro Inigo, Matteo Artunedo (following)
 * @brief definition of all the functions for the character module.
 * @version 0.1
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief definition for the struct Character
 * @author Alvaro Inigo
 *
 */
struct _Character
{
    Id id;                      /*!<Id of the character*/
    char name[WORD_SIZE];       /*!<a string that contains the name of the character*/
    char gdesc[GDESCTAM];       /*!<a string that contains the graphic description of the character*/
    char dead_gdesc[GDESCTAM];  /*!<a string that contains the graphic description of the character*/
    int health;                 /*!<the health of the character, an integer*/
    Bool friendly;              /*!<A bool that sets wether the character is friendly or not*/
    char message[WORD_SIZE];    /*!<a string for the message that a character says*/
    Id following;               /*!<Id of the player they are following*/
    Id location;                /*Id of the location of the character*/
};

Character *character_create(Id id)
{
    Character *newChar = NULL;
    newChar = (Character *)malloc(sizeof(Character));

    if (!newChar)
        return NULL;

    /*Initialization of a new character*/
    newChar->id = id;
    newChar->name[0] = '\0';
    newChar->gdesc[0] = '\0';
    newChar->health = NO_HP;
    newChar->friendly = FALSE;
    newChar->message[0] = '\0';
    newChar->following = NO_ID;

    return newChar;
}

Status character_destroy(Character *c)
{
    if (!c)
        return ERROR;

    free(c);
    return OK;
}

Status character_set_id(Character *c, Id id)
{
    if (!c)
        return ERROR;
    c->id = id;
    return OK;
}

Status character_set_name(Character *c, char *name)
{
    if (!c)
        return ERROR;
    strcpy(c->name, name);
    return OK;
}

Status character_set_gdesc(Character *c, char *desc)
{
    if (!c || !desc)
        return ERROR;
    strcpy(c->gdesc, desc);
    return OK;
}

Status character_set_dead_gdesc(Character *c, char *desc)
{
    if (!c || !desc)
        return ERROR;
    strcpy(c->dead_gdesc, desc);
    return OK;
}

Status character_set_health(Character *c, int hp)
{
    if (!c)
        return ERROR;
    c->health = hp;
    return OK;
}

Status character_set_friendly(Character *c, Bool behave)
{
    if (!c)
        return ERROR;
    c->friendly = behave;
    return OK;
}

Status character_set_message(Character *c, char *message)
{
    if (!c)
        return ERROR;
    strcpy(c->message, message);
    return OK;
}

Id character_get_id(Character *c)
{
    if (!c)
        return NO_ID;
    return c->id;
}

char *character_get_name(Character *c)
{
    if (!c)
        return NULL;
    return c->name;
}

char *character_get_gdesc(Character *c)
{
    if (!c)
        return NULL;
    return c->gdesc;
}

char *character_get_dead_gdesc(Character *c)
{
    if (!c)
        return NULL;
    return c->dead_gdesc;
}

int character_get_health(Character *c)
{
    if (!c)
        return NO_HP;
    return c->health;
}

Bool character_get_friendly(Character *c)
{
    if (!c)
        return FALSE;
    return c->friendly;
}

char *character_get_message(Character *c)
{
    if (!c)
        return NULL;
    return c->message;
}

Status character_print(Character *cha)
{
    if (!cha)
        return ERROR;

    /* 1. Print the id and the name of the character */
    fprintf(stdout, "--> Character (Id: %ld; Name: %s; gDescription: %s; health: %d)\n", cha->id, cha->name, cha->gdesc, cha->health);
    if (cha->friendly == FALSE)
    {
        fprintf(stdout, "\n--> The character is agressive");
    }
    else
    {
        fprintf(stdout, "\n--> The character is friendly");
    }
    fprintf(stdout, "\n---> The message: %s\n", cha->message);
    fprintf(stdout, "\n---> The Id of the player they are following: %ld\n", cha->following);

    return OK;
}

Status character_set_following(Character *c, Id follow_id){
    if(!c) return ERROR;

    c->following = follow_id;
    return OK;
}

Id character_get_following(Character *c){
    if(!c) return NO_ID;

    return c->following;
}

Status character_set_location(Character *c, Id location_id) {
    if (!c) return ERROR;

    c->location = location_id;
    return OK;
}

Id character_get_location(Character *c) {
    if (!c) return NO_ID;

    return c->location;
}