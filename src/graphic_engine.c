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
#define WIDTH_MAP 60              /*!<Width of the map in the graphic interface*/
#define WIDTH_DES 29              /*!<Width of the description box in the graphic interface*/
#define WIDTH_BAN 23              /*!<Width of the banner in the graphic interface*/
#define HEIGHT_MAP 29             /*!<Height of the map in the graphic interface*/
#define HEIGHT_BAN 1              /*!<Height of the banner in the graphic interface*/
#define HEIGHT_HLP 2              /*!<Height of the help box in the graphic interface*/
#define HEIGHT_FDB 3              /*!<Height of the feedback box in the graphic interface*/
#define NUMBER_OF_BARS 2          /*!<Number and size of the '|' at the sides of the squares*/
#define SIZE_OF_SPACE 2           /*!<Size of the chars ' ,' between each object name*/
#define FINAL_CHARACTER 1         /*!<Size corresponding to the \0 character of the string*/
#define BOTTOM_HEIGHT 1           /*!<Height of the lowest line of spaces in the map*/
#define MIDDLE_HEIGHT 2           /*!<Height of the middle line of spaces in the map*/
#define TOP_HEIGHT 3              /*!<Height of the highest line of spaces in the map*/
#define GDESC_INITIAL_POSITION 2  /*!<The position the first line of the graphic description of a space has in the total space square*/
#define GDESC_FINAL_POSITION 7    /*!<The position the last line of the graphic description of a space has in the total space square*/
#define MAX_STR 255               /*The maximum characters of a line*/

/**
 * @brief structure where the pointers to all the areas of the textual graphic interface are stored
 *
 * @date 27-01-2025
 * @author Profesores
 */
struct _Graphic_engine
{
  Area 
  *map,       /*Map area of the graphic engine. Here we can see the players, objects, spaces, graphical descriptions, etc*/
  *descript,  /*Description area of the graphic engine. Here the player can get info about the game such as object and character placement, his health, etc*/
  *banner,    /*Title area in the graphic engine. Here we can see the title of the game and the player who is currently playing*/
  *help,      /*Help area of the graphic engine. Here all of the possible commands a player can run are displayed*/
  *feedback;  /*Feedback area in the graphic engine. Here the player can see the commands he has executed and if they were succesful*/
};

/**
 * @brief Set the values of the arrows in the space
 *
 * @author Matteo Artunedo
 * @date 14-3-25
 *
 * @param game pointer to the game
 * @param spaceId id of the space where the character is located
 * @param north1 arrow that connects the west space with its north
 * @param south1 arrow that connects the west space with its south
 * @param north2 arrow that connects the player's space with its south
 * @param south2 arrow that connects the player's space with its south
 * @param north3 arrow that connects the east space with its south
 * @param south3 arrow that connects the east space with its south
 * @return Status
 */
Status graphic_engine_set_arrows(Game *game, Id spaceId, char *north1, char *south1, char *north2, char *south2, char *north3, char *south3);

/**
 * @brief Create a line of spaces (3 space squares placed horizontally one after the other)
 * @author Matteo Artunedo
 * @param game pointer to the game structure
 * @param id_center the id of the space that will be in the center of the line
 * @param id_player the id of where the player is located
 * @param height 1 if the line being created is the last one that is printed in the map box, 2 if it is the middle line and 3 if it is the top line
 * @return char** matrix with the complete line
 */
char **graphic_engine_create_line_of_spaces(Game *game, Id id_center, Id id_player, int height);

/**
 * @brief Create a square space description for the space with the given id
 * @author Matteo Artunedo
 * @param game pointer to the game structure
 * @param square_id id of the space which corresponds to the box being created
 * @return char** matrix with the square of the space that will be printed on the screen
 */
char **graphic_engine_create_space_square(Game *game, Id square_id);

/**
 * @brief returns the id of the space that is at the side of id_center
 * @author Matteo Artunedo
 * @param game pointer to game
 * @param id_player id of the space where the player is located
 * @param d direction used to look for the adjacent square (W or E)
 * @param height 1 if it is the last line that is printed in the map box, 2 if it is the middle line and 3 if it is the top line
 * @return Id of the adjacent space
 */
