/**
 * @brief creates a textual graphic engine for the game
 * @file gameManagement.c
 * @author Alvaro Inigo
 * @version 0.2
 * @date 2025-03-014
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "gameManagement.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*Declaration of private functions*/

/**
 * @brief Saves in a file all the information about the objects in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_objects(Game *game, FILE *saving_file);

/**
 * @brief Saves in a file all the information about the players in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_players(Game *game, FILE *saving_file);

/**
 * @brief Saves in a file the turn of the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_turn(Game *game, FILE *saving_file);

/**
 * @brief Saves in a file all the information about the spaces in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_spaces(Game *game, FILE *saving_file);

/**
 * @brief Saves in a file all the information about the characters in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_characters(Game *game, FILE *saving_file);

/**
 * @brief Saves in a file all the information about the links in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_links(Game *game, FILE *saving_file);

/**
 * @brief Saves in a file all the information about the interface in the game
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param saving_file the file we want to write
 * @return Status OK or ERROR
 */
Status gameManagement_save_interface(Game *game, FILE *saving_file);

Status gameManagement_load_turn(Game *game, char *filename);
Status gameManagement_load_interface(Game *game, char *filename);

/*End of private functions*/

Status gameManagement_load_spaces(Game *game, char *filename)
{
  /*#s:11|Entry| _ | ___ | mo'_| @ _ | __/ __|*/
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char **read_gdesc;
  char *toks = NULL;
  int i;
  Id id;
  Space *space = NULL;
  Status status = OK;

  if (!filename || !game)
  {
    return ERROR;
  }

  if (!(read_gdesc = (char **)calloc(N_LINES_IN_GDESC, sizeof(char *))))
  {
    return ERROR;
  }
  if (!(read_gdesc[0] = (char *)calloc(N_LINES_IN_GDESC * (N_ROWS_IN_GDESC + 1), sizeof(char))))
  {
    free(read_gdesc);
    return ERROR;
  }
  for (i = 1; i < 5; i++)
  {
    read_gdesc[i] = read_gdesc[0] + (N_ROWS_IN_GDESC + 1) * i;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * reads the file and loads each data individually.
   */

  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#s:", line, 3) == 0)
    /*#s:11|Entry| _ | ___ | mo'_| @ _ | __/ __|*/
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      /*Si hay una descripción gráfica, la leemos y la copiamos a nuetra matriz read_gdesc*/
      if ((toks = strtok(NULL, "|\n\r")) != NULL)
      {
        strcpy(read_gdesc[0], toks);
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[1], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[2], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[3], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[4], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
      }
      else
      {
        /*Si no hay una descripción gráfica, copiamos espacios en blanco a la descripción del espacio*/
        strcpy(read_gdesc[0], "         ");
        strcpy(read_gdesc[1], "         ");
        strcpy(read_gdesc[2], "         ");
        strcpy(read_gdesc[3], "         ");
        strcpy(read_gdesc[4], "         ");
      }

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      /*
       * It creates the space with the data that has been read
       */
      space = space_create(id); /*calls to space_create providing the id written in the file*/
      if (space != NULL)
      { /*Sets the information related to the space and adds it to the game*/
        space_set_name(space, name);
        game_add_space(game, space);
        space_set_gdesc(space, read_gdesc);
      }
      else
      {
        fclose(file);
        free(read_gdesc[0]);
        free(read_gdesc);
        return ERROR;
      }
    }
  }
  free(read_gdesc[0]);
  free(read_gdesc);
  if (ferror(file) || space == NULL)
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status gameManagement_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, spaceId = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * reads the file and loads each data individually.
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      spaceId = atol(toks);
      toks = strtok(NULL, "|\n\r");
      strcpy(description, toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, spaceId);
