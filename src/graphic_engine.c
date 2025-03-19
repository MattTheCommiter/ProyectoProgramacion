/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Matteo Artuned
 * @version 0.2
 * @date 12-03-2025
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "character.h"

/*Constant values used for the creation of the game's graphic interface*/
#define WIDTH_MAP 60      /*!<Width of the map in the graphic interface*/
#define WIDTH_DES 29      /*!<Width of the description box in the graphic interface*/
#define WIDTH_BAN 23      /*!<Width of the banner in the graphic interface*/
#define HEIGHT_MAP 29     /*!<Height of the map in the graphic interface*/
#define HEIGHT_BAN 1      /*!<Height of the banner in the graphic interface*/
#define HEIGHT_HLP 2      /*!<Height of the help box in the graphic interface*/
#define HEIGHT_FDB 3      /*!<Height of the feedback box in the graphic interface*/
#define NUMBER_OF_BARS 2  /*!<Number and size of the '|' at the sides of the squares*/
#define SIZE_OF_SPACE 2   /*!<Size of the chars ' ,' between each object name*/
#define FINAL_CHARACTER 1 /*!<Size corresponding to the \0 character of the string*/
#define BOTTOM_HEIGHT 1   /*!<Height of the lowest line of spaces in the map*/
#define MIDDLE_HEIGHT 2   /*!<Height of the middle line of spaces in the map*/
#define TOP_HEIGHT 3      /*!<Height of the highest line of spaces in the map*/
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
Status set_arrows(Game *game, Id spaceId, char *north1, char *south1, char *north2, char *south2, char *north3, char *south3);

/**
 * @brief Create a line of spaces (3 space squares placed horizontally one after the other)
 * @author Matteo Artunedo
 * @param game pointer to the game structure
 * @param id_center the id of the space that will be in the center of the line
 * @param id_player the id of where the player is located
 * @param height 1 if the line being created is the last one that is printed in the map box, 2 if it is the middle line and 3 if it is the top line
 * @return char** matrix with the complete line
 */
char **create_line_of_spaces(Game *game, Id id_center, Id id_player, int height);

/**
 * @brief Create a square space description for the space with the given id
 * @author Matteo Artunedo
 * @param game pointer to the game structure
 * @param square_id id of the space which corresponds to the box being created
 * @return char** matrix with the square of the space that will be printed on the screen
 */
char **create_space_square(Game *game, Id square_id);

/**
 * @brief returns the id of the space that is at the side of id_center
 * @author Matteo Artunedo
 * @param game pointer to game
 * @param id_player id of the space where the player is located
 * @param space_get_adjacent pointer to the function that will determine which position we want to access (it will be either space_get_west or space_get_east)
 * @param height 1 if it is the last line that is printed in the map box, 2 if it is the middle line and 3 if it is the top line
 * @return Id of the adjacent space
 */
Id horizontally_adjacent_square(Game *game, Id id_player, Id(space_get_adjacent)(Space *space), int height);

/**
 * @brief returns the id of the space that is at the vertically adjacent to id_center
 * @author Matteo Artunedo
 * @param game pointer to game
 * @param id_player id of the space where the player is located
 * @param space_get_v_adjacent pointer to the function that will determine which position we want to access (it will be either space_get_north or space_get_south)
 * @return Id of the vertically adjacent space
 */
Id vertically_adjacent_square(Game *game, Id id_center, Id((*space_get_v_adjacent)(Space *space)));

