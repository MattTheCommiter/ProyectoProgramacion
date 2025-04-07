/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "character.h"
#include "link.h"

#define MAX_SPACES 100              /*!<The maximum ammount of spaces that can exist in the game*/
#define MAX_OBJECTS 10              /*!<The maximum ammount of objects present at the game*/
#define MAX_CHARACTERS 10           /*!<The maximum ammount of characters present at the game*/
#define MAX_LINKS (MAX_SPACES * 4)  /*!<The maximum amount of links present at the game*/
#define MAX_MESSAGE 50              /*!<The maximum ammout of characters in the messages*/
#define MAX_PLAYERS 8               /*!<The maximum ammout of players that can play at the same time*/

/**
 * @brief describes whether we want to access to the last, the second to last or the third to last command
 * 
 */
typedef enum {
    THIRD_TO_LAST,  /*Indicates we are retreiving the third to last command the player introduced*/
    SECOND_TO_LAST, /*Indicates we are retreiving the second to last command the player introduced*/
    LAST            /*Indicates we are retreiving the last command the player introduced*/
} CommandPosition;

/**
 * @brief specifices the type for the _Game structure 
 * 
 */
typedef struct _Game Game;

/**
 * @brief adds a new space to the array of spaces in the game structure
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game a pointer to the structure with the game's main information
 * @param space a pointer to the space that is going to be added
 * @return Status: if the function was completed succesfully
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Dynamically allocates memory for the game and initializes all the structures components
 *
 * @date 21-02-2025
 * @author Alvaro Inigo
 *
 * @param game a double pointer to the structure with the game's main information
 * @return Status: if the function was completed succesfully
 */
Status game_create(Game **game);

/**
 * @brief creates the game calling game_create and reads a text file to get information about the spaces
 *
 * @date 21-02-2025
 * @author Alvaro Inigo
 *
 * @param game a double pointer to the structure with the game's main information
 * @param filename name of the file where the game's information is saved
 * @return Status: if the function was completed succesfully
 */
Status game_create_from_file(Game **game, char *filename);

/**
 * @brief frees all the dynamically allocated memory in the game structure
 *
 * @date 27-01-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @return Status: if the function was completed succesfully
 */
Status game_destroy(Game *game);

/**
 * @brief returns a pointer to the space that has the id passed as an argument
 *
 * @date 15-02-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @param id the id of the desired space
 * @return a pointer to the desired space
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief returns the location of the player that is currently playing
 *
 * @date 27-01-2025
 * @author Alvaro Inigo, Matteo Artunedo (multiplayer)
 *
 * @param game a pointer to the structure with the game's main information
 * @return the id of the player's location
 */
Id game_get_current_player_location(Game *game);

/**
 * @brief changes the location of the player that is currently playing
 *
 * @date 27-01-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @param id the id of the new location
 * @return Status: if the function was completed succesfully
 */
Status game_set_current_player_location(Game *game, Id id);

/**
 * @brief returns the id of the object's location
 *
 * @date 27-01-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @param objectId the Id of the object we want to find, returning its location
 * @return the id of the object's location
 */
Id game_get_object_location(Game *game, Id objectId);

/**
 * @brief changes the id of the object's location to the one passed as an argument
 *
 * @date 27-01-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @param id the id of the new location
 * @param objectId the id of the object of which we want to set the location
 * @return Status
 */
Status game_set_object_location(Game *game, Id id, Id objectId);

/**
 * @brief returns a boolean value that describes if the game has finished or not
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game a pointer to the structure with the game's main information
 * @return Bool (TRUE or FALSE) that describes if the game is finished or not
 */
Bool game_get_finished(Game *game);

/**
 * @brief Changes the state of the game, starting or finishing it
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game a pointer to the structure with the game's main information
 * @param finished the new boolean value that describes whether the game has finished or not
 * @return Status if the function has been completed succesfully
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief prints the players' location, the objects' location and prints the information regarding all the spaces in the game
 *
 * @date 27-01-2025
 * @author Matteo Artunedo
 *
 * @param game a pointer to the structure with the game's main information
 */