#endif
      /*
       * It creates the space with the data that has been read
       */
      object = object_create(id); /*calls to object_create providing the id written in the file*/
      if (object != NULL)
      { /*Sets the information related to the object and adds it to the game*/
        object_set_name(object, name);
        object_set_description(object, description);
        space_add_objectId(game_get_space(game, spaceId), id);
        game_add_object(game, object);
      }
    }
  }

  if (ferror(file) || object == NULL)
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status gameManagement_load_players(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESCTAM] = "";
  char *toks = NULL;
  Id id = NO_ID, spaceId = NO_ID;
  Player *player = NULL;
  Status status = OK;
  int hp = 0;
  int inventory_size = 0;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * reads the file and loads each data individually.
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|\r\n");
      id = atol(toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(name, toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|\r\n");
      spaceId = atol(toks);
      toks = strtok(NULL, "|\r\n");
      hp = atoi(toks);
      toks = strtok(NULL, "|\n\r");
      inventory_size = atoi(toks);

/*
#p: id|name|GDESC|idSpace|HP|INVENTORY|
*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%s|%ld|%d|%d|\n", id, name, gdesc, spaceId, hp, inventory_size);
#endif

      /*
       * It creates the player with the data that has been read
       */
      player = player_create(id, inventory_size); /*calls to player_create providing the id written in the file*/
      if (player != NULL)
      { /*Sets the information related to the object and adds it to the game*/
        player_set_name(player, name);
        player_set_gdesc(player, gdesc);
        player_set_location(player, spaceId);
        space_set_discovered(game_get_space(game, spaceId), TRUE);
        player_set_health(player, hp);
        game_add_player(game, player);
      }
    }
  }

  if (ferror(file) || !player)
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status gameManagement_load_characters(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESCTAM] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, spaceId = NO_ID;
  Character *character = NULL;
  Status status = OK;
  int hp = 0;
  Bool friendliness = FALSE;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * reads the file and loads each data individually.
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#c:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|\r\n");
      id = atol(toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(name, toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|\r\n");
      spaceId = atol(toks);
      toks = strtok(NULL, "|\r\n");
      hp = atoi(toks);
      toks = strtok(NULL, "|\r\n");
      friendliness = atoi(toks);
      toks = strtok(NULL, "|\r");
      strcpy(message, toks);

      /*
      #c:3|ant friend|    ^0m|122|5|0|Hey ant friend!
      */

#ifdef DEBUG
      printf("Leido: %ld|%s|%s|%ld|%d|%d|%s|\n", id, name, gdesc, spaceId, hp, friendliness, message);
#endif

      /*
       * It creates the character with the data that has been read
       */
      character = character_create(id); /*calls to character_create providing the id written in the file*/
      if (character != NULL)
      { /*Sets the information related to the character and adds it to the game*/
        character_set_name(character, name);
        character_set_gdesc(character, gdesc);
        space_add_character(game_get_space(game, spaceId), id);
        character_set_location(character, spaceId);
        character_set_health(character, hp);
        character_set_message(character, message);
        character_set_friendly(character, friendliness);
        game_add_character(game, character);
      }
    }
  }

  if (ferror(file) || character == NULL)
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status gameManagement_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  Status status = OK;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  Link *link = NULL;
  Id id = NO_ID;
  char name[WORD_SIZE] = "";
  Id idOrigin = NO_ID, idDest = NO_ID;
  Direction direccion = UNKNOWN_DIR;
  Bool open = FALSE;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * reads the file and loads each data individually.
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    /*#l:31|Entry|11|121|1|1| Id,Nombre,Idsalida,Iddest,direccion,open*/
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|\r\n");
      id = atol(toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(name, toks);
      toks = strtok(NULL, "|\r\n");
      idOrigin = atol(toks);
      toks = strtok(NULL, "|\r\n");
      idDest = atol(toks);
      toks = strtok(NULL, "|\r\n");
      direccion = atol(toks);
      toks = strtok(NULL, "|\r\n");
      open = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%d|%d|\n", id, name, idOrigin, idDest, direccion, open);
#endif

      /*
       * It creates the link with the data that has been read
       */
      link = link_create(id); /*calls to link_create providing the id written in the file*/
      if (link != NULL)
      { /*Sets the information related to the link and adds it to the game*/
        link_set_name(link, name);
        link_set_origin_id(link, idOrigin);
        link_set_destination_id(link, idDest);
        link_set_direction(link, direccion);
        link_set_is_open(link, open);
        if (!(game_add_link(game, link)))
        {
          link_destroy(link);
          return ERROR;
        }
      }
    }
  }

  if (ferror(file) || !link)
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status gameManagement_save(Game *game, char *filename)
{
  FILE *save = NULL;
  if (!game || !filename)
    return ERROR;
  save = fopen(filename, "w");

  if (!save)
    return ERROR;

  /*Ahora vamos a escribir todos los datos del juego en el fichero de texto*/

  if (!gameManagement_save_objects(game, save) || !gameManagement_save_players(game, save) || !gameManagement_save_turn(game, save) || !gameManagement_save_spaces(game, save) || !gameManagement_save_characters(game, save) || !gameManagement_save_links(game, save) || !gameManagement_save_interface(game, save))
  {
    fclose(save);
    return ERROR;
  }

  fclose(save);
  return OK;
}