/*PRIVATE FUNCTIONS*/
Status set_arrows(Game *game, Id spaceId, char *north1, char *south1, char *north2, char *south2, char *north3, char *south3)
{
  Id id_east = NO_ID, id_west = NO_ID, id_north = NO_ID, id_south = NO_ID;
  id_north = space_get_north(game_get_space(game, spaceId));
  id_south = space_get_south(game_get_space(game, spaceId));
  id_east = space_get_east(game_get_space(game, spaceId));
  id_west = space_get_west(game_get_space(game, spaceId));

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
    id_west = horizontally_adjacent_square(game, spaceId, space_get_west, MIDDLE_HEIGHT);
  }
  if (id_east == NO_ID)
  {
    id_east = horizontally_adjacent_square(game, spaceId, space_get_east, MIDDLE_HEIGHT);
  }

  /*Estudiamos si el espacio al este del espacio del jugador tiene norte y/o sur, poniendo las flechas acorde a esa información*/
  if (space_get_id(game_get_space(game, space_get_north(game_get_space(game, id_east)))) != NO_ID)
  {
    *north3 = '^';
  }
  if (space_get_id(game_get_space(game, space_get_south(game_get_space(game, id_east)))) != NO_ID)
  {
    *south3 = 'v';
  }
  /*Estudiamos si el espacio al oeste del espacio del jugador tiene norte y/o sur, poniendo las flechas acorde a esa información*/
  if (space_get_id(game_get_space(game, space_get_north(game_get_space(game, id_west)))) != NO_ID)
  {
    *north1 = '^';
  }
  if (space_get_id(game_get_space(game, space_get_south(game_get_space(game, id_west)))) != NO_ID)
  {
    *south1 = 'v';
  }
  return OK;
}

char **create_space_square(Game *game, Id square_id)
{
  char **space_square = NULL, str[255], ant_str[] = "m0^", blank_player_str[] = "   ", **gdesc, *player, object[N_TOTAL_ROWS_IN_SQUARE - FINAL_CHARACTER], character[GDESCTAM], blank_character_str[] = "      "; /*Quitar este número mágico*/
  Space *space;
  Object *object_in_pos = NULL;
  Bool full = FALSE;
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
    if (game_get_player_location(game) == square_id)
    {
      player = ant_str;
    }
    else
    {
      player = blank_player_str;
    }
    /*Damos un valor al personaje del espacio si lo hay*/
    if (space_get_character(space) == NO_ID)
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
        full = TRUE;
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
    sprintf(str, "+---------------+");
    strcpy(space_square[8], str);
  }

  return space_square;
}

Id vertically_adjacent_square(Game *game, Id id_center, Id((*space_get_v_adjacent)(Space *space)))
{
  Id found_id = NO_ID;
  found_id = space_get_id(game_get_space(game, space_get_west(game_get_space(game, space_get_v_adjacent(game_get_space(game, space_get_east(game_get_space(game, id_center))))))));
  if (found_id == NO_ID)
  {
    found_id = space_get_id(game_get_space(game, space_get_east(game_get_space(game, space_get_v_adjacent(game_get_space(game, space_get_west(game_get_space(game, id_center))))))));
  }
  return found_id;
}

Id horizontally_adjacent_square(Game *game, Id id_player, Id (*space_get_adjacent)(Space *space), int height)
{
  Id found_id = NO_ID;
  /*Buscamos si el espacio situado a la derecha o la izquierda (según la función space_get que se pase como argumento) existe mediante caminos más complejos. De este modo, podemos imprimir el espacio aunque no haya acceso directo desde el espacio del centro de la línea*/
  if (height == TOP_HEIGHT)
  {
    /*Si la línea que se está imprimiendo es la superior, probamos a llegar al espacio de la derecha/izquierda desde el espacio del jugador, moviéndonos primero a la derecha/izquierda y después subiendo*/
    found_id = space_get_north(game_get_space(game, space_get_adjacent(game_get_space(game, id_player))));
  }
  else if (height == BOTTOM_HEIGHT)
  {
    /*Si la línea que se está imprimiendo es la inferior, probamos a llegar al espacio de la derecha/izquierda desde el espacio del jugador, moviéndonos primero a la derecha/izquierda y después bajando*/
    found_id = space_get_south(game_get_space(game, space_get_adjacent(game_get_space(game, id_player))));
  }
  else if (height == MIDDLE_HEIGHT)
  {
    /*En caso de que el la línea sea la del centro, probamos ambos caminos, tanto el que sube al final como el que baja*/
    found_id = space_get_south(game_get_space(game, space_get_adjacent(game_get_space(game, space_get_north((game_get_space(game, id_player)))))));
    if (found_id == NO_ID)
    {
      found_id = space_get_north(game_get_space(game, space_get_adjacent(game_get_space(game, space_get_south((game_get_space(game, id_player)))))));
    }
  }
  return found_id;
}

