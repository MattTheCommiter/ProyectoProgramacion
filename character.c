/**
 * @file character.c
 * @author Alvaro Inigo
 * @brief definition of all the functions for the character module.
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

#define GdescTam 7
#define MAXHEALTH 100
/**
 * @brief definition for the struct Character
 * @author Alvaro Inigo
 * 
 */
struct _Character{
    Id id;
    char name[WORD_SIZE];
    char gdesc[GdescTam];
    int health;
    Bool friendly;
    char message[WORD_SIZE];

};


Character *character_create(Id id){
    Character *newChar = NULL;
    newChar = (Character *)malloc(sizeof(Character));

    if(!newChar) return NULL;

    /*Initialization of a new character*/
    newChar->id = id;
    newChar->name[0] = '\0';
    newChar->gdesc[0] = '\0';
    newChar->health = NO_HP;
    newChar->friendly = FALSE;
    newChar->message[0] = '\0';

    return newChar;

}

Status character_destroy(Character *c){
    if(!c) return ERROR;

    free(c);
    return OK;
}

Status character_set_id(Character *c, Id id){
    if(!c) return ERROR;
    c->id = id;
    return OK;
}

Status character_set_name(Character *c, char *name){
    if(!c) return ERROR;
    strcpy(c->name, name);
    return OK;
}

Status character_set_gdesc(Character *c, char *desc){
    if(!c) return ERROR;
    strcpy(c->gdesc, desc);
    return OK;
}

Status character_set_health(Character *c, int hp){
    if(!c) return ERROR;
    c->health = hp;
    return OK;
}

Status character_set_friendly(Character *c, Bool behave){
    if(!c) return ERROR;
    c->friendly = behave;
    return OK;
}

Status character_set_message(Character *c, char *message){
    if(!c) return ERROR;
    strcpy(c->message, message);
    return OK;
}

Id character_get_id(Character *c){
    if(!c) return NO_ID;
    return c->id;
}

char *character_get_name(Character *c){
    if(!c) return NULL;
    return c->name;
}

char *character_get_gdesc(Character *c){
    if(!c) return NULL;
    return c->gdesc;
}

int character_get_health(Character *c){
    if(!c) return NO_HP;
    return c->health;
}

Bool character_get_friendly(Character *c){
    if(!c) return FALSE;
    return c->friendly;
}

char *character_get_message(Character *c){
    if(!c) return NULL;
    return c->message;
}


Status character_print(Character *cha){
    if(!cha) return ERROR;

      /* 1. Print the id and the name of the character */
  fprintf(stdout, "--> Character (Id: %ld; Name: %s gDescription: %s health: %d)\n", cha->id, cha->name, cha->gdesc,cha->health);
  if (cha->friendly == FALSE)
  {
    fprintf(stdout, "--> The character is agressive");
  }
  else
  {
    fprintf(stdout, "--> The character is friendly");
  }
  fprintf(stdout, "---> The message: %s",cha->message);

  return OK;
}

Character *character_spider_create(){
    Character *spider = NULL;
    spider = character_create(SPIDER);
    if(!spider){
        return NULL;
    }
    spider->friendly = FALSE;
    strcpy(spider->gdesc,"/\\oo/\\");
    spider->health = 5;
    strcpy(spider->name,"Spider");
    return spider;
}

Character *character_ant_friend_create(){
    Character *ant = NULL;
    ant = character_create(ANT_FRIEND);
    if(!ant){
        return NULL;
    }
    ant->friendly = TRUE;
    strcpy(ant->gdesc,"^0m");
    strcpy(ant->message,"Hi!");
    ant->health = 5;
    strcpy(ant->name,"Ant");
    return ant;
}