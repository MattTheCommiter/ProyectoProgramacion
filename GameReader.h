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

Status gameReader_load_spaces(Game *game, char *filename);


#endif