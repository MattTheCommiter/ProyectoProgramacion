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
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

/*Constant values used for the creation of the game's graphic interface*/
#define WIDTH_MAP 60
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 29
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
/**
 * @brief Create a line of spaces
 * 
 * @param id_center the id of the object that will be at the center of the line
 * @return char** matriz with the complete line
 */
char **create_line_of_spaces(Game *game, Id id_center);

/**
 * @brief Create a square space description for the space with the given id
 * 
 * @param game 
 * @param square_id 
 * @return char** matrix with the square of the space that will be printed on the screen
 */
char **create_space_square(Game *game, Id square_id);



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

char **create_space_square(Game *game, Id square_id){
  char **space_square=NULL, str[255], ant_str[]="m0^", blank_player_str[]="   ", **gdesc, *player, object=' '; /*Quitar este número mágico*/
  Space *space;
  int i;

  space = game_get_space(game, square_id);
  
  
  
  if(!(space_square = (char **)calloc(N_TOTAL_LINES_IN_SQUARE, sizeof(char *)))){
    return NULL;
   }
  if(!(space_square[0] = (char *)calloc(N_TOTAL_LINES_IN_SQUARE*(N_TOTAL_ROWS_IN_SQUARE + 1), sizeof(char)))){
    free(space_square);
    return NULL;
   }



  for(i=1;i<N_TOTAL_LINES_IN_SQUARE;i++){
    space_square[i] = space_square[0] + (N_TOTAL_ROWS_IN_SQUARE + 1)*i;
   }

   
   
  if(square_id == NO_ID){
    for(i=0;i<N_TOTAL_LINES_IN_SQUARE;i++){
      strcpy(space_square[i], "                 ");
    }
   }
   else{
    if(game_get_player_location(game) == square_id){
        player = ant_str;
    }else{
        player=blank_player_str;
    }

    gdesc = space_get_gdesc(space);

    sprintf(str, "+---------------+");
    strcpy(space_square[0], str);
    if(square_id < MIN_VALUE_WITH_THREE_NUMBERS){
      sprintf(str, "| %s         %2d|", player, (int)square_id);
      strcpy(space_square[1], str);
    }else{
      sprintf(str, "| %s        %2d|", player, (int)square_id);
      strcpy(space_square[1], str);
    }
    sprintf(str, "|%s      |", gdesc[0]);
    strcpy(space_square[2], str);
    sprintf(str, "|%s      |", gdesc[1]);
    strcpy(space_square[3], str);
    sprintf(str, "|%s      |", gdesc[2]);
    strcpy(space_square[4], str);
    sprintf(str, "|%s      |", gdesc[3]);
    strcpy(space_square[5], str);
    sprintf(str, "|%s      |", gdesc[4]);
    strcpy(space_square[6], str);
    sprintf(str, "|       %c       |", object);
    strcpy(space_square[7], str);
    sprintf(str, "+---------------+");
    strcpy(space_square[8], str);
  }


  return space_square;
}

