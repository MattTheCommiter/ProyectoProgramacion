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

#define N_CMDT 2
#define N_CMD 7

typedef enum
{
    CMDS,
    CMDL
} CommandType;

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
 * @brief dynamically allocated memory for the command and sets its code to NO_CMD
 *
 * @return Command* pointer to the dynamically allocated Command structure
 */
Command *command_create();

/**
 * @brief frees the memory reserved for the command pointer
 *
 * @param command pointer to the command structure that is to be freed
 * @return Status: if the function was completed succesfully
 */
Status command_destroy(Command *command);

/**
 * @brief sets the code of a command structure to a desired code
 *
 * @param command the structure that is to be changed
 * @param code the new code for the structure
 * @return Status: if the function was completed succesfully
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief returns the code of the command structure
 *
 * @param command pointer to the structure
 * @return CommandCode: the structure's command
 */
CommandCode command_get_code(Command *command);

/**
 * @brief reads the user's input and changes the command to the one entered
 *
 * @param command pointer to the command structure
 * @return Status: calls to the command_set_code function to change the code to the one entered by the user
 */
Status command_get_user_input(Command *command);

#endif
