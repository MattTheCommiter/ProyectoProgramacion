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

#define WORD_SIZE 1000 /*Maximum size of words*/
#define NO_ID -1 /*Identification code used for when no id is given*/


/*The Id is neccesary for initialising the player and object*/
typedef long Id;

/**
 * @brief this enumeration is used for the id's of the player and the object
 */
typedef enum
{
    ANT,
    SEED
} Member;

/**
 * @brief assigns a 0 to FALSE and a 1 to TRUE
 */
typedef enum
{
    FALSE,
    TRUE
} Bool;

/**
 * @brief assigns a 0 to ERROR and a 1 to OK
 */
typedef enum
{
    ERROR,
    OK
} Status;

/**
 * @brief assigs a different value to each coordinate
 */
typedef enum
{
    N,
    S,
    E,
    W
} Direction;

#endif
