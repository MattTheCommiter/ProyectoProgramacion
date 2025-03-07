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

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, {"d", "Drop"}, {"l", "Left"}, {"r", "Right"}, {"t", "Take"}, {"c", "Chat"},{"a", "Attack"}};
char *arg_to_str[N_OBJECTS][N_CMDT] = {{"s", "seed"}, {"g", "grain"}, {"c", "crumb"}, {"l", "leaf"}};
/**
 * @brief Command
 *
 * This struct stores the code related to a command.
 */
struct _Command
{
  CommandCode code; /*!< Name of the command */
  ArgumentCode arg;
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
  char input[CMD_LENGTH] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1, j = NO_ARG + 1;
  
  CommandCode cmd;
  ArgumentCode arg = NO_ARG;

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
    if (cmd == TAKE)
    {
      token = strtok(NULL, "\n");
      while(arg==NO_ARG && j < N_OBJECTS){
        if(!strcasecmp(token, arg_to_str[j][CMDS]) || !strcasecmp(token, arg_to_str[j][CMDL])){
          arg = j;
        }
        else
        {
          j++;
        }
      }

      /*
      if(!strcasecmp(token, "Seed")){
        arg=SEED;
      }else if(!strcasecmp(token, "Crumb")){
        arg=CRUMB;
      }else if(!strcasecmp(token, "Grain")){
        arg=GRAIN;
      }else if(!strcasecmp(token, "Leaf")){
        arg=LEAF;
      }*/
      command_set_argument(command, arg);
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

/* We verify that the code written by the user corresponds to one of the commands saved in cmd_to_str, whether it is a one-letter code or the full name of the code. */
/*If either of the comparisons are true, the loop ends and the index 'i' is used to save the chosen command through the command_set_code function*/
ArgumentCode command_get_argument(Command *command)
{
  if (!command)
    return NO_ARG;
  return command->arg;
}

Status command_set_argument(Command *command, ArgumentCode arg)
{
  if (!command)
    return ERROR;
  command->arg = arg;
  return OK;
}