void game_print(Game *game);
/**
 * @brief Gets a pointer to the player that is currently playing
 *
 * @date 12-02-2025
 * @author Alvaro Inigo, Matteo Artunedo (multiplayer)
 *
 * @param game a pointer to the strucuture.
 * @return a pointer to the player.
 */
Player *game_get_current_player(Game *game);
/**
 * @brief gets the object of the game(pointer) with a specified id 
 *
 * @date 12-02-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the game
 * @param id the id of the desired object
 * @return a pointer to the object
 */
Object *game_get_object(Game *game, Id id);
/**
 * @brief adds an object to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param object a pointer to the object we want to add
 * @return Status if the function has been completed succesfully
 */
Status game_add_object(Game *game, Object *object);
/**
 * @brief adds an object to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param position the position in the array of objects of the object we want to get the Id
 * @return Id the id of the object
 */
Id game_get_object_id_at(Game *game, int position);
/**
 * @brief adds a character to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param character a pointer to the character we want to add
 * @return Status if the function has been completed succesfully
 */
Status game_add_character(Game *game, Character *character);
/**
 * @brief adds an object to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param position the position in the array of objects of the object we want to get the Id
 * @return Id the id of the character
 */
Id game_get_character_id_at(Game *game, int position);

/**
 * @brief gets the object of the game(pointer)
 *
 * @date 12-02-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the game
 * @param id the id of the desired object
 * @return a pointer to the object
 */
Object *game_get_object(Game *game, Id id);
/**
 * @brief adds an object to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param object a pointer to the object we want to add
 * @return Status if the function has been completed succesfully
 */
Status game_add_object(Game *game, Object *object);
/**
 * @brief adds an object to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param position the position in the array of objects of the object we want to get the Id
 * @return Id the id of the object
 */
Id game_get_object_id_at(Game *game, int position);
/**
 * @brief adds a character to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param character a pointer to the character we want to add
 * @return Status if the function has been completed succesfully
 */
Status game_add_character(Game *game, Character *character);
/**
 * @brief adds an object to the game
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param position the position in the array of objects of the object we want to get the Id
 * @return Id the id of the character
 */
Id game_get_character_id_at(Game *game, int position);

/**
 * @brief gets the object of the game(pointer)
 *
 * @date 12-02-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to game
 * @param id the id of the desired object
 * @return a pointer to the object
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief returns the character of the game by a specific name
 * @date 24-03-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param name a string that contains the name
 * @return Character* a pointer to the character
 */
Character *game_get_character_from_name(Game *game, char *name);
/**
 * @brief Gets an object's Id from its name
 * @date 03/03/25
 * @author Alvaro Inigo
 * @param game a pointer to game
 * @param name a pointer to char, the name of the object
 * @return Id the id of the object with the name
 */
Id game_get_objectId_from_name(Game *game, char *name);

/**
 * @brief Gets the message in the game
 * @date 04/03/25
 * @author Matteo Artunedo
 * @param game a pointer to game
 * @return a string with the message
 */
char *game_get_message(Game *game);

/**
 * @brief Sets the message in the game
 * @date 04/03/25
 * @author Matteo Artunedo
 * @param game a pointer to game
 * @param msg a string with the new message
 * @return OK if the function is completed succesfully or ERROR if an error occurrs
 */
Status game_set_message(Game *game, char *msg);

/**
 * @brief Gets the object in a specific position in the object array
 * @date 04/03/25
 * @author Matteo Artunedo
 * @param game a pointer to game
 * @param pos an int with the position of the object in the array
 * @return pointer to the object or NULL if an error occurrs
 */
Object *game_get_object_in_pos(Game *game, int pos);

/**
 * @brief gets the numbers of objects un game
 * @date 08/03/25
 * @author Alvaro Inigo
 * @param game a pointer to game
 * @return int , the number of objects in the game
 */
int game_get_n_objects(Game *game);

/**
 * @brief gets the number of characters in the game
 * @date 08/03/25
 * @author Alvaro Inigo
 * @param game a pointer to game
 * @return int , the number of characters in the game
 */
