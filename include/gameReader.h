/**
 * @brief Provides functions to load game data from text files.
 * 
 * @file gameReader.h
 * @author Alvaro
 * @version 1.3
 * @date 2025-02-08
 * @copyright Copyright (c) 2025
 */

#ifndef GameReader_H
#define GameReader_H

#include "types.h"
#include "game.h"
#include "player.h"
#include "character.h"
#include "object.h"
#include "link.h"

/*declaration of public functions*/

/**
 * @brief creates a new space from the text of a file, the text must be in a specific format, separated by '|'
 * gets all the information needed to create a new space.
 *
 * @date 10-02-2025
 * @author Álvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @param filename the name of the text file
 * @return Status: if the function was completed succesfully
 */
Status gameReader_load_spaces(Game *game, char *filename);

/**
 * @brief Creates the objects given the data file given a specific format.
 *
 * @date 7-03-2025
 * @author Álvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 * @param filename the name of the text file
 * @return Status: if the function was completed succesfully
 */
Status gameReader_load_objects(Game *game, char *filename);

/**
 * @brief Creates the players given the data file from a specific format
 * @date 24-03-2025
 * @author Álvaro Inigo
 * @param game a pointer to game
 * @param filename the name of the text file
 * @return Status OK of ERROR
 */
Status gameReader_load_players(Game *game, char *filename);

/**
 * @brief Creates the characters given the data file from a specific format
 * @date 24-03-2025
 * @author Álvaro Inigo
 * @param game a pointer to game
 * @param filename the name of the text file
 * @return Status OK of ERROR
 */
Status gameReader_load_characters(Game *game, char *filename);

/**
 * @brief Creates the links given the data file from a specific format
 * @date 25-03-2025
 * @author Álvaro Inigo
 * @param game a pointer to game
 * @param filename the name of the text file
 * @return Status OK of ERROR
 */
Status gameReader_load_links(Game *game, char *filename);

#endif