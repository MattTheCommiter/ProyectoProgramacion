/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Matteo Artuñedo
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

 
 #ifndef PLAYER_H
 #define PLAYER_H
 
 #include "types.h"
 #include "space.h"
 #include "game.h"

 
 typedef struct _Player Player;
 
 /**
  * @brief It creates a new player, allocating memory and initializing its members
  * @author Matteo Artuñedo
  *
  * @param id the identification number for the new player
  * @return a new player, initialized
  */
 Player* player_create(Id id);
 
 /**
  * @brief It destroys a player, freeing the allocated memory
  * @author Matteo Artuñedo
  *
  * @param player a pointer to the player that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status player_destroy(Player* player);
 
 /**
  * @brief It gets the id of a player
  * @author Matteo Artuñedo
  *
  * @param player a pointer to the player
  * @return the id of player
  */
 Id player_get_id(Player* player);
 
 /**
  * @brief It sets the name of a player
  * @author Matteo Artuñedo
  *
  * @param player a pointer to the player
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status player_set_name(Player* player, char* name);
 
 /**
  * @brief It gets the name of a player
  * @author Matteo Artuñedo
  *
  * @param player a pointer to the player
  * @return  a string with the name of the player
  */
 const char* player_get_name(Player* player);
 
/**
 * @brief It sets the id of the player's object
 * @author Matteo Artuñedo
 *
 * @param player a pointer to the player
 * @param value the id of the new object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
 Status player_set_object(Player* player, Id value);
 
 /**
  * @brief It returns the id of the player's object
  * @author Matteo Artuñedo
  *
  * @param player a pointer to the player
  * @return the id of the player's object
  */
 Id player_get_object(Player* player);
 
 /**
  * @brief It prints the player information
  * @author Matteo Artuñedo
  *
  * This fucntion shows the id and name of the player, the space it is located in and whether it has an object or not.
  * @param space a pointer to the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status player_print(Player* player);

 /**
  * @brief returns the id of the space where the player is currently in
  * 
  * @param player a pointer to the player
  * @return the id of the player's location
  */
 Id player_get_location(Player* player);

/**
 * @brief sets the id of the player's location to a new id
 * 
 * @param player pointer to the player
 * @param spaceId Id of the new player location
 * @return Status: whether the function was completed succesfully
 */
 Status player_set_location(Player* player, Id spaceId);
 #endif
 