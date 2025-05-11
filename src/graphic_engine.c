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
#define WIDTH_DIALOGUE 60                       /*!<Width of the dialogue box in the graphic interface*/
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

#define FINAL_CHARACTER 1                       /*!<Size corresponding to the \0 character of the string*/
#define ARROW_SIZE 1                            /*!<Size corresponding to the arrow characters*/
#define MAX_STR 255                             /*!<The maximum characters of a line*/
/**
 * @brief Describes the positions of the array that contains each of the rows in the compass area
 * @author Matteo Artunedo
 */
typedef enum {
  COMPASS_TOP_BORDER = 0,   /*!< Top border of the compass */
  NORTH_POSITION,           /*!< Row for the north space name */
  NORTH_ARROW,              /*!< Row for the upward arrow */
  MIDDLE_ROW,               /*!< Row for the middle (west, center, east) */
  SOUTH_ARROW,              /*!< Row for the downward arrow */
  SOUTH_POSITION,           /*!< Row for the south space name */
  UP_DOWN_ROW               /*!< Row for the up and down space names */
} CompassRow;


/**
 * @brief macro function that halves a given length
 * @author Matteo Artunedo
 */
#define halve_length(len) ((len)/2)

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
 * @brief Paints the compass with the names of the spaces in the specified directions
 * (square left down on the screen). It generates a visual representation showing the names of the spaces
 * in the north, south, west, east, up, and down directions relative to the current game state.
 * @author Matteo Artunedo 
 *
 * @param game Pointer to the Game structure.
 * @param north ID of the space to the north.
 * @param south ID of the space to the south.
 * @param west ID of the space to the west.
 * @param east ID of the space to the east.
 * @param up ID of the space above.
 * @param down ID of the space below.
 * @return A 2D array of characters representing the compass for orientation, or NULL if an error occurs.
 */
