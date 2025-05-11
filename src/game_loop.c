/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG, Matteo Artunedo (mutiplayer implementation), AGL and Alvaro Inigo (log implementation)
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <strings.h>

#include <unistd.h>
#include <time.h>

#include "graphic_engine.h"
#include "game_actions.h"
#include "command.h"
#include "game.h"
#include "game_rules.h"

#define TIME_BETWEEN_TURNS 1  /*!< Ammount of seconds the game gives each player to visualize their action before changing the turn*/

/**
 * @brief creates the game structure with the information from a file (calls the game_create_from_file function) and creates the game's graphic engine (calling the graphic_engine_create function)
 *
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param game a pointer to the structure with the game's main information
 * @param gengine a pointer to the game's graphic engine
 * @param file_name a string with the name of the file where the information needed to create the game is stored
 * @return int: 1 if an error occurs and 0 if no errors occur.
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief runs the game, receiving the user's inputs and painting the graphic interface
 *
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param game a double pointer to the structure with the game's main information
 * @param gengine a pointer to the game's graphic engine
 * @param log_file a pointer to the log file
 */
void game_loop_run(Game **game, Graphic_engine *gengine, FILE *log_file);

/**
 * @brief destroys the game and the graphic engine
 *
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param game a pointer to the structure with the game's main information
 * @param gengine a pointer to the game's graphic engine
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/*****************************************************************************/

int DETERMINIST_MODE = 0;
/**
 * @brief initializes the game loop (calling the game_loop_init function) and runs the game loop
 *
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param argc number of arguments in char *argv[]
 * @param argv array where the name of the text file is stored
 * @return int: 1 if an error occurs and 0 if no errors occur
 */ 
int main(int argc, char *argv[])
{
  Game *game = NULL;
  Graphic_engine *gengine;
  FILE *log_file = NULL;
  char filename[MAX_MESSAGE];
  int i;

  /*If game data file is missing, the program exits with an error.
  If the game data file is provided but the log file is not, the code will still proceed with the game
  If log file are also provided, logging is enabled*/
  if (argc < 2){
    fprintf(stderr, "Use: %s <game_data_file> <-l log_file>\n", argv[0]);
    return 1;
  }

  for (i = 2 ; i < argc ; i++) 
  {
    if (strcasecmp(argv[i], "-d") == 0) DETERMINIST_MODE = 1;
    if (strcasecmp(argv[i], "-l") == 0)
    {
      sprintf(filename, "%s.log", argv[i+1]);
      log_file = fopen(filename, "w");
      if (!log_file) 
      {
        fprintf(stderr, "Error opening the log file: |%s|", argv[i+1]);
        return 1;
      }
      i += 2;
    }
  }
  /*at least four arguments provided (the program name, game data file, -l flag, and log file name*/
  /*
  if (argc >= 4 && strcmp(argv[2], "-l") == 0){
    sprintf(filename, "%s.log", argv[3]);
    log_file = fopen(filename, "w");
    if (!log_file)  {
      fprintf(stderr, "Error opening log file: %s\n", argv[3]);
      return 1;
    }
  }
  */

  /*Command to support UNICODE characters*/
  setlocale(LC_ALL, "");

  /* initializes the game and the graphic engine using the game data file*/
  if (!game_loop_init(&game, &gengine, argv[1])){
    /*runs the game loop, from user inputs and updates the game state. It also logs commands if a log file is given*/
    game_loop_run(&game, gengine, log_file);
    game_loop_cleanup(game, gengine);
  }

  if (log_file){
    fclose(log_file);
  }

  return 0;
}

/**Yhis function initializes the game, calling the game_create_from_file function with the text file
 * that has been passed as an argument. */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
  srand(time(NULL));
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    game_destroy((*game));
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy((*game));
    return 1;
  }
  game_set_current_cinematic(*game, INTRODUCTION);
  return 0;
}

