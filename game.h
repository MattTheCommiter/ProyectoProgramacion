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

#define MAX_SPACES 100

typedef struct _Game {
  Id player_location;
  Id object_location;
  Space *spaces[MAX_SPACES];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
} Game;

/**
 * @brief Dynamically allocates memory for the game and initializes all the structures components 
 * 
 * @param game a pointer to the structure with the game's main information
 * @return Status: if the function was completed succesfully
 */
Status game_create(Game *game);

/**
 * @brief creates the game calling game_create and reads a text file to get information about the spaces
 * 
 * @param game pointer to the structure with the game's main information
 * @param filename 
 * @return Status: if the function was completed succesfully
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief frees all the dynamically allocated memory in the game structure
 * 
 * @param game a pointer to the structure with the game's main information
 * @return Status: if the function was completed succesfully
 */
Status game_destroy(Game *game);

/**
 * @brief returns a pointer to the space that has the id passed as an argument
 * 
 * @param game a pointer to the structure with the game's main information
 * @param id the id of the desired space
 * @return a pointer to the desired space
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief returns the id of the player's location
 * 
 * @param game a pointer to the structure with the game's main information
 * @return the id of the player's location
 */
Id game_get_player_location(Game *game);

/**
 * @brief changes the id of the player's location to the one passed as an argument
 * 
 * @param game a pointer to the structure with the game's main information
 * @param id the id of the new location
 * @return Status: if the function was completed succesfully
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief returns the id of the object's location
 * 
 * @param game a pointer to the structure with the game's main information
 * @return the id of the object's location
 */
Id game_get_object_location(Game *game);

/**
 * @brief changes the id of the object's location to the one passed as an argument
 * 
 * @param game a pointer to the structure with the game's main information
 * @param id the id of the new location
 * @return Status 
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief returns the last command of the game
 * 
 * @param game a pointer to the structure with the game's main information
 * @return a pointer to the last command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief changes the game's last_cmd parameter to a pointer to a new last_cmd
 * 
 * @param game a pointer to the structure with the game's main information
 * @param command the new last_cmd
 * @return Status: if the function was completed succesfully
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief returns a boolean value that describes if the game has finished or not
 * 
 * @param game a pointer to the structure with the game's main information
 * @return Bool (TRUE or FALSE) that describes if the game is finished or not
 */
Bool game_get_finished(Game *game);

/**
 * @brief Changes the state of the game, starting or finishing it
 * 
 * @param game a pointer to the structure with the game's main information
 * @param finished the new boolean value that describes whether the game has finished or not
 * @return Status if the function has been completed succesfully
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief prints the id of the player's location, the object's location and prints the information regarding all the spaces in the game
 * 
 * @param game a pointer to the structure with the game's main information
 */
void game_print(Game *game);

#endif