Id graphic_engine_horizontally_adjacent_square(Game *game, Id id_player, Direction d, int height);

/**
 * @brief returns the id of the space that is at the vertically adjacent to id_center
 * @author Matteo Artunedo
 * @param game pointer to game
 * @param id_player id of the space where the player is located
 * @param d direction used to look for the adjacent square (N or S)
 * @return Id of the vertically adjacent space
 */
Id graphic_engine_vertically_adjacent_square(Game *game, Id id_center, Direction d);

/**
 * @brief Paints the feedback of one command in the player command history
 * 
 * @param game pointer to the game
 * @param ge pointer to the graphic engine
 * @param pos position of thecommand (whether we want to print the last command, the second to last or the third to last)
 */
char *graphic_interface_paint_feedback_for_pos(Game *game, Graphic_engine*ge, CommandPosition pos);

/*PRIVATE FUNCTIONS*/
Status graphic_engine_set_arrows(Game *game, Id spaceId, char *north1, char *south1, char *north2, char *south2, char *north3, char *south3)
{
  Id id_east = NO_ID, id_west = NO_ID, id_north = NO_ID, id_south = NO_ID;
  id_north = game_get_connection(game, spaceId, N);
  id_south = game_get_connection(game, spaceId, S);
  id_east = game_get_connection(game, spaceId, E);
  id_west = game_get_connection(game, spaceId, W);

  if (!game || !north1 || !south1 || !north2 || !south2 || !north3 || !south3)
  {
    return ERROR;
  }

  if (id_north != NO_ID)
  {
    *north2 = '^';
  }
  if (id_south != NO_ID)
  {
    *south2 = 'v';
  }

  if (id_west == NO_ID)
  {
    id_west = graphic_engine_horizontally_adjacent_square(game, spaceId, W, MIDDLE_HEIGHT);
  }
  if (id_east == NO_ID)
  {
    id_east = graphic_engine_horizontally_adjacent_square(game, spaceId, E, MIDDLE_HEIGHT);
  }

  /*Estudiamos si el espacio al este del espacio del jugador tiene norte y/o sur, poniendo las flechas acorde a esa información*/
  if (game_get_connection(game, id_east, N) != NO_ID)
  {
    *north3 = '^';
  }
  if (game_get_connection(game, id_east, S) != NO_ID)
  {
    *south3 = 'v';
  }
  /*Estudiamos si el espacio al oeste del espacio del jugador tiene norte y/o sur, poniendo las flechas acorde a esa información*/
  if (game_get_connection(game, id_west, N) != NO_ID)
  {
    *north1 = '^';
  }
  if (game_get_connection(game, id_west, S) != NO_ID)
  {
    *south1 = 'v';
  }
  return OK;
}

