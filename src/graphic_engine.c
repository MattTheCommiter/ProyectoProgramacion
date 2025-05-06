/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Matteo Artunedo, Alvaro Inigo
 * @version 1.3
 * @date 12-03-2025
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Constant values used for the creation of the game's graphic interface
 * 
 */
#define WIDTH_MAP N_TOTAL_COLUMNS_IN_SQUARE     /*!<Width of the map in the graphic interface*/
#define WIDTH_DIALOGUE 60                       /*!<Width of the dialogue boc in the graphic interface*/
#define WIDTH_DES 40                            /*!<Width of the description box in the graphic interface*/
#define WIDTH_BAN 25                            /*!<Width of the banner in the graphic interface*/
#define WIDTH_COMPASS WIDTH_DIALOGUE            /*!<Width of the compas area in the graphic_interface*/
#define WIDTH_HLP WIDTH_MAP                     /*!<Width of the help area in the grapihc interface*/
#define WIDTH_FEEDBACK WIDTH_DES                /*!<Width of the feedback area in the grapihc interface*/
#define WIDTH_SEPARATOR 1                       /*!<Width of the lines that separate space areas*/
#define WIDTH_MISSION WIDTH_DIALOGUE + WIDTH_MAP + WIDTH_DES + WIDTH_SEPARATOR * 2   /*!<Width of the mission area*/

#define HEIGHT_MAP (N_TOTAL_ROWS_IN_SQUARE + 2) /*!<Height of the map in the graphic interface*/
#define HEIGHT_DIALOGUE HEIGHT_MAP              /*!<Height of the dialogue box in the grapihc interface*/
#define HEIGHT_COMPASS 7                        /*!<Height of the compas area in the graphic_interface*/
#define HEIGHT_MISSION 5                        /*!<Height of the mission area in the grapihc interface*/
#define HEIGHT_BAN 1                            /*!<Height of the banner in the graphic interface*/
#define HEIGHT_HLP HEIGHT_COMPASS               /*!<Height of the help box in the graphic interface*/
#define HEIGHT_FDB HEIGHT_COMPASS               /*!<Height of the feedback box in the graphic interface*/
#define HEIGHT_DES HEIGHT_MAP                   /*!<Height of the description box in the graphic interface*/
#define HEIGHT_SEPARATOR 1                      /*!<Height of the lines that separate areas in the graphic interface*/

#define SIZE_OF_SPACE 2                         /*!<Size of the chars ' ,' between each object name*/
#define FINAL_CHARACTER 1                       /*!<Size corresponding to the \0 character of the string*/
#define ARROW_SIZE 1                            /*!<Size corresponding to the arrow characters*/
#define BOTTOM_HEIGHT 1                         /*!<Height of the lowest line of spaces in the map*/
#define MIDDLE_HEIGHT 2                         /*!<Height of the middle line of spaces in the map*/
#define TOP_HEIGHT 3                            /*!<Height of the highest line of spaces in the map*/
#define GDESC_INITIAL_POSITION 2                /*!<The position the first line of the graphic description of a space has in the total space square*/
#define GDESC_FINAL_POSITION 7                  /*!<The position the last line of the graphic description of a space has in the total space square*/
#define MAX_STR 255                             /*!<The maximum characters of a line*/

/**
 * @brief structure where the pointers to all the areas of the textual graphic interface are stored
 *
 * @date 27-01-2025
 * @author Profesores
 */
struct _Graphic_engine
{
  Area 
  *map,       /*!<Map area of the graphic engine. Here we can see the players, objects, spaces, graphical descriptions, etc*/
  *descript,  /*!<Description area of the graphic engine. Here the player can get info about the game such as object and character placement, his health, etc*/
  *dialogue,  /*!<Dialog area of the graphic engine. Here the player can read the conversations between characters*/
  *banner,    /*!<Title area in the graphic engine. Here we can see the title of the game and the player who is currently playing*/
  *help,      /*!<Help area of the graphic engine. Here all of the possible commands a player can run are displayed*/
  *feedback,  /*!<Feedback area in the graphic engine. Here the player can see the commands he has executed and if they were succesful*/
  *compass,    /*!<Compass area in the graphic engine. This will show the player the spaces they can move to*/
  *mission;    /*!<Mission area in the grapihc engine. This will show the player the current mission and objective*/
};

