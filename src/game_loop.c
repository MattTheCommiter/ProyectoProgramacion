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
#include <unistd.h>

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
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

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

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
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
 */
void game_loop_run(Game *game, Graphic_engine *gengine)
{
  Command *last_cmd;

  if (!gengine)
  {
    return;
  }

  do
  {
    /*We create a new command which will be added  in the command history of the player currently playing*/
    last_cmd = command_create();
    /*We paint the game for the player whose turn it currently is*/
    graphic_engine_paint_game(gengine, game);
    /*We read the player's command and add it to their command history*/
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);

    /*We determine whether the player has chosen to exit the game or not*/
    if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) != EXIT){
      /*If there are multiple players or the last player standing dies, we print the game again and introduce a timer for the player to be able to view the newly printed graphic engine, which shows the effects of their action (updated location, health bar, backpack, etc)*/
      if(game_get_n_players(game) > 1 || player_get_health(game_get_current_player(game)) == 0){
        graphic_engine_paint_game(gengine, game);
        sleep(TIME_BETWEEN_TURNS);
      }

      /*We check whether the player has died as a result of his last action*/
      if(player_get_health(game_get_current_player(game)) == 0){
        /*If there are more players in the game, we delete the current player*/
        if(game_get_n_players(game) > 1){
          game_delete_player(game);
        }
        else{
          /*If the current player is the only one left, the game finishes*/
          game_set_finished(game, TRUE);
        }
      }
      game_next_turn(game);
    }
  }
  while ((command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) != EXIT) && (game_get_finished(game) == FALSE));
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