char **graphic_engine_create_space_square(Game *game, Id square_id)
{
  char **space_square = NULL, str[MAX_STR], blank_player_str[] = "   ", **gdesc, *player, object[N_TOTAL_ROWS_IN_SQUARE - FINAL_CHARACTER], character[GDESCTAM], blank_character_str[] = "      "; /*Quitar este número mágico*/
  Space *space;
  Object *object_in_pos = NULL;
  Bool discovered=space_get_discovered(game_get_space(game, square_id));
  int i, len_printed = 0;

  /*El puntero a espacio que le corresponde al cuadrado que vamos a crear*/
  space = game_get_space(game, square_id);

  /*Creamos la matriz en la que guardaremos la información del cuadrado*/
  if (!(space_square = (char **)calloc(N_TOTAL_LINES_IN_SQUARE, sizeof(char *))))
  {
    return NULL;
  }
  if (!(space_square[0] = (char *)calloc(N_TOTAL_LINES_IN_SQUARE * (N_TOTAL_ROWS_IN_SQUARE + FINAL_CHARACTER), sizeof(char))))
  {
    free(space_square);
    return NULL;
  }

  for (i = 1; i < N_TOTAL_LINES_IN_SQUARE; i++)
  {
    space_square[i] = space_square[0] + (N_TOTAL_ROWS_IN_SQUARE + 1) * i;
  }

  /*Ponemos todo el cuadrado en blanco si el id del espacio es NO_ID*/
  if (square_id == NO_ID)
  {
    for (i = 0; i < N_TOTAL_LINES_IN_SQUARE; i++)
    {
      strcpy(space_square[i], "                 ");
    }
  }
  /*Si es un id válido, vamos imprimiendo las distintas partes del espacio*/
  else
  {
    /*Damos un valor a player según si el jugador está en el espacio o no*/
    if (game_get_current_player_location(game) == square_id)
    {
      player = player_get_gdesc(game_get_current_player(game));
    }
    else
    {
      player = blank_player_str;
    }
    /*Damos un valor al personaje del espacio si lo hay*/
    if (space_get_character(space) == NO_ID || discovered == FALSE)
    {
      strcpy(character, blank_character_str);
    }
    else
    {
      strcpy(character, character_get_gdesc(game_get_character(game, space_get_character(space))));
    }


   
    for(i = 0; i < space_get_num_of_objects(space); i++){
      object_in_pos = game_get_object(game, space_get_object_id_in_pos(space, i));

      /*We print the list of names, taking care we dont overflow the object string*/
      if ((len_printed + strlen(object_get_name(object_in_pos))) > (N_TOTAL_ROWS_IN_SQUARE - NUMBER_OF_BARS - SIZE_OF_SPACE))
      {
        /*If the next name doest fit, we print ... to show there are more objects*/
        while (len_printed < N_TOTAL_ROWS_IN_SQUARE - NUMBER_OF_BARS)
        {
          len_printed += sprintf(object + len_printed, ".");
        }
      }
      else
      {
        /*If the name fits, we print it, if its not the first name, print ' ,' first*/
        if (len_printed == 0)
        {
          len_printed += sprintf(object + len_printed, "%s", object_get_name(object_in_pos));
        }
        else
        {
          len_printed += sprintf(object + len_printed, ", %s", object_get_name(object_in_pos));
        }
      }
    }
   
    /*If there are no more objects to print, we fill the string with spaces*/
    while (len_printed < N_TOTAL_ROWS_IN_SQUARE - NUMBER_OF_BARS)
    {
      len_printed += sprintf(object + len_printed, " ");
    }

    gdesc = space_get_gdesc(space);
    /*Imprimimos la descripción gráfica del espacio (esté esta en blanco o con dibujos)*/
    sprintf(str, "+---------------+");
    strcpy(space_square[0], str);
    if (square_id < MIN_VALUE_WITH_THREE_NUMBERS)
    {
      sprintf(str, "| %s  %s %2d|", player, character, (int)square_id);
      strcpy(space_square[1], str);
    }
    else
    {
      sprintf(str, "| %s %s %2d|", player, character, (int)square_id);
      strcpy(space_square[1], str);
    }
    if(discovered == TRUE)
    {
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
      sprintf(str, "|%s|", object);
      strcpy(space_square[7], str);
    }
    else
    {
      for(i=GDESC_INITIAL_POSITION;i<=GDESC_FINAL_POSITION;i++){
        sprintf(str, "|               |");
        strcpy(space_square[i], str);
      }
    }
    sprintf(str, "+---------------+");
    strcpy(space_square[8], str);
  }

  return space_square;
}

Id graphic_engine_vertically_adjacent_square(Game *game, Id id_center, Direction d)
{
  Id found_id = NO_ID;
  found_id = game_get_connection(game, game_get_connection(game, game_get_connection(game, id_center, E), d), W);
  if (found_id == NO_ID)
  {
    found_id = game_get_connection(game, game_get_connection(game, game_get_connection(game, id_center, W), d), E);
  }
  return found_id;
}