/**
 * @brief paints the compas area of the graphic interface
 * @author Matteo Arunedo
 * @param game pointer to the game
 * @param north Id of the space in the north
 * @param south Id of the space in the south
 * @param west Id of the space in the west
 * @param east Id of the space in the east
 * @param up Id of the space on top
 * @param down Id of the space beow
 * @return two-dimensional array with the compas information
 */
char **graphic_engine_paint_compas(Game *game, Id north, Id south, Id west, Id east, Id up, Id down);


/**
 * @brief Create a square space description for the space with the given id
 * @author Matteo Artunedo
 * @param game pointer to the game structure
 * @param square_id id of the space which corresponds to the box being created
 * @return char** matrix with the square of the space that will be printed on the screen
 */
char **graphic_engine_create_space_square(Game *game, Id square_id);



/**
 * @brief Paints the feedback of one command in the player command history
 * @author Matteo Artunedo 
 * @param game pointer to the game
 * @param ge pointer to the graphic engine
 * @param pos position of the command (whether we want to print the last command, the second to last or the third to last)
 * @param str the string to which the feedback will be copied
 */
void graphic_interface_paint_feedback_for_pos(Game *game, Graphic_engine*ge, CommandPosition pos, char *str);

/*PRIVATE FUNCTIONS*/
char **graphic_engine_paint_compass(Game *game, Id north, Id south, Id west, Id east, Id up, Id down) 
{
  char **compas_info=NULL, *space_name=NULL, *space_name2=NULL, middle_str[]="< + >", blank_word[] = " ", unknown_str[] = "???", *up_name=NULL, *down_name=NULL;
  int i, left_padding, total_width, middle_str_pos;
  long link_id;
  if (!game)
  {
    return NULL;
  }

  if (!(compas_info = (char **)calloc(HEIGHT_COMPASS, sizeof(char *))))
  {
    return NULL;
  }
  if (!(compas_info[0] = (char *)calloc((WIDTH_COMPASS) * HEIGHT_COMPASS, sizeof(char))))
  {
    free(compas_info);
    return NULL;
  }

  for (i = 1; i < HEIGHT_COMPASS; i++)
  {
    compas_info[i] = compas_info[0] + (WIDTH_COMPASS * i);
  }



  memset((void *)compas_info[0], (int)' ', WIDTH_COMPASS);
  compas_info[0][WIDTH_COMPASS - 1] = '\0';



  /*We paint the name of the north space in the upper part*/
  space_name = (char *)space_get_name(game_get_space(game, north));
  if(!space_name){
    space_name = blank_word;
  }
  /*Calculate left padding*/
  left_padding = (WIDTH_COMPASS - strlen(space_name)) / 2;

  /*Fill the row with spaces and copy the string*/
  for (i = 0; i < WIDTH_COMPASS - 1; i++) {
      if (i < left_padding) {
          compas_info[1][i] = ' '; /*Left padding*/
      } else if (i < left_padding + strlen(space_name)) {
          compas_info[1][i] = space_name[i - left_padding]; /*Copy string*/
      } else {
          compas_info[1][i] = ' '; /*Right padding*/
      }
  }

  /*Null-terminate the row*/
  compas_info[1][WIDTH_COMPASS - 1] = '\0';



  /*We paint the vertical arrow facing upwards*/
  memset(compas_info[2], ' ', WIDTH_COMPASS);
  compas_info[2][WIDTH_COMPASS / 2 - 1] = '^';
  compas_info[2][WIDTH_COMPASS - 1] = '\0';


  /*We paint the area in the middle*/
  space_name = (char *)space_get_name(game_get_space(game, west));
  space_name2 = (char *)space_get_name(game_get_space(game, east));
  if (!space_name) {
      space_name = blank_word;
  }
  if (!space_name2) {
      space_name2 = blank_word;
  }

  /* Calculate total width of the strings */
  total_width = strlen(space_name) + strlen(middle_str) + strlen(space_name2);

  /* Calculate left padding */
  middle_str_pos = WIDTH_COMPASS / 2 - strlen(middle_str) / 2 - 1;
  left_padding = middle_str_pos - strlen(space_name);

  /* Fill the row with spaces and copy the strings */
  for (i = 0; i < WIDTH_COMPASS - 1; i++) {
      if (i < left_padding) {
          compas_info[3][i] = ' '; /* Left padding */
      } else if (i < left_padding + strlen(space_name)) {
          compas_info[3][i] = space_name[i - left_padding]; /* Copy first string */
      } else if (i < left_padding + strlen(space_name) + strlen(middle_str)) {
          compas_info[3][i] = middle_str[i - left_padding - strlen(space_name)]; /* Copy middle string */
      } else if (i < left_padding + total_width) {
          compas_info[3][i] = space_name2[i - left_padding - strlen(space_name) - strlen(middle_str)]; /* Copy second string */
      } else {
          compas_info[3][i] = ' '; /* Right padding */
      }
  }

  /* Null-terminate the row */
  compas_info[3][WIDTH_COMPASS - 1] = '\0';




  /*We paint the vertical arrow facing downwards*/
  memset((void *)compas_info[4], (int)' ', WIDTH_COMPASS);
  compas_info[4][WIDTH_COMPASS/2 - 1] = 'v';
  compas_info[4][WIDTH_COMPASS - 1] = '\0';



  /*We paint the name of the south space in the lower part*/
  space_name = (char *)space_get_name(game_get_space(game, south));
  if(!space_name){
    space_name = blank_word;
  }
  /*Calculate left padding*/
  left_padding = (WIDTH_COMPASS - strlen(space_name)) / 2;

  /*Fill the row with spaces and copy the string*/
  for (i = 0; i < WIDTH_COMPASS - 1; i++) {
      if (i < left_padding) {
          compas_info[5][i] = ' '; /*Left padding*/
      } else if (i < left_padding + strlen(space_name)) {
          compas_info[5][i] = space_name[i - left_padding]; /*Copy string*/
      } else {
          compas_info[5][i] = ' '; /*Right padding*/
      }
  }

  /*Null-terminate the row*/
  compas_info[5][WIDTH_COMPASS - 1] = '\0';



  up_name = (char *)space_get_name(game_get_space(game, up));
  link_id = game_get_current_player_location(game) * 100 + up;
  if(!up_name) up_name = blank_word;
  else if (link_get_is_open(game_get_link(game, link_id)) == FALSE) up_name = unknown_str;
  
  down_name = (char *)space_get_name(game_get_space(game, down));
  link_id = game_get_current_player_location(game) * 100 + down;
  if(!down_name) down_name = blank_word;
  else if (link_get_is_open(game_get_link(game, link_id)) == FALSE) down_name = unknown_str;
  
  memset((void *)compas_info[6], (int)' ', WIDTH_COMPASS);
  sprintf(compas_info[6], "Up: %s  Down: %s", up_name, down_name);
  compas_info[6][WIDTH_COMPASS - 1] = '\0';


  return compas_info;
}