Status gameManagement_load(Game *game, char *filename)
{
  if (!game || !filename)
    return ERROR;

  /*Reiniciamos el juego, liberando el anterior juego y cargando uno con los datos proporcionados*/

  if (game_destroy(game) == ERROR)
  {
    return ERROR;
  }
  if (game_create_from_file(&game, filename) == ERROR)
  {
    return ERROR;
  }
  if(gameManagement_load_turn(game, filename) == ERROR){
    return ERROR;
  }
  if(gameManagement_load_interface(game, filename) == ERROR){
    return ERROR;
  }

  return OK;
}

/*Implementation of private functions*/

Status gameManagement_save_objects(Game *game, FILE *saving_file)
{
  int i;
  Object *object = NULL;
  if (!game || !saving_file)
    return ERROR;

  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object = game_get_object_in_pos(game, i);
    fprintf(saving_file, "#o:%ld|%s|%ld|%s|\n", object_get_id(object), object_get_name(object), game_get_object_location(game, object_get_id(object)), object_get_description(object));
  }

  return OK;
}
Status gameManagement_save_players(Game *game, FILE *saving_file)
{
  int i;
  Player *player = NULL;

  if (!game || !saving_file)
    return ERROR;

  for (i = 0; i < game_get_n_players(game); i++)
  {
    player = game_get_player_in_pos(game, i);
    fprintf(saving_file, "#p:%ld|%s|%s|%ld|%d|%d|\n", player_get_id(player), player_get_name(player), player_get_gdesc(player), player_get_location(player), player_get_health(player), inventory_get_max_objs(player_get_inventory(player)));
  }

  return OK;
}

