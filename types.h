/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0.1
 * @date 12-02-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;
/*The Id's neccesary to initialise the player and object*/
typedef enum
{
    ANT,
    SEED
} Member;
typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef enum
{
    ERROR,
    OK
} Status;

typedef enum
{
    N,
    S,
    E,
    W
} Direction;

#endif