/**this function runs the game and calls the necessary functions for this purpose. */
void game_loop_run(Game **game, Graphic_engine *gengine, FILE *log_file){
  Command *last_cmd = NULL;
  CommandCode cmd_code;
  char *cmd_name = NULL;
  char *cmd_arg = NULL;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Status cmd_status;
  int i;

  if (!gengine){
    return;
  }

  do
  {
    /*We create a new command which will be added  in the command history of the player currently playing*/
    last_cmd = command_create();

    /*We play the cinematic if it corresponds to do so*/
    if(game_get_current_cinematic(*game) != NO_CINEMATIC){
      game_set_show_message(*game, TRUE, game_get_turn(*game));
      for(i=0;i<cinematics_get_n_lines(game_get_current_cinematic_text(*game));i++){
        game_set_message(*game, cinematics_get_line(game_get_current_cinematic_text(*game), i), game_get_turn(*game));
        graphic_engine_paint_game(gengine, *game);
        sleep(TIME_BETWEEN_CINEMATICS);
      }
      game_set_current_cinematic(*game, NO_CINEMATIC);
      game_set_show_message(*game, FALSE, game_get_turn(*game));
      /*clear the dialogue after the cinematic*/
    }
    if(game_get_current_mission_code(*game) == NO_MISSION){
      game_rules_mission_update(*game);
    }

    /*We paint the game for the player whose turn it currently is*/
    graphic_engine_paint_game(gengine, *game);
    /*We read the player's command and add it to their command history*/
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd, gengine);

    /*we update the mission state*/
    game_rules_mission_update(*game);

    /*If log is enabled*/
    if (log_file){
      cmd_code = command_get_code(last_cmd);
      cmd_name = cmd_to_str[cmd_code - NO_CMD][CMDL];    /*Converts the command code to a string, through the index of the array*/
      cmd_arg = command_get_argument(last_cmd);
      cmd_status = command_get_lastcmd_success(last_cmd);

      /*Log the command (and the argument in some cases) and its result*/
      if (cmd_code == TAKE || cmd_code == INSPECT || cmd_code == DROP || cmd_code == MOVE || cmd_code == ATTACK || cmd_code == CHAT || cmd_code == ABANDON || cmd_code == RECRUIT){
        fprintf(log_file, "%s %s: %s (P%d)\n", cmd_name, cmd_arg, cmd_status == OK ? "OK" : "ERROR", game_get_turn(*game) + 1);
      }else{
        fprintf(log_file, "%s: %s (P%d)\n", cmd_name, cmd_status == OK ? "OK" : "ERROR", game_get_turn(*game) + 1);
      }
    }

    /*We determine whether the player has chosen to exit the game or not*/
    /*if(command_get_code(game_interface_data_get_cmd_in_pos(*game, LAST)) != EXIT){*/
      /*If there are multiple players or the last player standing dies, we print the game again and introduce a timer for the player to be able to view the newly printed graphic engine, which shows the effects of their action (updated location, health bar, backpack, etc)*/
      /*if(game_get_n_players(*game) > 1 || player_get_health(game_get_current_player(*game)) == 0){
        graphic_engine_paint_game(gengine, *game);
        sleep(TIME_BETWEEN_TURNS);
      }*/

      /*We check whether the player has died as a result of his last action*/
      if(player_get_health(game_get_current_player(*game)) == 0){
        /*If there are more players in the game, we delete the current player*/
        if(game_get_n_players(*game) > 1){
          game_delete_player(*game);
        }
        else{
          /*If the current player is the only one left, the game finishes*/
          game_set_finished(*game, TRUE);
        }
      }
      /*game_next_turn(*game);
    }*/
    
  }
  while ((command_get_code(game_interface_data_get_cmd_in_pos(*game, LAST)) != EXIT) && (game_get_finished(*game) == FALSE));
}

/**destroys the game and cleans the textual graphic interface. */
void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