Id graphic_engine_horizontally_adjacent_square(Game *game, Id id_player, Direction d, int height)
{
  Id found_id = NO_ID;
  /*Buscamos si el espacio situado a la derecha o la izquierda (según la función space_get que se pase como argumento) existe mediante caminos más complejos. De este modo, podemos imprimir el espacio aunque no haya acceso directo desde el espacio del centro de la línea*/
  if (height == TOP_HEIGHT)
  {
    /*Si la línea que se está imprimiendo es la superior, probamos a llegar al espacio de la derecha/izquierda desde el espacio del jugador, moviéndonos primero a la derecha/izquierda y después subiendo*/
    found_id = game_get_connection(game, game_get_connection(game, id_player, d), N);
  }
  else if (height == BOTTOM_HEIGHT)
  {
    /*Si la línea que se está imprimiendo es la inferior, probamos a llegar al espacio de la derecha/izquierda desde el espacio del jugador, moviéndonos primero a la derecha/izquierda y después bajando*/
    found_id = game_get_connection(game, game_get_connection(game, id_player, d), S);
  }
  else if (height == MIDDLE_HEIGHT)
  {
    /*En caso de que el la línea sea la del centro, probamos ambos caminos, tanto el que sube al final como el que baja*/
    found_id = game_get_connection(game, game_get_connection(game, game_get_connection(game, id_player, S), d), N);
    if (found_id == NO_ID)
    {
      found_id = game_get_connection(game, game_get_connection(game, game_get_connection(game, id_player, N), d), S);
    }
  }
  return found_id;
}

char **graphic_engine_create_line_of_spaces(Game *game, Id id_center, Id id_player, int height)
{
  char **gdesc_line = NULL, **left_square = NULL, **center_square = NULL, **right_square = NULL, str[MAX_STR], left_square_arrow = ' ', right_square_arrow = ' ';
  int i;
  Id id_left, id_right;

  /*OBTENCION DE LOS ID_LEFT E ID_RIGHT*/

  /*Obtenemos los id's del espacio a la izquierda y la derecha del que se nos ha pasado*/
  id_left = game_get_connection(game, id_center, W);
  id_right = game_get_connection(game, id_center, E);

  /*Si el espacio del centro tiene conexión directa con el de la derecha, imprimiremos una flecha*/
  if (id_right != NO_ID)
  {
    right_square_arrow = '>';
  }
  else
  {
    /*Buscamos si existe el espacio desde otros caminos*/
    id_right = graphic_engine_horizontally_adjacent_square(game, id_player, E, height);
  }

  /*Si el espacio del centro tiene conexión directa con el de la izquierda, imprimiremos una flecha*/
  if (id_left != NO_ID)
  {
    left_square_arrow = '<';
  }
  else
  {
    /*Buscamos si existe el espacio desde otros caminos*/
    id_left = graphic_engine_horizontally_adjacent_square(game, id_player, W, height);
  }

  /*FIN DE LA OBTENCIÓN DE LOS ID_LEFT E ID_RIGHT*/

  /*Create the matrix to store the entire line*/
  if (!(gdesc_line = (char **)calloc(N_TOTAL_LINES_IN_3_SQUARES, sizeof(char *))))
  {
    return NULL;
  }
  if (!(gdesc_line[0] = (char *)calloc(N_TOTAL_LINES_IN_3_SQUARES * (N_TOTAL_ROWS_IN_3_SQUARES + FINAL_CHARACTER), sizeof(char))))
  {
    free(gdesc_line);
    return NULL;
  }
  for (i = 1; i < N_TOTAL_LINES_IN_3_SQUARES; i++)
  {
    gdesc_line[i] = gdesc_line[0] + (N_TOTAL_ROWS_IN_3_SQUARES + 1) * i;
  }
  /*End of creating the matrix*/

  left_square = graphic_engine_create_space_square(game, id_left);
  center_square = graphic_engine_create_space_square(game, id_center);
  right_square = graphic_engine_create_space_square(game, id_right);

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

  /*Liberamos la memoria para los cuadrados desde los que hemos copiado el contenido*/
  if (left_square)
  {
    if (left_square[0])
    {
      free(left_square[0]);
    }
    free(left_square);
  }

  if (center_square)
  {
    if (center_square[0])
    {
      free(center_square[0]);
    }
    free(center_square);
  }

  if (right_square)
  {
    if (right_square[0])
    {
      free(right_square[0]);
    }
    free(right_square);
  }
  /*End of creating the lines*/
  return gdesc_line;
}
/*END OF PRIVATE FUNCTIONS*/

