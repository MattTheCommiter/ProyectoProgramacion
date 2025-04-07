/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Matteo Artunedo, Alvaro Inigo,  AGL (modifications for updating Player to include a backpack)
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "set.h"
#include "character.h" /* defines GDESCTAM macro */
#include "inventory.h"

/**
 * @brief Defines a new type for the Player structure.
 */
typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Matteo Artunedo
 *
 * @param id the identification number for the new player
 * @param inventory_size the max number of items the player can have in its inventory
 * @return a new player, initialized
 */
Player *player_create(Id id, int inventory_size);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Matteo Artunedo
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status player_destroy(Player *player);

/**
 * @brief Sets the ID of the player.
 * @author Matteo Artunedo, AGL
 * @param player Pointer to the Player structure.
 * @param playerId The new ID to be assigned to the player.
 * @return Status indicating the success or failure of the operation.
 *         - OK if the ID is successfully set.
 *         - ERROR if the player pointer or playerId is invalid.
 */
Status player_set_id(Player *player, Id playerId);

/**
 * @brief It gets the id of a player
 * @author Matteo Artunedo
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player *player);

/**
 * @brief It sets the name of a player
 * @author Matteo Artunedo
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status player_set_name(Player *player, char *name);

/**
 * @brief It gets the name of a player
 * @author Matteo Artunedo
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char *player_get_name(Player *player);

/**
 * @brief Checks if the player's backpack is full
 * @author Team 2101_D, AGL
 * @param player A pointer to the player
 * @return TRUE if the backpack is full, FALSE otherwise
 */
Bool player_backpack_is_full(Player *player);

/**
 * @brief Checks if the player's backpack is empty
 * @author Team 2101_D, AGL
 * @param player A pointer to the player
 * @return TRUE if the backpack is empty, FALSE otherwise
 */
Bool player_backpack_is_empty(Player *player);

/**
 * @brief Adds an object to the player's backpack.
 * @author Team 2101_D, AGL
 * @param player A pointer to the Player structure.
 * @param obj_id The ID of the object to be added to the backpack.
 * @return Status OK if the object was added successfully, ERROR otherwise.
 */
Status player_add_object_to_backpack(Player *player, Id obj_id);

/**
 * @brief Removes an object from the player's backpack.
 * @author Team 2101_D, AGL
 * @param player A pointer to the Player structure.
 * @param obj_id The ID of the object to be removed from the backpack.
 * @return Status OK if the object was removed successfully, ERROR otherwise.
 */
Status player_remove_object_from_backpack(Player *player, Id obj_id);

/**
 * @brief Gets the number of objects in the player's backpack.
 * @author Team 2101_D, AGL
 * @param player A pointer to the Player structure.
 * @return int The number of objects in the backpack, or -1 if the player or backpack is invalid.
 */
int player_get_num_objects_in_backpack(Player *player);

/**
 * @brief Gets the object ID at a specified position in the player's backpack
 * @author Team 2101_D, AGL
 * @param player A pointer to the Player structure.
 * @param position The position of the object in the backpack.
 * @return Id The object ID at the specified position, or NO_ID if the player, backpack, or position is invalid.
 */
Id player_get_backpack_object_id_at(Player *player, int position);

/**
 * @brief Checks if the player's backpack contains a specific object ID.
 * @author Team 2101_D, AGL
 * @param player A pointer to the Player structure.
 * @param obj_id The ID of the object to check for in the backpack.
 * @return Bool TRUE if the backpack contains the object ID, FALSE otherwise.
 */
Bool player_backpack_contains(Player *player, Id obj_id);

/**
 * @brief It prints the details of the player.
 * @author Matteo Artunedo
 *

 * This function prints the details of the player, including the ID, name, location, health, and backpack contents.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status player_print(Player *player);

/**
 * @brief returns the id of the space where the player is currently in
 * @author Matteo Artunedo
 *
 * @param player a pointer to the player
 * @return the id of the player's location
 */
Id player_get_location(Player *player);

/**
 * @brief sets the id of the player's location to a new id
 * @author Matteo Artunedo
 * @param player pointer to the player
 * @param spaceId Id of the new player location
 * @return Status: whether the function was completed succesfully
 */
Status player_set_location(Player *player, Id spaceId);

/**
 * @brief sets the health of the player
 * @author Alvaro Inigo
 * @param p a pointer to player
 * @param hp the new health
 * @return Status
 */
Status player_set_health(Player *p, int hp);

/**
 * @brief Gets the hp of the player
 * @author Alvaro Inigo
 * @param p a pointer to the player
 * @return int the health
 */
int player_get_health(Player *p);

/**
 * @brief sets the graphic description of a player
 * @author Alvaro Inigo
 * @param player a pointer to the player
 * @param gdesc a pointer to char, the string that contais the graphic description
 * @return Status OK of ERROR
 */
Status player_set_gdesc(Player *player, char *gdesc);

/**
 * @brief gets the graphic description of a player
 * @author Alvaro Inigo
 * @param player a pointer to the player
 * @return char* a pointer to the string of the gdesc
 */
char *player_get_gdesc(Player *player);

/**
 * @brief tells if an object is in the players backpack
 * @author Alvaro Inigo
 * @param player a pointer to the player
 * @param objectId the id of the object
 * @return Bool TRUE if it belongs to the inventory or FALSE
 */
Bool player_object_is_in_backpack(Player *player, Id objectId);
#endif