char **graphic_engine_paint_compass(Game *game, Id north, Id south, Id west, Id east, Id up, Id down);


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
  char **compas_info = NULL, *space_name = NULL, *space_name2 = NULL, middle_str[] = "< + >", blank_word[] = " ", unknown_str[] = "???", *up_name = NULL, *down_name = NULL;
  int i=0, left_padding=0, total_width=0, middle_str_pos=0;
  long link_id=NO_ID;
  /*Error control*/
  if (!game)
  {
    return NULL;
  }
  /*Create the two-dimensional array*/
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

  /*Paint the top border of the compass*/
  memset((void *)compas_info[COMPASS_TOP_BORDER], (int)' ', WIDTH_COMPASS);
  compas_info[COMPASS_TOP_BORDER][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

  /*We paint the name of the north space in the upper part*/
  space_name = (char *)space_get_name(game_get_space(game, north));
  link_id = get_link_id(game_get_current_player_location(game), north);
  if (!space_name)
  {
    space_name = blank_word;
  }else if (link_get_is_open(game_get_link(game, link_id)) == FALSE && link_id < MIN_ID_FOR_FLASHBACK){
    space_name = unknown_str;
  }
    
  /* Calculate left padding */
  left_padding = halve_length(WIDTH_COMPASS - strlen(space_name));

  /* Fill the row with spaces and copy the string */
  for (i = 0; i < WIDTH_COMPASS - FINAL_CHARACTER; i++)
  {
    if (i < left_padding)
    {
      compas_info[NORTH_POSITION][i] = ' '; /* Left padding */
    }
    else if (i < left_padding + strlen(space_name))
    {
      compas_info[NORTH_POSITION][i] = space_name[i - left_padding]; /* Copy string */
    }
    else
    {
      compas_info[NORTH_POSITION][i] = ' '; /* Right padding */
    }
  }

  /* Null-terminate the row */
  compas_info[NORTH_POSITION][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

  /* We paint the vertical arrow facing upwards */
  memset(compas_info[NORTH_ARROW], ' ', WIDTH_COMPASS);
  compas_info[NORTH_ARROW][halve_length(WIDTH_COMPASS) - FINAL_CHARACTER] = '^';
  compas_info[NORTH_ARROW][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

  /*We paint the area in the middle*/
  space_name = (char *)space_get_name(game_get_space(game, west));
  space_name2 = (char *)space_get_name(game_get_space(game, east));
  
  link_id = get_link_id(game_get_current_player_location(game), west);
  if (!space_name)
  {
    space_name = blank_word;
  }else if (link_get_is_open(game_get_link(game, link_id)) == FALSE && link_id < MIN_ID_FOR_FLASHBACK){
    space_name = unknown_str;
  }

  link_id = get_link_id(game_get_current_player_location(game), east);
  if (!space_name2)
  {
    space_name2 = blank_word;
  }else if (link_get_is_open(game_get_link(game, link_id)) == FALSE && link_id < MIN_ID_FOR_FLASHBACK){
    space_name2 = unknown_str;
  }

  /* Calculate total width of the strings */
  total_width = strlen(space_name) + strlen(middle_str) + strlen(space_name2);

  /* Calculate left padding */
  middle_str_pos = halve_length(WIDTH_COMPASS) - halve_length(strlen(middle_str)) - FINAL_CHARACTER;
  left_padding = middle_str_pos - strlen(space_name);

  /* Fill the row with spaces and copy the strings */
  for (i = 0; i < WIDTH_COMPASS - FINAL_CHARACTER; i++)
  {
    if (i < left_padding)
    {
      compas_info[MIDDLE_ROW][i] = ' '; /* Left padding */
    }
    else if (i < left_padding + strlen(space_name))
    {
      compas_info[MIDDLE_ROW][i] = space_name[i - left_padding]; /* Copy first string */
    }
    else if (i < left_padding + strlen(space_name) + strlen(middle_str))
    {
      compas_info[MIDDLE_ROW][i] = middle_str[i - left_padding - strlen(space_name)]; /* Copy middle string */
    }
    else if (i < left_padding + total_width)
    {
      compas_info[MIDDLE_ROW][i] = space_name2[i - left_padding - strlen(space_name) - strlen(middle_str)]; /* Copy second string */
    }
    else
    {
      compas_info[MIDDLE_ROW][i] = ' '; /* Right padding */
    }
  }

  /* Null-terminate the row */
  compas_info[MIDDLE_ROW][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

  /* We paint the vertical arrow facing downwards */
  memset((void *)compas_info[SOUTH_ARROW], (int)' ', WIDTH_COMPASS);
  compas_info[SOUTH_ARROW][halve_length(WIDTH_COMPASS) - FINAL_CHARACTER] = 'v';
  compas_info[SOUTH_ARROW][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

  /*We paint the name of the south space in the lower part*/
  space_name = (char *)space_get_name(game_get_space(game, south));
  link_id = get_link_id(game_get_current_player_location(game), south);
  if (!space_name)
  {
    space_name = blank_word;
  }else if (link_get_is_open(game_get_link(game, link_id)) == FALSE && link_id < MIN_ID_FOR_FLASHBACK){
    space_name = unknown_str;
  }
  /* Calculate left padding */
  left_padding = halve_length(WIDTH_COMPASS - strlen(space_name));

  /* Fill the row with spaces and copy the string */
  for (i = 0; i < WIDTH_COMPASS - FINAL_CHARACTER; i++)
  {
    if (i < left_padding)
    {
      compas_info[SOUTH_POSITION][i] = ' '; /* Left padding */
    }
    else if (i < left_padding + strlen(space_name))
    {
      compas_info[SOUTH_POSITION][i] = space_name[i - left_padding]; /* Copy string */
    }
    else
    {
      compas_info[SOUTH_POSITION][i] = ' '; /* Right padding */
    }
  }

  /* Null-terminate the row */
  compas_info[SOUTH_POSITION][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

  /* Paint up and down names */
  up_name = (char *)space_get_name(game_get_space(game, up));
  link_id = get_link_id(game_get_current_player_location(game), up);
  if (!up_name)
    up_name = blank_word;
  else if (link_get_is_open(game_get_link(game, link_id)) == FALSE)
    up_name = unknown_str;

  down_name = (char *)space_get_name(game_get_space(game, down));
  link_id = get_link_id(game_get_current_player_location(game), down);
  if (!down_name)
    down_name = blank_word;
  else if (link_get_is_open(game_get_link(game, link_id)) == FALSE)
    down_name = unknown_str;

  memset((void *)compas_info[UP_DOWN_ROW], (int)' ', WIDTH_COMPASS);
  sprintf(compas_info[UP_DOWN_ROW], "Up: %s  Down: %s", up_name, down_name);
  compas_info[UP_DOWN_ROW][WIDTH_COMPASS - FINAL_CHARACTER] = '\0';

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
  ge->banner = screen_area_init((int)(halve_length(WIDTH_MISSION)), 0, WIDTH_BAN, HEIGHT_BAN);
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
  Id id_act = NO_ID, obj_loc = NO_ID, character_loc = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID, id_up=NO_ID, id_down=NO_ID, character_following = NO_ID, open_id = NO_ID, depend_id = NO_ID;
  char **map_information = NULL, **compass_information=NULL;
  char str[MAX_STR], *object_name = NULL, *object_gdesc=NULL, *character_gdesc = NULL, *character_name = NULL;
  int i, character_hp, obj_hp;
  /* Paint the in the map area */
  screen_area_clear(ge->map);

  /*paint the dialogue and messages*/
  if(game_get_current_cinematic(game) == NO_CINEMATIC){
    screen_area_clear(ge->dialogue);
  }
  if(game_get_show_message(game, game_get_turn(game)) == TRUE){
    screen_area_puts(ge->dialogue, game_get_message(game, game_get_turn(game)));
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

  screen_area_puts(ge->descript, " OBJECTS IN THE CURRENT FLOOR:");
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    obj_loc = game_get_object_location(game, object_get_id(game_get_object_in_pos(game, i)));
    /*We check that either the object is in the same floor as the player or it is in the player's backpack*/
    if ((obj_loc != NO_ID && (space_get_floor(obj_loc) == space_get_floor(id_act))) || player_backpack_contains(game_get_current_player(game),  object_get_id(game_get_object_in_pos(game, i))))
    {
      object_name = object_get_name(game_get_object_in_pos(game, i));
      object_gdesc = object_get_gdesc(game_get_object_in_pos(game, i));
      obj_hp = object_get_health(game_get_object_in_pos(game, i));
      open_id = object_get_open(game_get_object_in_pos(game, i));
      depend_id = object_get_dependency(game_get_object_in_pos(game, i));
      sprintf(str, " %s %s", object_name, object_gdesc);
      screen_area_puts(ge->descript, str);
      /*We print the object's information only if it is in a discovered space or in the backpack*/
      if(space_get_discovered(game_get_space(game, obj_loc)) == TRUE || obj_loc == NO_ID){
        /*If the location id is NO_ID, it means the object is in the backpack*/
        if(obj_loc == NO_ID){
          sprintf(str, " - location: backpack");
        }else{
          sprintf(str, " - location: %d", (int)obj_loc);
        }
        screen_area_puts(ge->descript, str);
        switch(object_get_movable(game_get_object_in_pos(game, i))){
          case TRUE:
            sprintf(str, " - movable: YES");
            break;
          default:
            sprintf(str, " - movable: NO");
            break;
        }
        screen_area_puts(ge->descript, str);
        /*If the object heals, we print the hp it gives*/
        if(obj_hp > 0){
          sprintf(str, " - HP the object gives: %d", obj_hp);
          screen_area_puts(ge->descript, str);
        }
  
        if(open_id != NO_ID){
          sprintf(str, " - link the object opens: %s", link_get_name(game_get_link(game, open_id)));
          screen_area_puts(ge->descript, str);
        }
  
        if(depend_id != NO_ID){
          sprintf(str, " - object depends of: %s", object_get_name(game_get_object(game, depend_id)));
          screen_area_puts(ge->descript, str);
        }
      }else 
      {
        sprintf(str, " - location:?");
        screen_area_puts(ge->descript, str);
      }  
    }
  }

  

  /*for all the characters, we print their location and health*/
  screen_area_puts(ge->descript, " "); /*Separator line*/
  screen_area_puts(ge->descript, " CHARACTERS IN THE CURRENT FLOOR: ");
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    character_loc = game_get_character_location(game, game_get_character_id_at(game, i));
    character_hp = character_get_health(game_get_character(game, game_get_character_id_at(game, i)));

    if(character_hp > 0 && space_get_floor(id_act) == space_get_floor(character_loc)){
      /*We get the rest of the character's information*/
      character_name = character_get_name(game_get_character(game, game_get_character_id_at(game, i)));
      character_gdesc = character_hp > 0? character_get_gdesc(game_get_character(game, game_get_character_id_at(game, i))):character_get_dead_gdesc(game_get_character(game, game_get_character_id_at(game, i)));
      character_following = character_get_following(game_get_character(game, game_get_character_id_at(game, i)));
      if(space_get_discovered(game_get_space(game, character_loc)) == TRUE){
        sprintf(str, " %s %s", character_name, character_gdesc);
        screen_area_puts(ge->descript, str);
        sprintf(str, " - location:%d",(int)character_loc);
        screen_area_puts(ge->descript, str);
        sprintf(str, " - health: %d", character_hp >= 0? character_hp:0);
        screen_area_puts(ge->descript, str);
        if(character_following != NO_ID){
          sprintf(str, " - following: %s", player_get_name(game_get_player(game, character_following)));
          screen_area_puts(ge->descript, str);
        }
        if(character_get_friendly(game_get_character(game, game_get_character_id_at(game, i))) == TRUE){
          sprintf(str, " - friendly: YES");
        }else{
          sprintf(str, " - friendly: NO");
        }
        screen_area_puts(ge->descript, str);
      }else{
        sprintf(str, " %s %s  (?)", character_name, character_gdesc);
        screen_area_puts(ge->descript, str);
      }
    }

  }
  /*We print the player, its location , health and then the object in the inventory*/

  screen_area_puts(ge->descript, " "); /*Separator line*/
  screen_area_puts(ge->descript, " PLAYER INFORMATION: ");
  sprintf(str, " Player(%s) %s  hp: %d",player_get_name(game_get_current_player(game)), player_get_gdesc(game_get_current_player(game)), player_get_health(game_get_current_player(game)));
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, " "); /*Separator line*/
  sprintf(str, " Objects in the inventory: (%d/%d)", player_get_num_objects_in_backpack(game_get_current_player(game)), inventory_get_max_objs(player_get_inventory(game_get_current_player(game))));
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
    character_hp = character_get_health(game_get_character(game, space_get_character_in_pos(game_get_space(game, id_act), i)));
    if(character_hp > 0){
      character_name = character_get_name(game_get_character(game, space_get_character_in_pos(game_get_space(game, id_act), i)));
      character_gdesc = character_get_gdesc(game_get_character(game, space_get_character_in_pos(game_get_space(game, id_act), i)));
      sprintf(str, " %s %s", character_name, character_gdesc);
      screen_area_puts(ge->descript, str);
    }
  }

  screen_area_puts(ge->descript, " "); /*Separator line*/

  sprintf(str, " Objects in the space: ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < space_get_num_of_objects(game_get_space(game, id_act)); i++){
    object_name = object_get_name(game_get_object(game, space_get_object_id_in_pos(game_get_space(game, id_act), i)));
    object_gdesc = object_get_gdesc(game_get_object(game, space_get_object_id_in_pos(game_get_space(game, id_act), i)));
    sprintf(str, " - %s %s", object_name, object_gdesc);
    screen_area_puts(ge->descript, str);
    
  }
  
  /*Printing the description of the game, given after the command 'Inspect'*/
  if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK)
  {
    sprintf(str, "Object description: %s", game_get_description(game));
    screen_area_puts(ge->dialogue, str);

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
  screen_area_puts(ge->help, " GENERAL COMMANDS: move 'dir' or m 'dir'| exit or e | save 'file' or s 'file' | load 'file' or l 'file'");
  screen_area_puts(ge->help, " OBJECT RELATED: take 'obj' or t 'obj' | drop 'obj' or d 'obj' | inspect 'obj' or i 'obj' | open 'link' with 'obj' or o 'link' with 'obj'");
  screen_area_puts(ge->help, " CHARACTER RELATED: chat 'ch' or c 'ch' | attack 'ch' or at 'ch' | recruit 'ch' or r 'ch' | abandon 'ch' or ab 'ch' | team 'ch' or tm 'ch'");
  screen_area_puts(ge->help, " PLAYER RELATED: give 'obj' to 'player' or g 'obj' to 'player' | turn or tu");

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
