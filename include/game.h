/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG, Álvaro Iñigo, Matteo Artuñedo, Guilherme Povedano, Araceli Gutiérrez
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
#include "cinematics.h"
#include "mission.h"

#define MAX_SPACES 100              /*!<The maximum ammount of spaces that can exist in the game*/
#define MAX_OBJECTS 25              /*!<The maximum ammount of objects present at the game*/
#define MAX_CHARACTERS 10           /*!<The maximum ammount of characters present at the game*/
#define MAX_LINKS (MAX_SPACES * 4)  /*!<The maximum amount of links present at the game*/
#define MAX_MESSAGE 50              /*!<The maximum ammout of characters in the messages*/
#define MAX_PLAYERS 8               /*!<The maximum ammout of players that can play at the same time*/
#define MAX_MISSIONS 10             /*!<The maximum ammount of missions that can be in the game*/

/**
 * @brief This enumeration matches the numerical value of the turn with the player it corresponds to
 * 
 */
typedef enum {
  ALICE_TURN,   /*!<Assigns value '0* to Alice's turn*/
  BOB_TURN      /*!<Assigns value '0* to Bob's turn*/
} TurnByPlayer;

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
 * @brief gets the number of spaces in the game
 * @date 18-04-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return int the number of spaces in the game
 */
int game_get_n_spaces(Game *game);
/**
 * @brief gets the space located in the position of the array of spaces of game
 * @date 18-04-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game 
 * @param pos the position of the space wanted
 * @return Space* the space
 */
Space *game_get_space_in_pos(Game *game, int pos);

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
 * @brief Gets the player of the game in a determinate position asked.
 * @date 18-04-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos int, the position of the player wanted
 * @return Player* a pointer to the player
 */
Player *game_get_player_in_pos(Game *game, int pos);

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
  * @brief returns the character in the position pos of the array of characters in game
  * @date 18/04/25
  * @author Alvaro Inigo
  * @param game a pointer to the game
  * @param pos the position of the character in the array
  * @return Character* the wanted character
  */
Character *game_get_character_in_pos(Game *game, int pos);

/**
  * @brief returns the character id in the position pos of the array of characters in game
  * @date 18/04/25
  * @author Alvaro Inigo
  * @param game a pointer to the game
  * @param position the position of the character in the array
  * @return Character* the wanted character
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
 * @brief Gets the message in the game for the current player
 * @date 04/03/25
 * @author Matteo Artunedo
 * @param game a pointer to game
 * @return a string with the message
 */
char *game_get_message(Game *game);

/**
 * @brief Sets the message in the game for the current player
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
 * @brief gets the id of a link in a given position in the links array
 * @author Guilherme Povedano 
 * @date 25-04-2025
 * @param game pointer to game that stores the data 
 * @param position position int in the array that will be retrieved
*/
Id game_get_link_id_at(Game *game, long position);

/**
 * @brief given a game pointer and a link id, fetches the associated link structure
 * @author Guilherme Povedano 
 * @date 25-04-25
 * @param game pointer to game that stores the data 
 * @param id id of the link to be retrieved 
 */
Link *game_get_link(Game *game, Id id);


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
 * @brief returns the link in the position asked of the array of links in game
 * @date 18/04/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the link wanted
 * @return Link* the link wanted
 */
Link *game_get_link_in_pos(Game *game, int pos);

/**
 * @brief sets the description of an object in the game for the current player
 * @date 24/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param desc the new description of the object
 * @return Status OK or ERROR.
 */
Status game_set_description(Game *game, char *desc);
/**
 * @brief Returns the description of an object in the game for the current player
 * @date 24/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return char* the string that contains the description
 */
char *game_get_description(Game *game);

/**
 * @brief sets objective message in the game for the current player
 * @date 24/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param desc the new objective message
 * @return Status OK or ERROR.
 */
Status game_set_objective(Game *game, char *desc);

/**
 * @brief Returns the objective text in the game for the current player
 * @date 24/03/25
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return char* the string that contains the objective message
 */
char *game_get_objective(Game *game);


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
TurnByPlayer game_get_turn(Game *game);


