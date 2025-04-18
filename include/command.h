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

#define N_CMDT 2       /*!< Number of ways the user can type each command (non-case sensitive)*/
#define N_CMD 11       /*!< Number of commands that are possible*/
#define MAX_CMD_ARG 20 /*!< Maximum number of characters in the argument parameter of the command*/
#define NO_ARG NULL    /*!< the pointer defined for no argument*/

/**
 * @brief Enumeration of the two possible ways the user can introduce a command
 */
typedef enum
{
    CMDS, /*!<Corresponds to a one-letter code used to identify the command*/
    CMDL  /*!<Corresponds to the command's full name*/
} CommandType;

/**
 * @brief Enumeration with all the possible commands
 */
typedef enum
{
    NO_CMD = -1, /*!<Assigs -1 to the keyword "NO_CMD", which will be used in command-related functions*/
    UNKNOWN,     /*!<Assigs 0 to the keyword "UNKNOWN", which will be used in command-related functions*/
    EXIT,        /*!<Assigs 1 to the keyword "EXIT", which will be used in command-related functions*/
    MOVE,        /*!<Assigs 2 to the keyword "NEXT", which will be used in command-related functions*/
    DROP,        /*!<Assigs 3 to the keyword "DROP", which will be used in command-related functions*/
    TAKE,        /*!<Assigs 4 to the keyword "TAKE", which represents taking the an object*/
    CHAT,        /*!<Assigs 5 to the keyword "CHAT", which will be used in command-related functions*/
    ATTACK,      /*!<Assigs 6 to the keyword "ATTACK", which will be used in command-related functions*/
    INSPECT,     /*!<Assigs 7 to the keyword "INSPECT", which will be used in command-related functions*/
    RECRUIT,     /*!<Assigs 8 to the keyword "RECRUIT", which will be used in command-related functions*/
    ABANDON      /*!<Assigs 9 to the keyword "ABANDON", which will be used in command-related functions*/
} CommandCode;

/**
 * @brief Defines a new type for the Command structure.
 */
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

/**
 * @brief sets the argument parameter of the command
 *
 * @param command pointer to the command
 * @param arg code of the new argument
 * @return Status: whether the function was completed succesfully
 */
Status command_set_argument(Command *command, char *arg);

/**
 * @brief gets the argument parameter of the command
 * @author Matteo Artuñedo
 * @param command pointer to the command
 * @return code with the command argument or NO_CMD if an error occurrs
 */
char *command_get_argument(Command *command);


/**
 * @brief sets either the last command was successful or not.
 * @author Alvaro Inigo
 * @param command pointer to the command
 * @param lastcmd_success status variable: OK or ERROR
 * @return Status, OK if everything went right or ERROR
 */
Status command_set_lastcmd_success(Command *command, Status lastcmd_success);


/**
 * @brief gets the success parameter of the command
 * @author Alvaro Inigo
 * @param command pointer to the command
 * @return Status code, OK or ERROR
 */
Status command_get_lastcmd_success(Command *command);
#endif
