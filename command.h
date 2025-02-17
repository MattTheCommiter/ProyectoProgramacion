/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2 /*Number of ways the user can type each command (non-case sensitive)*/
#define N_CMD 7  /*Number of commands that are possible*/

/**
 * @brief Enumeration of the two possible ways the user can introduce a command
 */
typedef enum
{
    CMDS, /*Corresponds to a one-letter code used to identify the command*/
    CMDL  /*Corresponds to the command's full name*/
} CommandType;

/**
 * @brief Enumeration with all the possible commands
 */
typedef enum
{
    NO_CMD = -1,
    UNKNOWN,
    EXIT,
    NEXT,
    BACK,
    TAKE,
    DROP
} CommandCode;

typedef struct _Command Command;

/**
 * @brief dynamically allocates memory for the command and sets its code to NO_CMD
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @return Command*: pointer to the dynamically allocated Command structure
 */
Command *command_create();

/**
 * @brief frees the memory reserved for the command pointer
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param command pointer to the Command structure that is to be freed
 * @return Status: whether the function was completed succesfully
 */
Status command_destroy(Command *command);

/**
 * @brief sets the code of a command structure to a desired code
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param command pointer to the Command structure that will be changed
 * @param code the new code for the structure
 * @return Status: whether the function was completed succesfully
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief returns the code of the command structure
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param command pointer to the Command structure
 * @return CommandCode: the structure's command
 */
CommandCode command_get_code(Command *command);

/**
 * @brief reads the user's input and changes the command to the one entered
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param command pointer to the command structure
 * @return Status: calls to the command_set_code function to change the code to the one entered by the user
 */
Status command_get_user_input(Command *command);

#endif
