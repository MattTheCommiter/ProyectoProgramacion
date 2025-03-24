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

#define WORD_SIZE 1000 /*!<Maximum size of words*/
#define NO_ID -1       /*!<Identification code used for when no id is given*/
#define NO_HP -1       /*!<Identification for the hp when it is not given*/

/*The Id is neccesary for initialising the player and object*/
typedef long Id;

/**
 * @brief this enumeration is used for the id's of the player and the object
 */
typedef enum
{
    ANT1 ,       /*!<Corresponds to the ID assigned to the first player*/
    ANT2 ,       /*!<Corresponds to the ID assigned to the second player*/
    SPIDER,     /*!<Corresponds to the ID assigned to the spider*/
    ANT_FRIEND  /*!<Corresponds to the ID assigned to the ant friend*/
} Member;

/**
 * @brief assigns a 0 to FALSE and a 1 to TRUE
 */
typedef enum
{
    FALSE,  /*!<Value 0, which corresponds to the logical value FALSE*/
    TRUE    /*!<Value 1, which corresponds to the logical value TRUE*/
} Bool;

/**
 * @brief assigns a 0 to ERROR and a 1 to OK
 */
typedef enum
{
    ERROR,  /*!<Assigns 0 to the keyword "FALSE", which will be used as a return in functions*/
    OK      /*!<Assigns 1 to the keyword "TRUE", which will be used as a return in functions*/
} Status;

/**
 * @brief assigs a different value to each coordinate
 */
typedef enum
{
    UNKNOWN_DIR,    /*!<Assigns value 0 to the keyword "UNKNOWN_DIR", which will be used in space-related functions*/
    N,          /*!<Assigns value 1 to the keyword "N", which will be used in space-related functions*/      
    S,          /*!<Assigns value 2 to the keyword "S", which will be used in space-related functions*/
    E,          /*!<Assigns value 3 to the keyword "E", which will be used in space-related functions*/
    W           /*!<Assigns value 4 to the keyword "W", which will be used in space-related functions*/
} Direction;

#endif
