/**
 * @file character.h
 * @author Alvaro Inigo
 * @brief Contains all the functions of the character domain.
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Character Character;
/**
 * @brief 
 * @author Alvaro Inigo
 * @param id to the new character
 * @return Character* a pointer to the new character
 */
Character *character_create(Id id);

/**
 * @brief Destroys the character.
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @return Status 
 */
Status character_destroy(Character *c);

/**
 * @brief sets the id for the Character
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @param id new id
 * @return Status 
 */
Status character_set_id(Character *c, Id id);

/**
 * @brief Sets the name for the character
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @param name the new name
 * @return Status 
 */
Status character_set_name(Character *c, char *name);

/**
 * @brief Sets a new graphic description for the character.
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @param desc the graphic description, a pointer to char
 * @return Status 
 */
Status character_set_gdesc(Character *c, char *desc);

/**
 * @brief Sets the health of the character
 * @author Alvaro Inigo
 * @param c a pointer to the character
 * @param hp the new hp
 * @return Status 
 */
Status character_set_health(Character *c, int hp);

/**
 * @brief Sets the behaviour of the character
 * @author Alvaro Inigo
 * @param c a pointer to the character
 * @param behave the new behaviour
 * @return Status 
 */
Status character_set_friendly(Character *c, Bool behave);

/**
 * @brief Sets the message of the character
 * @author Alvaro Inigo
 * @param c a pointer to the character
 * @param message the new message, a pointer to char
 * @return Status 
 */
Status character_set_message(Character *c, char *message);

/**
 * @brief gets the id of the character
 * @author Alvaro Inigo
 * @param c a pointer to the character
 * @return Id
 */

Id character_get_id(Character *c);

/**
 * @brief gets the name of the character
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @return char* 
 */
char *character_get_name(Character *c);

/**
 * @brief Gets the graphic description of character
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @return char* 
 */
char *character_get_gdesc(Character *c);

/**
 * @brief gets the health of the caracter
 * @author Alvaro Inigo
 * @param c a pointer to the character
 * @return int 
 */
int character_get_health(Character *c);

/**
 * @brief Gets the behaviour of the character
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @return Bool 
 */
Bool character_get_friendly(Character *c);

/**
 * @brief Gets the message of the character
 * @author Alvaro Inigo
 * @param c a pointer to character
 * @return char* 
 */
char *character_get_message(Character *c);

/**
 * @brief Prints the character through screen
 * @author Alvaro Inigo
 * @param cha a pointer to character
 * @return Status 
 */
Status character_print(Character *cha);





#endif