char **create_line_of_spaces(Game *game, Id id_center, Id id_player, int height)
{
  char **gdesc_line = NULL, **left_square = NULL, **center_square = NULL, **right_square = NULL, str[255], left_square_arrow = ' ', right_square_arrow = ' ';
  int i;
  Id id_left, id_right;

  /*OBTENCION DE LOS ID_LEFT E ID_RIGHT*/

  /*Obtenemos los id's del espacio a la izquierda y la derecha del que se nos ha pasado*/
  id_left = space_get_west(game_get_space(game, id_center));
  id_right = space_get_east(game_get_space(game, id_center));

  /*Si el espacio del centro tiene conexión directa con el de la derecha, imprimiremos una flecha*/
  if (id_right != NO_ID)
  {
    right_square_arrow = '>';
  }
  else
  {
    /*Buscamos si existe el espacio desde otros caminos*/
    id_right = horizontally_adjacent_square(game, id_player, space_get_east, height);
  }

  /*Si el espacio del centro tiene conexión directa con el de la izquierda, imprimiremos una flecha*/
  if (id_left != NO_ID)
  {
    left_square_arrow = '<';
  }
  else
  {
    /*Buscamos si existe el espacio desde otros caminos*/
    id_left = horizontally_adjacent_square(game, id_player, space_get_west, height);
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
  char str[255], *object_name = NULL, *character_gdesc = NULL, north_arrow1 = ' ', south_arrow1 = ' ', north_arrow2 = ' ', south_arrow2 = ' ', north_arrow3 = ' ', south_arrow3 = ' ';
  int i, character_hp;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Status last_cmd_succ = OK;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    id_north = space_get_north(game_get_space(game, id_act));
    id_south = space_get_south(game_get_space(game, id_act));
    set_arrows(game, id_act, &north_arrow1, &south_arrow1, &north_arrow2, &south_arrow2, &north_arrow3, &south_arrow3);
    if (id_north == NO_ID)
    {
      /*Probamos a llegar al norte desde caminos alternativos*/
      id_north = vertically_adjacent_square(game, id_act, space_get_north);
    }
    if (id_south == NO_ID)
    {
      /*Probamos a llega al sur desde caminos alternativos*/
      id_south = vertically_adjacent_square(game, id_act, space_get_south);
    }

    /*araña muerta se imprime del reves, no es necesario pero mejora la experiencia de juego*/
    if (character_get_health(game_get_character(game, SPIDER)) == 0)
    {
      character_set_gdesc(game_get_character(game, SPIDER), "\\/xx\\/");
    }
    /*fin del cambio grafico para la araña muerta*/

    /*Imprimimos la primera línea de espacios */
    created_line = create_line_of_spaces(game, id_north, id_act, TOP_HEIGHT);
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
    created_line = create_line_of_spaces(game, id_act, id_act, MIDDLE_HEIGHT);
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
    created_line = create_line_of_spaces(game, id_south, id_act, BOTTOM_HEIGHT);
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
      sprintf(str, "  %s location:%d", object_name, (int)obj_loc);
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
    sprintf(str, "  %s location:%d (%d)", character_gdesc, (int)character_loc, character_hp);
    screen_area_puts(ge->descript, str);
  }
  /*We print the player, its location , health and then the object in the inventory*/

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
  /*Printing the message of the game, given after the command 'Chat'*/
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
  if (last_cmd_succ == ERROR)
  {
    sprintf(str, " %s (%s) : ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  else
  {
    sprintf(str, " %s (%s) : OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }

  screen_area_puts(ge->feedback, str);

  /*Print a message if the player dies and the game ends*/
  if (player_get_health(game_get_player(game)) == 0)
  {
    sprintf(str, "Has muerto !!");
    game_set_finished(game, TRUE);
    screen_area_puts(ge->feedback, str);
  }

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