/*PUBLIC FUNCTIONS*/
Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
  {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_COMPASS + HEIGHT_MISSION + HEIGHT_BAN + HEIGHT_SEPARATOR + HEIGHT_SEPARATOR + HEIGHT_SEPARATOR, WIDTH_MISSION + WIDTH_SEPARATOR + WIDTH_SEPARATOR);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
  {
    return NULL;
  }

  ge->map = screen_area_init(WIDTH_DIALOGUE + WIDTH_SEPARATOR + WIDTH_SEPARATOR, HEIGHT_BAN + HEIGHT_MISSION + HEIGHT_SEPARATOR, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_SEPARATOR + WIDTH_DIALOGUE + WIDTH_SEPARATOR + WIDTH_MAP + WIDTH_SEPARATOR, HEIGHT_BAN + HEIGHT_MISSION + HEIGHT_SEPARATOR, WIDTH_DES, HEIGHT_DES);
  ge->dialogue = screen_area_init(1, HEIGHT_BAN + HEIGHT_MISSION + HEIGHT_SEPARATOR, WIDTH_DIALOGUE, HEIGHT_DIALOGUE);
  ge->compass = screen_area_init(1, HEIGHT_BAN + HEIGHT_MISSION + HEIGHT_SEPARATOR + HEIGHT_DIALOGUE + HEIGHT_SEPARATOR, WIDTH_COMPASS, HEIGHT_COMPASS);
  ge->banner = screen_area_init((int)((WIDTH_MISSION) / 2), 0, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(WIDTH_DIALOGUE + WIDTH_SEPARATOR + WIDTH_SEPARATOR, HEIGHT_BAN + HEIGHT_MISSION + HEIGHT_SEPARATOR + HEIGHT_MAP + HEIGHT_SEPARATOR, WIDTH_HLP, HEIGHT_HLP);
  ge->feedback = screen_area_init(WIDTH_SEPARATOR + WIDTH_DIALOGUE + WIDTH_SEPARATOR + WIDTH_MAP + WIDTH_SEPARATOR, HEIGHT_BAN + HEIGHT_MISSION + HEIGHT_SEPARATOR + HEIGHT_DES + HEIGHT_SEPARATOR, WIDTH_FEEDBACK, HEIGHT_FDB);
  ge->mission = screen_area_init(1, HEIGHT_BAN, WIDTH_MISSION, HEIGHT_MISSION);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->dialogue);
  screen_area_destroy(ge->compass);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_area_destroy(ge->mission);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, obj_loc = NO_ID, character_loc = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID, id_up=NO_ID, id_down=NO_ID, character_following;

  char **map_information = NULL, **compass_information=NULL;
  char str[MAX_STR], *object_name = NULL, *object_gdesc=NULL, *character_gdesc = NULL, *character_name = NULL;
  int i, character_hp;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  /*paint the dialogue and messages*/
  if(game_get_show_message(game) == TRUE){
    screen_area_puts(ge->dialogue, game_get_message(game));
  }else{
    screen_area_clear(ge->dialogue);
  }

  /*Paint the current mission*/
  screen_area_clear(ge->mission);
  sprintf(str, "CURRENT MISSION : %s", mission_get_name(game_get_current_mission_code(game)));
  screen_area_puts(ge->mission, str);
  sprintf(str, "CURRENT OBJECTIVE : %s", game_get_objective(game));
  screen_area_puts(ge->mission, str);


  /**************PAINT COMPAS ******************/
  id_act = game_get_current_player_location(game);
  id_north = game_get_connection(game, id_act, N);
  id_south = game_get_connection(game, id_act, S);
  id_east = game_get_connection(game, id_act, E);
  id_west = game_get_connection(game, id_act, W);
  id_up = game_get_connection(game, id_act, U);
  id_down = game_get_connection(game, id_act, D);
  compass_information = graphic_engine_paint_compass(game, id_north, id_south, id_west, id_east, id_up, id_down);
  for(i=0;i<HEIGHT_COMPASS;i++){
    screen_area_puts(ge->compass, compass_information[i]);
  }
  free(compass_information[0]);
  free(compass_information);



  /**************PAINT MAP AREA**************/
  sprintf(str, "Current space: %s (%ld)", space_get_name(game_get_space(game, id_act)), space_get_id(game_get_space(game, id_act)));
  screen_area_puts(ge->map, str);
  if ((id_act = game_get_current_player_location(game)) != NO_ID)
  {    
    map_information = space_get_gdesc(game_get_space(game, id_act));
    for (i = 0; i < N_TOTAL_ROWS_IN_SQUARE; i++)
    {
      screen_area_puts(ge->map, map_information[i]);
    }
  }

  /***
  **** printing all the information in the game description
  ***/
  screen_area_clear(ge->descript);
  /*For all the objects in the game, we print its location*/
  screen_area_puts(ge->descript, "----------------------------------------");
  screen_area_puts(ge->descript, "        GENERAL GAME INFORMATION: ");
  screen_area_puts(ge->descript, " "); /*Separator line*/

  screen_area_puts(ge->descript, " OBJECTS IN THE GAME:");
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object_name = object_get_name(game_get_object_in_pos(game, i));
    obj_loc = game_get_object_location(game, object_get_id(game_get_object_in_pos(game, i)));
    object_gdesc = object_get_gdesc(game_get_object_in_pos(game, i));
    if (obj_loc != NO_ID)
    {
      sprintf(str, " %s %s", object_name, object_gdesc);
      screen_area_puts(ge->descript, str);
      if(space_get_discovered(game_get_space(game, obj_loc)) == TRUE){
        sprintf(str, " - location:%d", (int)obj_loc);
      }else{
        sprintf(str, " - location:?");
      }
    
      screen_area_puts(ge->descript, str);
    }/*else{
      sprintf(str, " %s %s", object_name, object_gdesc);
      screen_area_puts(ge->descript, str);
    }*/
  }

  /*for all the characters, we print their location and health*/
  screen_area_puts(ge->descript, " "); /*Separator line*/
  screen_area_puts(ge->descript, " CHARACTERS IN THE GAME: ");
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    character_gdesc = character_get_gdesc(game_get_character(game, game_get_character_id_at(game, i)));
    character_name = character_get_name(game_get_character(game, game_get_character_id_at(game, i)));
    character_loc = game_get_character_location(game, game_get_character_id_at(game, i));
    character_hp = character_get_health(game_get_character(game, game_get_character_id_at(game, i)));
    character_following = character_get_following(game_get_character(game, game_get_character_id_at(game, i)));
    character_print(game_get_character(game, game_get_character_id_at(game, i)));
    if(space_get_discovered(game_get_space(game, character_loc)) == TRUE){
      sprintf(str, " %s %s", character_name, character_gdesc);
      screen_area_puts(ge->descript, str);
      sprintf(str, " - location:%d",(int)character_loc);
      screen_area_puts(ge->descript, str);
      sprintf(str, " - health: %d", character_hp >= 0? character_hp:0);
      screen_area_puts(ge->descript, str);
      sprintf(str, " - following: %ld", character_following);
    }else{
      sprintf(str, " %s %s  (?)", character_name, character_gdesc);
    }
    screen_area_puts(ge->descript, str);
  }
  /*We print the player, its location , health and then the object in the inventory*/

  screen_area_puts(ge->descript, " "); /*Separator line*/
  screen_area_puts(ge->descript, " PLAYER INFORMATION: ");
  sprintf(str, " Player(%s) %s: %d (%d)",player_get_name(game_get_current_player(game)), player_get_gdesc(game_get_current_player(game)), (int)game_get_current_player_location(game), player_get_health(game_get_current_player(game)));
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, " "); /*Separator line*/
  sprintf(str, " Objects in the inventory: ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < player_get_num_objects_in_backpack(game_get_current_player(game)); i++)
  {
    object_name = object_get_name(game_get_object(game, player_get_backpack_object_id_at(game_get_current_player(game), i)));
    obj_loc = game_get_object_location(game, (player_get_backpack_object_id_at(game_get_current_player(game), i)));
    object_gdesc = object_get_gdesc(game_get_object(game, player_get_backpack_object_id_at(game_get_current_player(game), i)));

    sprintf(str, " %s %s", object_name, object_gdesc);
    screen_area_puts(ge->descript, str);
    
  }
  screen_area_puts(ge->descript, "----------------------------------------");
  screen_area_puts(ge->descript, "       CURRENT SPACE INFORMATION: ");
  screen_area_puts(ge->descript, " "); /*Separator line*/

  sprintf(str, " Characters in the space: ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < space_get_n_characters(game_get_space(game, id_act)); i++){
    character_name = character_get_name(game_get_character(game, space_get_character_in_pos(game_get_space(game, id_act), i)));
    character_gdesc = character_get_gdesc(game_get_character(game, space_get_character_in_pos(game_get_space(game, id_act), i)));
    sprintf(str, " %s %s", character_name, character_gdesc);
    screen_area_puts(ge->descript, str);
  }



  sprintf(str, " Objects in the space: ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < space_get_num_of_objects(game_get_space(game, id_act)); i++){
    object_name = object_get_name(game_get_object(game, space_get_object_id_in_pos(game_get_space(game, id_act), i)));
    object_gdesc = object_get_gdesc(game_get_object(game, space_get_object_id_in_pos(game_get_space(game, id_act), i)));
    sprintf(str, " %s %s", object_name, object_gdesc);
    screen_area_puts(ge->descript, str);
  }
  /*Printing the description of the game, given after the command 'Inspect'*/
  if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT &&command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK)
  {
    sprintf(str, "Object description:");
    screen_area_puts(ge->descript, str);

    sprintf(str, "%s", game_get_description(game));
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  if(game_get_turn(game) == ALICE_TURN){
    screen_area_puts(ge->banner, "  House of legacy: Alice");
  }else{
    screen_area_puts(ge->banner, "  House of legacy: Bob");
  }

  /*Paint in the mission area*/
  


  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  screen_area_puts(ge->help, " - move 'dir' or m 'dir' - exit or e - take 'arg' or t 'arg' - drop 'arg' or d 'arg' - chat 'arg' or c 'arg' - attack 'arg' or at 'arg' - inspect 'arg' or i 'arg' - recruit 'arg' or r 'arg' - abandon 'arg' or ab 'arg' - ssave 'arg' or s 'arg' - load 'arg' or l 'arg' - team 'arg' or tm 'arg' - open 'arg' with 'arg' or o 'arg' with 'arg' - give 'arg' to 'arg' or g 'arg' to 'arg'");

  /* Paint in the feedback area */
  screen_area_puts(ge->feedback, "Player command history: ");
  screen_area_puts(ge->feedback, " ");
  graphic_interface_paint_feedback_for_pos(game, ge, THIRD_TO_LAST, str);
  screen_area_puts(ge->feedback, str);
  screen_area_puts(ge->feedback, " ");
  graphic_interface_paint_feedback_for_pos(game, ge, SECOND_TO_LAST, str);
  screen_area_puts(ge->feedback, str);
  screen_area_puts(ge->feedback, " ");
  graphic_interface_paint_feedback_for_pos(game, ge, LAST, str);
  screen_area_puts(ge->feedback, str);


  /*Print a message if the player dies and the game ends*/
  if (player_get_health(game_get_current_player(game)) == 0)
  {

    /*We print a death message according to the number of players in the game*/
    if(game_get_n_players(game) == 1){
      sprintf(str, "GAME OVER");
    }else{
      sprintf(str, "Jugador %d ha muerto!", (game_get_turn(game) + 1));
    }
    screen_area_puts(ge->feedback, str);
  }

  /* Dump to the terminal */
  screen_paint((game_get_turn(game)), game_get_lights_on(game));
  printf("prompt:> ");
}

void graphic_interface_paint_feedback_for_pos(Game *game, Graphic_engine*ge, CommandPosition pos, char *str){
  CommandCode cmd=NO_CMD;
  Status cmd_succ=ERROR;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if(!game || !ge || !str) return;

  cmd = command_get_code(game_interface_data_get_cmd_in_pos(game, pos));
  cmd_succ = command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, pos));
  if (cmd_succ == ERROR)
  {
    sprintf(str, " %s (%s) : ERROR (P%d)", cmd_to_str[cmd - NO_CMD][CMDL], cmd_to_str[cmd - NO_CMD][CMDS] , game_get_turn(game) + 1);
  }
  else
  {
    sprintf(str, " %s (%s) : OK (P%d)", cmd_to_str[cmd - NO_CMD][CMDL], cmd_to_str[cmd - NO_CMD][CMDS] , game_get_turn(game) + 1);
  }

  return;
}

void graphic_engine_clear_dialogue(Graphic_engine *ge){
  if(!ge) return;
  screen_area_clear(ge->dialogue);
  return;
}