/*PUBLIC FUNCTIONS*/
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
  Id id_act = NO_ID, obj_loc = NO_ID, character_loc = NO_ID, id_north = NO_ID, id_south = NO_ID;

  char **created_line = NULL;
  char str[MAX_STR], *object_name = NULL, *character_gdesc = NULL, north_arrow1 = ' ', south_arrow1 = ' ', north_arrow2 = ' ', south_arrow2 = ' ', north_arrow3 = ' ', south_arrow3 = ' ';
  int i, character_hp;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_current_player_location(game)) != NO_ID)
  {
    id_north = game_get_connection(game, id_act, N);
    id_south = game_get_connection(game, id_act, S);
    graphic_engine_set_arrows(game, id_act, &north_arrow1, &south_arrow1, &north_arrow2, &south_arrow2, &north_arrow3, &south_arrow3);
    if (id_north == NO_ID)
    {
      /*Probamos a llegar al norte desde caminos alternativos*/
      id_north = graphic_engine_vertically_adjacent_square(game, id_act, N);
    }
    if (id_south == NO_ID)
    {
      /*Probamos a llega al sur desde caminos alternativos*/
      id_south = graphic_engine_vertically_adjacent_square(game, id_act, S);
    }

    /*araña muerta se imprime del reves, no es necesario pero mejora la experiencia de juego*/
    
    if (character_get_health(game_get_character_from_name(game, "spider")) == 0)
    {
      character_set_gdesc(game_get_character_from_name(game, "spider"), "\\/xx\\/");
    }
    /*fin del cambio grafico para la araña muerta*/

    /*Imprimimos la primera línea de espacios */
    created_line = graphic_engine_create_line_of_spaces(game, id_north, id_act, TOP_HEIGHT);
    screen_area_puts(ge->map, created_line[0]);
    if (created_line != NULL)
    {
      for (i = 0; i < N_TOTAL_LINES_IN_3_SQUARES; i++)
      {
        screen_area_puts(ge->map, created_line[i]);
      }
    }
    free(created_line[0]);
    free(created_line);
    created_line = NULL;

    /*Imprimimos las flechas que unen la primera línea con la segunda*/
    sprintf(str, "        %c                  %c                  %c          ", north_arrow1, north_arrow2, north_arrow3);
    screen_area_puts(ge->map, str);

    /*Imprimimos la segunda línea de espacios*/
    created_line = graphic_engine_create_line_of_spaces(game, id_act, id_act, MIDDLE_HEIGHT);
    for (i = 0; i < N_TOTAL_LINES_IN_3_SQUARES; i++)
    {
      screen_area_puts(ge->map, created_line[i]);
    }
    free(created_line[0]);
    free(created_line);
    created_line = NULL;

    /*Imprimimos las flechas que unen la segunda línea con la tercera*/
    sprintf(str, "        %c                  %c                  %c          ", south_arrow1, south_arrow2, south_arrow3);
    screen_area_puts(ge->map, str);

    /*Imprimimos la segunda línea de espacios*/
    created_line = graphic_engine_create_line_of_spaces(game, id_south, id_act, BOTTOM_HEIGHT);
    for (i = 0; i < N_TOTAL_LINES_IN_3_SQUARES; i++)
    {
      screen_area_puts(ge->map, created_line[i]);
    }
    free(created_line[0]);
    free(created_line);
    created_line = NULL;
  }

  /***
  **** printing all the information in the game description
  ***/
  screen_area_clear(ge->descript);
  /*For all the objects in the game, we print its location*/

  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object_name = object_get_name(game_get_object_in_pos(game, i));
    obj_loc = game_get_object_location(game, object_get_id(game_get_object_in_pos(game, i)));
    if (obj_loc != NO_ID)
    {
      if(space_get_discovered(game_get_space(game, obj_loc)) == TRUE){
        sprintf(str, "  %s location:%d", object_name, (int)obj_loc);
      }else{
        sprintf(str, "  %s location:?", object_name);
      }
    
      screen_area_puts(ge->descript, str);
    }
  }

  /*for all the characters, we print their location and health*/

  sprintf(str, "Characters : ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    character_gdesc = character_get_gdesc(game_get_character(game, game_get_character_id_at(game, i)));
    character_loc = game_get_character_location(game, game_get_character_id_at(game, i));
    character_hp = character_get_health(game_get_character(game, game_get_character_id_at(game, i)));
    if(space_get_discovered(game_get_space(game, character_loc)) == TRUE){
      sprintf(str, "  %s location:%d (%d)", character_gdesc, (int)character_loc, character_hp);
    }else{
      sprintf(str, "  %s location:? (%d)", character_gdesc, character_hp);
    }
    screen_area_puts(ge->descript, str);
  }
  /*We print the player, its location , health and then the object in the inventory*/

  sprintf(str, "Player : %d (%d)", (int)game_get_current_player_location(game), player_get_health(game_get_current_player(game)));
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Objects in the inventory: ");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < player_get_num_objects_in_backpack(game_get_current_player(game)); i++)
  {
    object_name = object_get_name(game_get_object(game, player_get_backpack_object_id_at(game_get_current_player(game), i)));
    obj_loc = game_get_object_location(game, (player_get_backpack_object_id_at(game_get_current_player(game), i)));
    if (obj_loc == NO_ID)
    {
      sprintf(str, "  %s", object_name);
      screen_area_puts(ge->descript, str);
    }
  }
  /*Printing the message of the game, given after the command 'Chat'*/
  if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == CHAT)
  {
    sprintf(str, "  Message: %s", game_get_message(game));
    screen_area_puts(ge->descript, str);
  }
  /*Printing the description of the game, given after the command 'Inspect'*/
  if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT)
  {
    sprintf(str, "Object description:");
    screen_area_puts(ge->descript, str);

    sprintf(str, "%s", game_get_description(game));
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  sprintf(str, "    The anthill game: player %d", (game_get_turn(game) + 1));
  screen_area_puts(ge->banner, str);

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "move 'dir' or m 'dir', exit or e, take 'arg' or t 'arg', drop 'arg' or d 'arg', chat or c, attack or a, inspect 'arg' or i 'arg'");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */

  
  strcpy(str, graphic_interface_paint_feedback_for_pos(game, ge, THIRD_TO_LAST));
  screen_area_puts(ge->feedback, str);
  strcpy(str, graphic_interface_paint_feedback_for_pos(game, ge, SECOND_TO_LAST));
  screen_area_puts(ge->feedback, str);
  strcpy(str, graphic_interface_paint_feedback_for_pos(game, ge, LAST));
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
  screen_paint((game_get_turn(game)));
  printf("prompt:> ");
}

char *graphic_interface_paint_feedback_for_pos(Game *game, Graphic_engine*ge, CommandPosition pos){
  CommandCode cmd=NO_CMD;
  Status cmd_succ=ERROR;
  char *str;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if(!game || !ge) return NULL;

  str = (char *)calloc(MAX_STR, sizeof(char));

  cmd = command_get_code(game_interface_data_get_cmd_in_pos(game, pos));
  cmd_succ = command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, pos));
  if (cmd_succ == ERROR)
  {
    sprintf(str, " %s (%s) : ERROR", cmd_to_str[cmd - NO_CMD][CMDL], cmd_to_str[cmd - NO_CMD][CMDS]);
  }
  else
  {
    sprintf(str, " %s (%s) : OK", cmd_to_str[cmd - NO_CMD][CMDL], cmd_to_str[cmd - NO_CMD][CMDS]);
  }

  return str;
}