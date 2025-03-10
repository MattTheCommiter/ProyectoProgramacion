/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0.1
 * @date 12-02-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

/*Constant values used for the creation of the game's graphic interface*/
#define WIDTH_MAP 48
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 13
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

/**
 * @brief structure where the pointers to all the areas of the textual graphic interface are stored
 *
 * @date 27-01-2025
 * @author Profesores
 */
struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback; /*!<All of the different parts of the textual graphic interface*/
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
  {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
  {
    return NULL;
  }
  /*Initializes all of the components of the game's graphic interface*/
  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID, obj_loc = NO_ID, character_loc = NO_ID;
  Space *space_act = NULL;
  char obj = '\0', obj_l = '\0', obj_r = '\0';
  char str[255], *object_name = NULL, *character_gdesc = NULL;
  int i, character_hp;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Status last_cmd_succ = OK;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_left = space_get_west(space_act);
    id_right = space_get_east(space_act);

    if (game_get_object_location(game, 1) == id_back)
      obj = '*';
    else
      obj = ' ';
    /*The following lines are dedicated to printing the map that appears on the screen, including the ant and the object (if present)*/
    if (id_back != NO_ID)
    {
      if (id_back < 100)
      {
        sprintf(str, "  |         %2d|", (int)id_back);
      }
      else
      {
        sprintf(str, "  |        %2d|", (int)id_back);
      }
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game, 1) == id_act)
      obj = '*';
    else
      obj = ' ';
    if (game_get_object_location(game, 1) == id_left)
      obj_l = '*';
    else
      obj_l = ' ';
    if (game_get_object_location(game, 1) == id_right)
      obj_r = '*';
    else
      obj_r = ' ';

    if (id_act != NO_ID)
    {
      if (id_left != NO_ID)
      {
        if (id_right != NO_ID)
        {
          sprintf(str, "  +-----------+   +-----------+   +-----------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "  |        %2d|   | m0^    %2d|   |        %2d|", (int)id_left, (int)id_act, (int)id_right);
          screen_area_puts(ge->map, str);
          sprintf(str, "  |     %c     |<  |     %c     |  >|     %c     |", obj_l, obj, obj_r);
          screen_area_puts(ge->map, str);
          sprintf(str, "  +-----------+   +-----------+   +-----------+");
          screen_area_puts(ge->map, str);
        }
        else
        {
          sprintf(str, "  +-----------+   +-----------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "  |        %2d|   | m0^    %2d|", (int)id_left, (int)id_act);
          screen_area_puts(ge->map, str);
          sprintf(str, "  |     %c     |< |     %c     |", obj_l, obj);
          screen_area_puts(ge->map, str);
          sprintf(str, "  +-----------+   +-----------+");
          screen_area_puts(ge->map, str);
        }
      }
      if (id_left == NO_ID)
      {
        if (id_right != NO_ID)
        {
          sprintf(str, "  +-----------+   +-----------+");
          screen_area_puts(ge->map, str);
          sprintf(str, "  | m0^    %2d|   |        %2d|", (int)id_act, (int)id_right);
          screen_area_puts(ge->map, str);
          sprintf(str, "  |     %c     |  >|     %c     |", obj, obj_r);
          screen_area_puts(ge->map, str);
          sprintf(str, "  +-----------+   +-----------+");
          screen_area_puts(ge->map, str);
        }
        else
        {
          sprintf(str, "  +-----------+");
          screen_area_puts(ge->map, str);
          if (id_act < 100)
          {
            sprintf(str, "  | m0^     %2d|", (int)id_act);
          }
          else
          {
            sprintf(str, "  | m0^    %2d|", (int)id_act);
          }
          screen_area_puts(ge->map, str);
          sprintf(str, "  |     %c     |", obj);
          screen_area_puts(ge->map, str);
          sprintf(str, "  +-----------+");
          screen_area_puts(ge->map, str);
        }
      }
    }

    if (game_get_object_location(game, 1) == id_next)
      obj = '*';
    else
      obj = ' ';

    if (id_next != NO_ID)
    {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      if (id_next < 100)
      {
        sprintf(str, "  |         %2d|", (int)id_next);
      }
      else
      {
        sprintf(str, "  |        %2d|", (int)id_next);
      }
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint in the description area */
  /*
  screen_area_clear(ge->descript);
  if ((obj_loc = game_get_object_location(game,1)) != NO_ID)
  {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }
  if ((obj_loc = game_get_object_location(game,1)) == NO_ID)
  {
    sprintf(str, "Seed in the inventory");
    screen_area_puts(ge->descript, str);
  }
*/
  screen_area_clear(ge->descript);
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object_name = object_get_name(game_get_object_in_pos(game, i));
    obj_loc = game_get_object_location(game, object_get_id(game_get_object_in_pos(game, i)));
    if (obj_loc != NO_ID)
    {
      sprintf(str, "  %s location:%d", object_name, (int)obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }
  sprintf(str, "Characters : ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    character_gdesc = character_get_gdesc(game_get_character(game, game_get_character_id_at(game, i)));
    character_loc = game_get_character_location(game, game_get_character_id_at(game, i));
    character_hp = character_get_health(game_get_character(game, game_get_character_id_at(game, i)));
    sprintf(str, "  %s location:%d (%d)", character_gdesc, (int)character_loc, character_hp);
    screen_area_puts(ge->descript, str);
  }
  sprintf(str, "Player : %d (%d)", (int)game_get_player_location(game), player_get_health(game_get_player(game)));
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Objects in the inventory: ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object_name = object_get_name(game_get_object_in_pos(game, i));
    obj_loc = game_get_object_location(game, object_get_id(game_get_object_in_pos(game, i)));
    if (obj_loc == NO_ID)
    {
      sprintf(str, "  %s", object_name);
      screen_area_puts(ge->descript, str);
    }
  }

  if (command_get_code(game_get_last_command(game)) == CHAT)
  {
    sprintf(str, "  Message: %s", game_get_message(game));
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "next or n, back or b, exit or e, take seed or ts,take grain or t g,take crumb or t c, take leaf or t l, drop or d, left or l, right or r, chat or c, attack or a");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  last_cmd_succ = game_get_last_command_success(game);
  if(last_cmd_succ == ERROR){
    sprintf(str, " %s (%s) ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }else{
    sprintf(str, " %s (%s) OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
