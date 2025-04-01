/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <time.h>
#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

#define TIME_BETWEEN_TURNS 1  /*Ammount of seconds the game gives each player to visualize their action before changing the turn*/

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
 * @param game a pointer to the structure with the game's main information
 * @param gengine a pointer to the game's graphic engine
 * @param logfile a pointer to the log file
 */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file);

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


  /*If game data file is missing, the program exits with an error.
  If the game data file is provided but the log file is not, the code will still proceed with the game
  If log file are also provided, logging is enabled*/
  if (argc < 2){
    fprintf(stderr, "Use: %s <game_data_file> <-l log_file>\n", argv[0]);
    return 1;
  }

  /*at least four arguments provided (the program name, game data file, -l flag, and log file name*/
  if (argc >= 4 && strcmp(argv[2], "-l") == 0){
    /*  open the log file for writing*/
    sprintf(filename, "%s.txt", argv[3]);
    log_file = fopen(filename, "w");
    if (!log_file)  {
      fprintf(stderr, "Error opening log file: %s\n", argv[3]);
      return 1;
    }
  }

  /* initializes the game and the graphic engine using the game data file*/
  if (!game_loop_init(&game, &gengine, argv[1])){
    /*runs the game loop, from user inputs and updates the game state. It also logs commands if a log file is given*/
    game_loop_run(game, gengine, log_file);
    game_loop_cleanup(game, gengine);
  }

  if (log_file){
    fclose(log_file);
  }

  return 0;
}

/**
 * @brief initializes the game, calling the game_create_from_file function with the text file that has been passed as an argument
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param game a pointer to the structure with the game's main information
 * @param genginge a pointer to pointer of the structure where the game's graphic engine will run
 * @param file_name string with the name of the file where the game's information is located
 *
 * @return 1 if errors occur, and 0 if everything runs correctly
 */
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

  return 0;
}

/**
 * @brief this function runs the game and calls the necessary functions for this purpose
 *
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param game structure with the game's main information
 * @param gengine pointer to the structure with the game's graphic interface information
 * * @param logfile a pointer to the log file
 */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file){
  Command *last_cmd;
  CommandCode cmd_code;
  char *cmd_name = NULL;
  char *cmd_arg = NULL;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Status cmd_status;

  if (!gengine){
    return;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE))
  {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);

    /*If log is enabled*/
    if (log_file){
      cmd_code = command_get_code(last_cmd);
      cmd_name = cmd_to_str[cmd_code - NO_CMD][CMDL];    /*Converts the command code to a string, through the index of the array*/
      cmd_arg = command_get_argument(last_cmd);
      cmd_status = game_get_last_command_success(game);

      /*Log the command (and the argument in some cases) and its result*/
      if (cmd_code == TAKE || cmd_code == INSPECT || cmd_code == DROP){
        fprintf(log_file, "%s %s: %s\n", cmd_name, cmd_arg, cmd_status == OK ? "OK" : "ERROR");
      }else{
        fprintf(log_file, "%s: %s\n", cmd_name, cmd_status == OK ? "OK" : "ERROR");
      }
    }
    if(command_get_code(last_cmd) != EXIT){
      graphic_engine_paint_game(gengine, game);
      if(game_get_n_players(game) > 1){
        sleep(TIME_BETWEEN_TURNS);
      }
      game_next_turn(game);
    }
    
  }
}

/**
 * @brief destroys the game and cleans the textual graphic interface
 *
 * @author Profesores PPROG
 * @date 27-01-2025
 *
 * @param game structure with the game's main information
 * @param pointer to the structure whith the game's graphic interface information
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
