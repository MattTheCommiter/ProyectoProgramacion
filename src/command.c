/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Matteo Artunedo
 * @version 0
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGTH 30 /*maximum length of commands written by user*/
#define ARG_LENGTH 30 /*maximum length of object names*/

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, {"d", "Drop"}, {"l", "Left"}, {"r", "Right"}, {"t", "Take"}, {"c", "Chat"}, {"a", "Attack"}, {"i", "Inspect"}};
/**
 * @brief Command
 *
 * This struct stores the code related to a command.
 */
struct _Command
{
  CommandCode code;                 /*!< Name of the command */
  char arg_description[ARG_LENGTH]; /*!< The argument description user in the 'Take' command*/
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
  char input[CMD_LENGTH] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1;

  CommandCode cmd;

  if (!command)
  {
    return ERROR;
  }
  /*read the command entered by the user*/
  if (fgets(input, CMD_LENGTH, stdin))
  {
    token = strtok(input, " \n");
    if (!token)
    {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    /* We verify that the code written by the user corresponds to one of the commands saved in cmd_to_str, whether it is a one-letter code or the full name of the code. */
    /*If either of the comparisons are true, the loop ends and the index 'i' is used to save the chosen command through the command_set_code function*/
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
    if (cmd == TAKE || cmd == INSPECT || cmd == DROP)
    {
      token = strtok(NULL, "\n");

      if (!token)
      {
        command_set_argument(command, NO_ARG);
      }else{
        command_set_argument(command, token);
      }
    }
    else
    {
      command_set_argument(command, NO_ARG);
    }
    return command_set_code(command, cmd);
  }
  else
  {
    fprintf(stdout, "No fgets");
    return command_set_code(command, EXIT);
  }
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