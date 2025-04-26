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

#define CMD_LENGTH 50 /*!<maximum length of commands written by user*/
#define ARG_LENGTH 50 /*!<maximum length of object names*/

/**
 * @brief Array mapping command strings to their descriptions.
 */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"m", "Move"}, {"d", "Drop"}, {"t", "Take"}, {"c", "Chat"}, {"at", "Attack"}, {"i", "Inspect"}, {"r", "Recruit"}, {"ab", "Abandon"}, {"s", "Save"}, {"l", "Load"}, {"tm", "Team"}, {"u", "Use"}};

/**
 * @brief This struct stores the code related to a command: the command's code, its argument (for take and drop functions) and its success value
 *
 *
 */
struct _Command
{
  CommandCode code;                 /*!< Name of the command */
  char arg_description[ARG_LENGTH]; /*!< The argument description user in the 'Take' command*/
  char argument2[WORD_SIZE];        /*!< Second argument (optional in USE command) */
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
    token = strtok(input, " \r\n");
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

    /* first argument for all commands */
    if (cmd == TAKE || cmd == INSPECT || cmd == DROP || cmd == MOVE || cmd == RECRUIT || cmd == ABANDON || cmd == CHAT || cmd == ATTACK || cmd == SAVE || cmd == LOAD || cmd == TEAM || cmd == USE)
    {
      token = strtok(NULL, " \r\n");
      if (token)
      {
        command_set_argument(command, token);
      }
      else
      {
        command_set_argument(command, NO_ARG);
      }
    }
    else
    {
      command_set_argument(command, NO_ARG);
    }

    /* second argument specifically for the USE command */
    if (cmd == USE)
    {
      token = strtok(NULL, " \r\n");
      if (token && !strcasecmp(token, "over"))
      {
        token = strtok(NULL, "\r\n");
        if (token)
        {
          command_set_argument2(command, token);
        }
        else
        {
          command_set_argument2(command, NO_ARG);
        }
      }
      else
      {
        command_set_argument2(command, NO_ARG);
      }
    }
    else
    {
      command_set_argument2(command, NO_ARG);
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