Status gameManagement_save_turn(Game *game, FILE *saving_file)
{
  if (!game || !saving_file)
    return ERROR;

  fprintf(saving_file, "#t:%d", game_get_turn(game));

  return OK;
}
Status gameManagement_save_spaces(Game *game, FILE *saving_file)
{
  int i;
  Space *space = NULL;
  char **gdesc = NULL;

  if (!game || !saving_file)
    return ERROR;
  for (i = 0; i < game_get_n_spaces(game); i++)
  {

    space = game_get_space_in_pos(game, i);
    gdesc = space_get_gdesc(space);
    fprintf(saving_file, "#s:%ld|%s|%s|%s|%s|%s|%s|\n", space_get_id(space), space_get_name(space), gdesc[0], gdesc[1], gdesc[2], gdesc[3], gdesc[4]);
  }

  return OK;
}
Status gameManagement_save_characters(Game *game, FILE *saving_file)
{
  int i;
  Character *character = NULL;
  if (!game || !saving_file)
    return ERROR;

  for (i = 0; i < game_get_n_characters(game); i++)
  {
    character = game_get_character_in_pos(game, i);
    fprintf(saving_file, "#c:%ld|%s|%s|%ld|%d|%d|%s|\n", character_get_id(character), character_get_name(character), character_get_gdesc(character), character_get_location(character), character_get_health(character), character_get_friendly(character), character_get_message(character));
  }

  return OK;
}
Status gameManagement_save_links(Game *game, FILE *saving_file)
{
  int i;
  Link *link = NULL;

  if (!game || !saving_file)
    return ERROR;

  for (i = 0; i < game_get_n_links(game); i++)
  {
    link = game_get_link_in_pos(game, i);
    fprintf(saving_file, "#l:%ld|%s|%ld|%ld|%d|%d|\n", link_get_id(link), link_get_name(link), link_get_origin_id(link), link_get_destination_id(link), link_get_direction(link), link_get_is_open(link));
  }

  return OK;
}
Status gameManagement_save_interface(Game *game, FILE *saving_file)
{
  int i;
  Command *lastCmd = NULL, *second_to_last = NULL, *third_to_last = NULL;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char *lastCmdName = NULL, *second_to_lastName = NULL, *third_to_lastName = NULL;
  CommandCode lastCmdCode, second_to_lastCode, third_to_lastCode;

  if (!game || !saving_file)
    return ERROR;

  for (i = 0; i < game_get_n_players(game); i++)
  {

    lastCmd = game_interface_in_pos_get_lastCmd(game, i);
    second_to_last = game_interface_in_pos_get_second_to_last_Cmd(game, i);
    third_to_last = game_interface_in_pos_get_third_to_last_Cmd(game, i);

    lastCmdName = cmd_to_str[command_get_code(lastCmd) - NO_CMD][CMDL];
    second_to_lastName = cmd_to_str[command_get_code(second_to_last) - NO_CMD][CMDL];
    third_to_lastName = cmd_to_str[command_get_code(third_to_last) - NO_CMD][CMDL];

    lastCmdCode = command_get_code(lastCmd);
    second_to_lastCode = command_get_code(second_to_last);
    third_to_lastCode = command_get_code(third_to_last);

    fprintf(saving_file, "#i:%d", i);
    if (lastCmdCode == TAKE || lastCmdCode == INSPECT || lastCmdCode == DROP || lastCmdCode == MOVE || lastCmdCode == ATTACK || lastCmdCode == CHAT || lastCmdCode == ABANDON || lastCmdCode == RECRUIT)
    {
      fprintf(saving_file, "|%s %s %s|", lastCmdName, command_get_argument(lastCmd), command_get_lastcmd_success(lastCmd) == OK ? "OK" : "ERROR");
    }
    else
    {
      fprintf(saving_file, "|%s %s|", lastCmdName, command_get_lastcmd_success(lastCmd) == OK ? "OK" : "ERROR");
    }

    if (second_to_lastCode == TAKE || second_to_lastCode == INSPECT || second_to_lastCode == DROP || second_to_lastCode == MOVE || second_to_lastCode == ATTACK || second_to_lastCode == CHAT || second_to_lastCode == ABANDON || second_to_lastCode == RECRUIT)
    {
      fprintf(saving_file, "%s %s %s|", second_to_lastName, command_get_argument(second_to_last), command_get_lastcmd_success(second_to_last) == OK ? "OK" : "ERROR");
    }
    else
    {
      fprintf(saving_file, "%s %s|", second_to_lastName, command_get_lastcmd_success(second_to_last) == OK ? "OK" : "ERROR");
    }

    if (third_to_lastCode == TAKE || third_to_lastCode == INSPECT || third_to_lastCode == DROP || third_to_lastCode == MOVE || third_to_lastCode == ATTACK || third_to_lastCode == CHAT || third_to_lastCode == ABANDON || third_to_lastCode == RECRUIT)
    {
      fprintf(saving_file, "%s %s %s|", third_to_lastName, command_get_argument(third_to_last), command_get_lastcmd_success(third_to_last) == OK ? "OK" : "ERROR");
    }
    else
    {
      fprintf(saving_file, "%s %s|", third_to_lastName, command_get_lastcmd_success(third_to_last) == OK ? "OK" : "ERROR");
    }

    fprintf(saving_file, "%s %s|\n", game_interface_in_pos_get_message(game, i), game_interface_in_pos_get_description(game, i));
  }

  return OK;
}

Status gameManagement_load_turn(Game *game, char *filename)
{
  FILE *save = NULL;
  char line[WORD_SIZE] = "";
  char *token = NULL;
  int turn;

  if (!game || !filename)
    return ERROR;

  save = fopen(filename, "r");

  if (!save)
    return ERROR;

  while (fgets(line, WORD_SIZE, save))
  {
    if (strncmp("#t:", line, 3))
    {
      token = strtok(line + 3, "\n\r");
      turn = atoi(token);
    }
  }

  fclose(save);
  if (game_set_turn(game, turn) == ERROR)
  {
    return ERROR;
  }
  return OK;
}

