/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Matteo Artunedo, Alvaro Inigo
 * @version 0
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGTH 100 /*!<maximum length of commands written by user*/
#define ARG_LENGTH 50  /*!<maximum length of object names*/

/**
 * @brief Array mapping command strings to their descriptions.
 */

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"m", "Move"}, {"d", "Drop"}, {"t", "Take"}, {"c", "Chat"}, {"at", "Attack"}, {"i", "Inspect"}, {"r", "Recruit"}, {"ab", "Abandon"}, {"s", "Save"}, {"l", "Load"}, {"tm", "Team"}, {"o", "Open"}, {"u", "Use"}, {"tu", "turn"}, {"g", "Give"}};

/**
 * @brief This struct stores the code related to a command: the command's code, its argument (for take and drop functions) and its success value
 *
 *
 */
struct _Command
{
  CommandCode code;                 /*!< Name of the command */
  char arg_description[ARG_LENGTH]; /*!< The argument description user in the command*/
  char argument2[ARG_LENGTH];       /*!< Second argument (optional in USE command) */
  Status lastcmd_Success;           /*!< Whether the last command was succesful or not*/
};

Command *command_create()
{
  Command *newCommand = NULL;

  newCommand = (Command *)malloc(sizeof(Command));
  if (newCommand == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  newCommand->arg_description[0] = '\0';
  newCommand->argument2[0] = '\0';
  newCommand->lastcmd_Success = OK;
  return newCommand;
}

Status command_destroy(Command *command)
{
  if (!command)
  {
    return ERROR;
  }

  free(command);
  return OK;
}

Status command_set_code(Command *command, CommandCode code)
{
  if (!command)
  {
    return ERROR;
  }

  command->code = code;

  return OK;
}

CommandCode command_get_code(Command *command)
{
  if (!command)
  {
    return NO_CMD;
  }
  return command->code;
}

Status command_get_user_input(Command *command)
{
  char input[CMD_LENGTH] = "", *token = NULL, first_argument[ARG_LENGTH], second_argument[ARG_LENGTH];
  char *aux = NULL, *sep = NULL, input_cpy[CMD_LENGTH];
  int i = UNKNOWN - NO_CMD + 1;

  CommandCode cmd;

  if (!command)
    return ERROR;

  if (fgets(input, CMD_LENGTH, stdin) == NULL)
  {
    return command_set_code(command, EXIT);
  }

  memcpy(input_cpy, input, CMD_LENGTH);

  token = strtok(input, " \r\n");
  if (!token)
    return command_set_code(command, UNKNOWN);

  cmd = UNKNOWN;

  while (cmd == UNKNOWN && i < N_CMD)
  {
    if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
    {
      cmd = i + NO_CMD;
    }
    else
    {
      i++;
    }
  }

  switch (cmd)
  {
  /* commands that only expect one argument */
  case TAKE:
  case DROP:
  case CHAT:
  case SAVE:
  case LOAD:
  case MOVE:
  case ATTACK:
  case INSPECT:
  case RECRUIT:
  case TEAM:
  case ABANDON:
  {
    /* copy of the input buffer needed because strtok modifies the input string to have a NULL character before the buffer's end */
    if (strlen(token) == strlen(input_cpy))
    {
      command_set_argument(command, NO_ARG);
      break;
    }

    /* pointer to the first word after the command token */
    aux = input + strlen(token) + 1;

    /* truncate command argument if necessary - will likely casue a action error in game_actions module */
    if (strlen(aux) >= ARG_LENGTH)
    {
      strncpy(first_argument, aux, ARG_LENGTH - 1);
      first_argument[ARG_LENGTH - 1] = '\0';
    }
    else
    {
      strcpy(first_argument, aux);
      first_argument[strlen(aux) - 1] = '\0';
    }

    command_set_argument(command, first_argument);
    command_set_argument2(command, NO_ARG);

    break;
  }
  case OPEN:
  case USE:
  case GIVE:
  {
    if (cmd == GIVE)
      sep = GIVE_ARG;
    if (cmd == OPEN)
      sep = OPEN_ARG;
    if (cmd == USE)
      sep = USE_ARG;

    /* keyword is not found */
    if (strstr(input_cpy, sep) == NULL && cmd != USE)
    {
      command_set_argument(command, NO_ARG);
      command_set_argument2(command, NO_ARG);
      break;
    }
    else if (cmd == USE && strstr(input_cpy, sep) == NULL)
    {
      /* handle explicitly case where use is called without second argument */

      /* start of first word after command token */
      aux = input + strlen(token) + 1;

      /* truncate if necessary */
      if (strlen(aux) >= ARG_LENGTH)
      {
        strncpy(first_argument, aux, ARG_LENGTH - 1);
        first_argument[ARG_LENGTH - 1] = '\0';
      }
      else
      {
        strcpy(first_argument, aux);
        first_argument[strlen(aux) - 1] = '\0';
      }

      /* assign both arguments, second arg is empty */
      command_set_argument(command, first_argument);
      command_set_argument2(command, NO_ARG);

      /* exit switch statement */
      break;
    }

    /* second argument of the command */
    aux = strstr(input_cpy, sep) + strlen(sep);

    /* no second argument is given */
    if (aux + strlen(aux) - 1 == input + strlen(input) - 1) /* avoid out of bounds access with -1 */
    {
      command_set_argument(command, NO_ARG);
      command_set_argument2(command, NO_ARG);
      break;
    }

    /* truncate second argument if necessary */
    if (strlen(aux) >= ARG_LENGTH)
    {
      strncpy(second_argument, aux, ARG_LENGTH - 1);
      second_argument[ARG_LENGTH - 1] = '\0';
    }
    else
    {
      strcpy(second_argument, aux);
      second_argument[strlen(aux) - 1] = '\0';
    }

    /* assign second argument */
    command_set_argument2(command, second_argument);

    /* null-terminate first argument for easier function calls */
    aux = strstr(input_cpy, sep);
    *aux = '\0';

    /* start of the first word after command token */
    aux = input_cpy + strlen(token) + 1;

    /* truncate if necessary */
    if (strlen(aux) >= ARG_LENGTH)
    {
      strncpy(first_argument, aux, ARG_LENGTH - 1);
      first_argument[ARG_LENGTH - 1] = '\0';
    }
    else
    {
      strncpy(first_argument, aux, strlen(aux) + 1);
      first_argument[strlen(aux)] = '\0';
    }

    /* assign first argument as well */
    command_set_argument(command, first_argument);

    /* exit switch statement */
    break;
  }
  default:
  {
    /* no argument expected */
    command_set_argument(command, NO_ARG);
    command_set_argument2(command, NO_ARG);
    break;
  }
  }

  return command_set_code(command, cmd);
}

char *command_get_argument(Command *command)
{
  if (!command)
    return NO_ARG;
  return command->arg_description;
}

Status command_set_argument(Command *command, char *argument_desc)
{
  if (!command)
    return ERROR;
  if (argument_desc == NO_ARG)
  {
    command->arg_description[0] = '\0';
    return OK;
  }
  strcpy(command->arg_description, argument_desc);

  return OK;
}

char *command_get_argument2(Command *command)
{
  if (!command)
  {
    return NO_ARG;
  }
  return command->argument2;
}

Status command_set_argument2(Command *command, char *argument_desc)
{
  if (!command)
    return ERROR;
  if (argument_desc == NO_ARG)
  {
    command->argument2[0] = '\0';
    return OK;
  }
  strcpy(command->argument2, argument_desc);

  return OK;
}

Status command_set_lastcmd_success(Command *command, Status lastcmd_success)
{
  if (!command)
  {
    return ERROR;
  }
  command->lastcmd_Success = lastcmd_success;
  return OK;
}

Status command_get_lastcmd_success(Command *command)
{
  if (!command)
  {
    return ERROR;
  }
  return command->lastcmd_Success;
}

Bool command_get_confirmation()
{
  char input[CMD_LENGTH];
  while (!fgets(input, MAX_CMD_ARG, stdin) || (strcasecmp(input, "N\n") && strcasecmp(input, "Y\n")))
    ;

  if (!strcasecmp(input, "N\n"))
    return FALSE;
  if (!strcasecmp(input, "Y\n"))
    return TRUE;

  return FALSE;
}