
#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Character Character;

Character *character_create(Id id);

Status character_destroy(Character *c);

Status character_set_id(Character *c, Id id);

Status character_set_name(Character *c, char *name);

Status character_set_gdesc(Character *c, char *desc);

Status character_set_health(Character *c, int hp);

Status character_set_friendly(Character *c, Bool behave);

Status character_set_message(Character *c, char *message);

Id character_get_id(Character *c);

char *character_get_name(Character *c);

char *character_get_gdesc(Character *c);

int character_get_health(Character *c);

Bool character_get_friendly(Character *c);

char *character_get_message(Character *c);


Status character_print(Character *cha);





#endif