int game_get_n_characters(Game *game);
/**
 * @brief gets the Id of the space a character is at
 * @date 08/03/25
 *@author Alvaro Inigo
 * @param game a pointer to the game
 * @param character_id the Id of the character we are looking for
 * @return Id the id of the space the character is located at.
 */
Id game_get_character_location(Game *game, Id character_id);


/**
 * @brief adds a given link to the array of links in the game structure [Time: O(n)]
 * @author Guilherme Povedano 
 * @date 23/03/2025
 * @param game pointer to the game structure that will be modified 
 * @param link pointer to the link that will be added to the game structure 
 * @return OK if everything went well, or ERROR if the arguments aren't valid or a link already exists in that space and direction
*/
Status game_add_link(Game *game, Link *link);

/**
 * @brief Fetches if a link matching input parameters is open or not [Time: O(n)] 
 * @author Guilherme Povedano
 * @date 22/03/2025
 * @param game pointer to the current game
 * @param current_space origin_id of the desired link
 * @param link_direction direction of the desired link
 * @return Bool for link->is_open if it can be found or FALSE otherwise.
*/
Bool game_connection_is_open(Game *game, Id current_space, Direction link_direction);

/**
 * @brief Fetches the destination_id of a link matching input parameters [Time: O(n)]
 * @author Guilherme Povedano
 * @date 22/03/2025
 * @param game pointer to the current game
 * @param current_space origin_id of the desired link
 * @param link_direction direction of the desired link
 * @return the id number of the destination_id of the link if it exists or FALSE otherwise. 
*/
Id game_get_connection(Game *game, Id current_space, Direction link_direction);

/**
 * @brief fetches the number of links contained in the game [Time: O(1)]
 * @author Guilherme Povedano 
 * @date 23/03/2025
 * @param game pointer to game structure containing the number of links
 * @return the number of links in a game, or -1 in case of error
*/
int game_get_n_links(Game *game);

/**
 * @brief sets the description of an object in the game
 * @date 24/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param desc the new description of the object
 * @return Status OK or ERROR.
 */
Status game_set_description(Game *game, char *desc);
/**
 * @brief Returns the description of an object in the game
 * @date 24/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return char* the string that contains the description
 */
char *game_get_description(Game *game);

/*Funcion temporal, hasta que cambiemos player por un array de jugadores
necesaria por ahora para el modulo de game reader
*/

/**
 * @brief adds a player to the game, as well as their command history
 * @author Alvaro Inigo, Matteo Artunedo (command history)
 * @param game a pointer to the game
 * @param player a pointer to the new player
 * @return Status either OK or ERROR
 */
Status game_add_player(Game *game, Player *player);


/**
 * @brief Increments the turn, allowing the next player to play
 * @author Matteo Artunedo
 * @param game pointer to the game
 */
void game_next_turn(Game *game);

/**
 * @brief receives the current turn of the player
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @return current turn
 */
int game_get_turn(Game *game);

/**
 * @brief returns the number of players in the game
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @return the number of players
 */
int game_get_n_players(Game *game);

/**
 * @brief it deletes a player from the array of players as well as his command history, freeing the allocated memory and reorganizing the arrays
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @return Status either OK or ERROR
 */
Status game_delete_player(Game *game);

/**
 * @brief changes the information data type for the current player, updating the last command and moving the ones that already existed one position backwards
 *
 * @author Matteo Artunedo
 *
 * @param game a pointer to the structure with the game's main information
 * @param last_cmd the new last_cmd
 * @return Status: if the function was completed succesfully
 */
Status game_interface_data_set_last_command(Game *game, Command *last_cmd);

/**
 * @brief Returns the last, second to last or third to last command according to the position argument
 * @author Matteo Artunedo
 * @param game pointer to the game structure
 * @param pos position of the command we want to get
 * @return pointer to the desired command
 */
Command *game_interface_data_get_cmd_in_pos(Game *game, CommandPosition pos);
#endif
