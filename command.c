/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 30

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, {"t", "Take"}, {"d", "Drop"}};

struct _Command
{
  CommandCode code; /*!< Name of the command */
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
  char input[CMD_LENGHT] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command)
  {
    return ERROR;
  }
  /*read the command entered by the user*/
  if (fgets(input, CMD_LENGHT, stdin))
  {
    token = strtok(input, " \n");
    if (!token)
    {
      return command_set_code(command, UNKNOWN); 
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD)
    { /* We verify that the code written by the user corresponds to one of the commands saved in cmd_to_str, whether it is a one-letter code or the full name of the code. */
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) /*If either of the comparisons are true, the loop ends and the index 'i' is used to save the chosen command through the command_set_code function*/
      {
        cmd = i + NO_CMD;
      }
      else
      {
        i++;
      }
    }
    return command_set_code(command, cmd);
  }
  else
    return command_set_code(command, EXIT);
}
