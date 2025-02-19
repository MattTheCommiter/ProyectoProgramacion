/**
 * @file GameReader.h
 * @author Alvaro
 * @brief Declares the public function used in GameReader.c and game.c
 * @version 0.1
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef GameReader_H
#define GameReader_h
#include "types.h"
#include "game.h"

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
Status gameReader_load_spaces(Game **game, char *filename);

#endif