Status gameManagement_load_interface(Game *game, char *filename)
{
  FILE *save = NULL;
  char line[WORD_SIZE] = "";
  char *token = NULL;
  int pos, i = 2;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Command *lastCmd = NULL, *second_to_lastCmd = NULL, *third_to_lastCmd = NULL;
  char *message = NULL, *description = NULL;
  CommandCode cmdCode;
  Status success;

  if (!game || !filename)
    return ERROR;

  save = fopen(filename, "r");
  if (!save)
    return ERROR;

  lastCmd = command_create();
  if (!lastCmd)
  {
    fclose(save);
    return ERROR;
  }

  second_to_lastCmd = command_create();
  if (!second_to_lastCmd)
  {
    fclose(save);
    command_destroy(lastCmd);
    return ERROR;
  }

  third_to_lastCmd = command_create();
  if (!third_to_lastCmd)
  {
    fclose(save);
    command_destroy(lastCmd);
    command_destroy(second_to_lastCmd);
    return ERROR;
  }

  cmdCode = UNKNOWN;

  while (fgets(line, WORD_SIZE, save))
  {
    if (strncmp("#i:", line, 3))
    {
      token = strtok(line + 3, "|\r\n");
      pos = atoi(token);
      token = strtok(NULL, " |\r\n");
      while (cmdCode == UNKNOWN && i < N_CMD)
      {
        if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
        {
          cmdCode = i + NO_CMD;
        }
        else
        {
          i++;
        }
      }

      command_set_code(lastCmd, cmdCode);

      if (cmdCode == TAKE || cmdCode == INSPECT || cmdCode == DROP || cmdCode == MOVE || cmdCode == RECRUIT || cmdCode == ABANDON || cmdCode == CHAT || cmdCode == ATTACK)
      {
        token = strtok(NULL, " |\r\n");
        if(command_set_argument(lastCmd, token) == ERROR) return ERROR;
      }
      command_set_argument(lastCmd, NO_ARG);
      token = strtok(NULL, " |\r\n");
      success = !strcmp(token, "ERROR")? ERROR : OK;
      command_set_lastcmd_success(lastCmd, success);



      token = strtok(NULL, " |\r\n");
      while (cmdCode == UNKNOWN && i < N_CMD)
      {
        if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
        {
          cmdCode = i + NO_CMD;
        }
        else
        {
          i++;
        }
      }

      command_set_code(second_to_lastCmd, cmdCode);

      if (cmdCode == TAKE || cmdCode == INSPECT || cmdCode == DROP || cmdCode == MOVE || cmdCode == RECRUIT || cmdCode == ABANDON || cmdCode == CHAT || cmdCode == ATTACK)
      {
        token = strtok(NULL, " |\r\n");
        if(command_set_argument(second_to_lastCmd, token) == ERROR) return ERROR;
      }
      command_set_argument(second_to_lastCmd, NO_ARG);
      token = strtok(NULL, " |\r\n");
      success = !strcmp(token, "ERROR")? ERROR : OK;
      command_set_lastcmd_success(second_to_lastCmd, success);


      token = strtok(NULL, " |\r\n");
      while (cmdCode == UNKNOWN && i < N_CMD)
      {
        if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
        {
          cmdCode = i + NO_CMD;
        }
        else
        {
          i++;
        }
      }

      command_set_code(third_to_lastCmd, cmdCode);

      if (cmdCode == TAKE || cmdCode == INSPECT || cmdCode == DROP || cmdCode == MOVE || cmdCode == RECRUIT || cmdCode == ABANDON || cmdCode == CHAT || cmdCode == ATTACK)
      {
        token = strtok(NULL, " |\r\n");
        if(command_set_argument(third_to_lastCmd, token) == ERROR) return ERROR;
      }
      command_set_argument(third_to_lastCmd, NO_ARG);
      token = strtok(NULL, " |\r\n");
      success = !strcmp(token, "ERROR")? ERROR : OK;
      command_set_lastcmd_success(third_to_lastCmd, success);


      token = strtok(NULL, " |\r\n");
      message = token;
      token = strtok(NULL, " |\r\n");
      description = token;


      game_locate_new_interface_in_pos(game, pos, lastCmd, second_to_lastCmd, third_to_lastCmd, message, description);

    }
  }

  fclose(save);
  return OK;
}

/*End of implementation of private functions*/