/**
 * @brief Sets the turn of the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param turn the turn we want to set
 * @return Status OK or ERROR
 */
Status game_set_turn(Game *game, TurnByPlayer turn);
/**
 * @brief returns the number of players in the game
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @return the number of players
 */
int game_get_n_players(Game *game);

/**
 * @brief returns the player of the game with a specific name
 * @author Alvar Inigo
 * @param game a pointer to the game
 * @param name the name of the player
 * @return Player* a pointer to the player whose name is given as argument
 */
Player *game_get_player_from_name(Game *game, char *name);

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

/**
 * @brief moves all of the followers of a player to a new space
 * 
 * @param game pointer to the game
 * @param new_space_id id of the space where the players will move to
 * @return Status: OK or ERROR 
 */
Status game_move_followers(Game *game, Id new_space_id);


/**
 * @brief gets the lastCmd of an interfaceData given its position
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface wanted
 * @return Command the lastCMD
 */
Command *game_interface_in_pos_get_lastCmd(Game *game, int pos);

/**
 * @brief gets the second to last Cmd of an interfaceData given its position
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface wanted
 * @return Command the second to last CMD
 */
Command *game_interface_in_pos_get_second_to_last_Cmd(Game *game, int pos);

/**
 * @brief gets the third to last Cmd of an interfaceData given its position
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface wanted
 * @return Command the third to last CMD
 */
Command *game_interface_in_pos_get_third_to_last_Cmd(Game *game, int pos);

/**
 * @brief gets the message of an interfaceData given its position
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface wanted
 * @return char* the message
 */
char *game_interface_in_pos_get_message(Game *game, int pos);

/**
 * @brief gets the description of an interfaceData given its position
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface wanted
 * @return char* the description
 */
char *game_interface_in_pos_get_description(Game *game, int pos);

/**
 * @brief gets the objective of an interface given its position
 * @author Alvaor Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface wanted
 * @return char* the objective text of the interface
 */
char *game_interface_in_pos_get_objective(Game *game, int pos);

/**
 * @brief sets the message of an interface in a given turn
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface in the game array
 * @param message the new message
 * @return Status  OK or ERROR
 */
Status game_interface_in_pos_set_message(Game *game, int pos, char *message);

/**
 * @brief sets the description of an interface in a given turn
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface in the game array
 * @param desc the new desciption
 * @return Status OK or ERROR
 */
Status game_interface_in_pos_set_description(Game *game, int pos, char *desc);

/**
 * @brief sets the objective text for the interface located in position pos given
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the interface
 * @param desc the new objective message
 * @return Status OK or ERROR
 */
Status game_interface_in_pos_set_objective(Game *game, int pos, char *desc);

/**
 * @brief returns if the message of the game must be shown
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return Bool TRUE if it must be shown of FALSE otherwise
 */
Bool game_get_show_message(Game *game);

/**
 * @brief sets if the message must be shown
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param boolean TRUE or FALSE
 * @return Status OK or ERROR if an error happened
 */
Status game_set_show_message(Game *game, Bool boolean);

/**
 * @brief gets if the message of the player in the turn pos must have its message shown
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the turn of the player
 * @return Bool TRUE or FALSE if the message must or not be shown
 */
Bool game_get_show_message_in_pos(Game *game, int pos);

/**
 * @brief sets if the message of the player in the turn pos must have its message shown
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param boolean the bool to set
 * @param pos the turn of the player
 * @return Bool TRUE or FALSE if the message must or not be shown
 */
Status game_set_show_message_in_pos(Game *game, Bool boolean, int pos);

/**
 * @brief Finds an object from the game by its name.
 * @author Araceli Gutiérrez
 *
 * This function searches through the array of objects in the game and returns
 * the object that matches the given name. If no object with the specified name
 * is found, the function returns NULL.
 *
 * @param game Pointer to the Game structure.
 * @param object_name The name of the object to search for.
 * @return Pointer to the Object if found, otherwise NULL.
 */
Object* game_get_object_from_name(Game *game, char *object_name);