char **create_line_of_spaces(Game *game, Id id_center){
  char **gdesc_line=NULL, **left_square=NULL, **center_square=NULL, **right_square=NULL, str[255], left_square_arrow=' ', right_square_arrow=' ';
  int i;
  Id id_left, id_right;

  id_left = space_get_west(game_get_space(game, id_center));
  id_right = space_get_east(game_get_space(game, id_center));

  if(id_right != NO_ID){
    right_square_arrow = '>';
  }
  if(id_left != NO_ID){
    left_square_arrow = '<';
  }

  /*Create the matrix to store the entire line*/
  if(!(gdesc_line = (char **)calloc(N_TOTAL_LINES_IN_GDESC, sizeof(char *)))){
    return NULL;
   }
  if(!(gdesc_line[0] = (char *)calloc(N_TOTAL_LINES_IN_GDESC*(N_TOTAL_ROWS_IN_GDESC + 1), sizeof(char)))){
    free(gdesc_line);
    return NULL;
   }
  for(i=1;i<N_TOTAL_LINES_IN_GDESC;i++){
       gdesc_line[i] = gdesc_line[0] + (N_TOTAL_ROWS_IN_GDESC + 1)*i;
   }
  /*End of creating the matrix*/
   
  left_square = create_space_square(game, id_left);
  center_square = create_space_square(game, id_center);
  right_square = create_space_square(game, id_right);

  /*Create the lines manually*/
  sprintf(str, "%s  %s  %s", left_square[0], center_square[0], right_square[0]);
  strcpy(gdesc_line[0], str);
  sprintf(str, "%s  %s  %s", left_square[1], center_square[1], right_square[1]);
  strcpy(gdesc_line[1], str);
  sprintf(str, "%s  %s  %s", left_square[2], center_square[2], right_square[2]);
  strcpy(gdesc_line[2], str);
  sprintf(str, "%s  %s  %s", left_square[3], center_square[3], right_square[3]);
  strcpy(gdesc_line[3], str);
  sprintf(str, "%s %c%s%c %s", left_square[4], left_square_arrow, center_square[4], right_square_arrow, right_square[4]);
  strcpy(gdesc_line[4], str);
  sprintf(str, "%s  %s  %s", left_square[5], center_square[5], right_square[5]);
  strcpy(gdesc_line[5], str);
  sprintf(str, "%s  %s  %s", left_square[6], center_square[6], right_square[6]);
  strcpy(gdesc_line[6], str);
  sprintf(str, "%s  %s  %s", left_square[7], center_square[7], right_square[7]);
  strcpy(gdesc_line[7], str);
  sprintf(str, "%s  %s  %s", left_square[8], center_square[8], right_square[8]);
  strcpy(gdesc_line[8], str);
  
  
  if(left_square){
    if(left_square[0]){
      free(left_square[0]);
    }
    free(left_square);
  }

  if(center_square){
    if(center_square[0]){
      free(center_square[0]);
    }
    free(center_square);
  }

  if(right_square){
    if(right_square[0]){
      free(right_square[0]);
    }
    free(right_square);
  }
  /*End of creating the lines*/
  return gdesc_line;
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
  Id id_act = NO_ID, obj_loc = NO_ID, character_loc = NO_ID, id_north=NO_ID, id_south=NO_ID;
  
  char **created_line=NULL;
  char str[255], *object_name = NULL, *character_gdesc = NULL, north_arrow = ' ', south_arrow = ' ';
  int i, character_hp;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Status last_cmd_succ = OK;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    id_north = space_get_north(game_get_space(game, id_act));
    id_south = space_get_south(game_get_space(game, id_act));

    if(id_north != NO_ID){
      north_arrow = '^';
    }
    if(id_south != NO_ID){
      south_arrow = 'v';
    }

    created_line = create_line_of_spaces(game, id_north);
    screen_area_puts(ge->map, created_line[0]);
    if(created_line!=NULL){
      for(i=0;i<N_TOTAL_LINES_IN_GDESC;i++){
        screen_area_puts(ge->map, created_line[i]);
      }
    }
    free(created_line[0]);
    free(created_line);
    created_line=NULL;
    
    sprintf(str, "                           %c                           ", north_arrow);
    screen_area_puts(ge->map, str);
    created_line = create_line_of_spaces(game, id_act);
    for(i=0;i<N_TOTAL_LINES_IN_GDESC;i++){
      screen_area_puts(ge->map, created_line[i]);
    }
    sprintf(str, "                           %c                           ", south_arrow);
    screen_area_puts(ge->map, str);
    free(created_line[0]);
    free(created_line);
    created_line=NULL;
    
    created_line = create_line_of_spaces(game, id_south);
    for(i=0;i<N_TOTAL_LINES_IN_GDESC;i++){
      screen_area_puts(ge->map, created_line[i]);
    }
    free(created_line[0]);  
    free(created_line);
    created_line=NULL;
  }

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