/**
 * @brief Removes an object from the game.
 * @author Araceli Gutiérrez
 *
 * This function searches for the specified object in the game's object array
 * and removes it by replacing it with the last object in the array.
 * The number of objects in the game is then decreased.
 *
 * @param game Pointer to the Game structure.
 * @param object Pointer to the Object to be removed.
 * @return Bool indicating whether the removal was successful (TRUE) or not (FALSE).
 */
Bool game_remove_object(Game *game, Object *object);

/**
 * @brief Finds an object from the game by its name.
 * @author Araceli Gutiérrez
 *
 * This function searches through the array of objects in the game and returns
 * the object that matches the given name. If no object with the specified name
 * is found, the function returns NULL.
 *
 * @param game Pointer to the Game structure.
 * @param object_name The name of the object to search for.
 * @return Pointer to the Object if found, otherwise NULL.
 */
Object* game_get_object_from_name(Game *game, char *object_name);

/**
 * @brief Removes an object from the game.
 * @author Araceli Gutiérrez
 *
 * This function searches for the specified object in the game's object array
 * and removes it by replacing it with the last object in the array.
 * The number of objects in the game is then decreased.
 *
 * @param game Pointer to the Game structure.
 * @param object Pointer to the Object to be removed.
 * @return Bool indicating whether the removal was successful (TRUE) or not (FALSE).
 */
Bool game_remove_object(Game *game, Object *object);

/**
 * @brief sets the lights_on component of game, which determines how the rooms are shown
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @param lights_on boolean value that determines whether the lights are on or off
 * @return Status Ok or ERROR
 */
Status game_set_lights_on(Game *game, Bool lights_on);

/**
 * @brief gets the lights_on value of game
 * @author Matteo Artunedo
 * @param game pointer to game
 * @return Bool: TRUE or FALSE depending on whether the lights are turned on or not
 */
Bool game_get_lights_on(Game *game);


/**
 * @brief sets the current_cinematic component of game, which determines if a cinematic has to be played and which one
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @param current_cinematic boolean value that determines if a cinematic has to be played and which one
 * @return Status Ok or ERROR
 */
Status game_set_current_cinematic(Game *game, Cinematics current_cinematic);

/**
 * @brief gets the current_cinematic value of game, which belongs to the public Cinematics enumeration
 * @author Matteo Artunedo
 * @param game pointer to game
 * @return the cinematic that has to be played or NO_CINEMATIC
 */
Cinematics game_get_current_cinematic(Game *game);


/**
 * @brief Gets a pointer to the Cinematics_text structure which stores the text of the current cinematic
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @return pointer to the structure that stores the cinematic's dialogues
 */
Cinematics_text *game_get_current_cinematic_text(Game *game);

/**
 * @brief gets the cinematicc text in the position wanted of the array in game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the cinematic wanted
 * @return Cinematics_text* the cinematic text selectioned
 */
Cinematics_text *game_get_cinematic_text_in_pos(Game *game, int pos);

/**
 * @brief gets the number of missions in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return int the number of missions in the game
 */
int game_get_n_missions(Game *game);

/**
 * @brief Gets the mission in position pos of the array of missions in game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param pos the position of the mission to look for
 * @return Mission* a pointer to the mission
 */
Mission *game_get_mission_in_pos(Game *game, int pos);


/**
 * @brief gets the current mission code of the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return Mission_Code the code of the current mission
 */
Mission_Code game_get_current_mission_code(Game *game);

/**
 * @brief gets the current mission of the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return Mission* the current mission playing
 */
Mission *game_get_current_mission(Game *game);

/**
 * @brief sets the current mission of the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param mission the mission to be set
 * @return Status OK or ERROR
 */
Status game_set_current_mission(Game *game, Mission_Code mission);

/**
 * @brief adds a new mission in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param mission a pointer to the new mission
 * @return Status OK or ERROR
 */
Status game_add_mission(Game *game, Mission *mission);

/**
 * @brief sets the next objective of the current mission in the game on the message of game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return Status OK or ERROR
 */
Status game_set_next_objective(Game *game);

/**
 * @brief sets the next dialogue line of the current mission in the game on the message of game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @return Status OK or ERROR
 */
Status game_set_next_dialogue(Game *game);
#endif
