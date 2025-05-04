#include "libscreen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*This line makes the compiler ignore all the possible warnings that may arise with the flag -Wpedantic*/
#pragma GCC diagnostic ignored "-Wpedantic"

/* Global variables */
int ROWS=23;    /*!<Number of total rows in the game's screen*/
int COLUMNS=80; /*!<Number of total columns in the game's screen*/

#define TOTAL_DATA (ROWS * COLUMNS) + 1 /*!<Total ammount of characters in the screen with extra space for NULL termination*/
#define BG_CHAR '~'   /*!<Value which corresponds to painting the background*/
#define FG_CHAR ' '   /*!<Value which corresponds to painting the foreground*/
#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x)) /*!<Macro function that returns a determined position (x,y) with respects to a certain cursor (d, which is usually a pointer to the data that we want to access)*/
#define FINAL_CHARACTER 1 /*!<Size of the '\0' character that limits the size of strings*/
#define SIZE_IN_CHAR_TWO_HEXADECIMAL_VALUES 2 /*!<Size two hexadecimal values occupy in a string, with each hexadecimal value corresponding to a character*/
#define SIZE_OF_CONVERTED_UNCODE_SEQ 4  /*!<Size of a UNICODE sequence string that has been converted to its corresponding code, with the '\0' at the end*/
#define N_ESCAPE_SEQ 4    /*!<Number of escape sequences that are found in a UNICODE sequence, for instance, \xF0\x9F\x91\xA9 has 4 escape sequences*/
#define HEXADECIMAL_BASE 16   /*!<Numerical value that corresponds to the base of hexadecimal numbers*/
#define EMOTICON_SIZE 1 /*!<Represents the size of the special UNICODE character in the terminal*/
#define NEXT_POSITION 1 /*!<Represents the number of positions advanced when desiring to move to the next position in an array*/
#define STARTING_POSITION 0 /*!<Represents the initial position in an array*/
#define TOTAL_HORIZONTAL_SEPARATORS 4 /*!<Represents the number of separating characters that are found in a line*/
#define SEPARATOR_LINE_AFTER_MAP 3    /*!<Represents that the separator line that is found after the map area is the second one out of the total*/
#define START_ESCAPE_SEQUENCE "\\x"   /*!<Represents the start of escape sequences for unicode */
/**
 * @brief structure that saves all of the information related to the area
 * 
 */
struct _Area{
  int x;        /*!<X position of the area in the screen*/
  int y;        /*!<Y position of the area in the screen*/
  int width;    /*!<Width of the area in the screen*/
  int height;   /*!<Height of the area in the screen*/
  char *cursor; /*!<Pointer to where the area information starts*/
};

/*!<Global variable that stores all of the Area information*/
char *__data;



/****************************/
/*     Private functions    */
/****************************/
int  screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);
char *frame_color_to_string(Frame_color color);

/****************************/
/* Functions implementation */
/****************************/
void screen_init(int rows, int columns){
  screen_destroy(); /* Dispose if previously initialized */
  ROWS = rows;
  COLUMNS = columns;
  __data = (char *) malloc(sizeof(char) * TOTAL_DATA);

  if (__data){
    /*The memset function is used to fill memory (__data in this case) with a determined value (BG_CHAR)*/
    memset(__data, (int) BG_CHAR, TOTAL_DATA); /*Fill the background*/
    *(__data + TOTAL_DATA - 1) = '\0';         /*NULL-terminated string*/
  }
}

void screen_destroy(){
  if (__data)
    free(__data);
}

void screen_paint(Frame_color color, Bool lights_on){
  char *src = NULL;
  char *destination=NULL;
  unsigned char aux[SIZE_IN_CHAR_TWO_HEXADECIMAL_VALUES + FINAL_CHARACTER]; /*Auxiliary variable where we store the two hexadecimal values that define each escape sequence*/
  unsigned char gdesc[SIZE_OF_CONVERTED_UNCODE_SEQ + FINAL_CHARACTER]; /*Variable where we store the hexadecimal values which correspond to the UNICODE character, with the '\0' at the end*/
  unsigned char sequence[GDESCTAM]; /*VAriable where we store the UNICODE sequence*/
  int i=0, j=0;
  int size_of_escape_seq_start;
  int n_unicode_characters=0;
  int n_separator_lines=0;
  char light_theme_code[] = "[0;30;47m", dark_theme_code[] = "[0;37;40m", *selected_theme=NULL;


  destination = malloc((COLUMNS + FINAL_CHARACTER) * sizeof(char));
  if (!destination) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
}

  size_of_escape_seq_start = strlen(START_ESCAPE_SEQUENCE);
  if(lights_on == TRUE){
    selected_theme = light_theme_code;
  }else{
    selected_theme = dark_theme_code;
  }

  memset(destination, 0, COLUMNS + 1);

  if (__data){
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/

    puts("\033[2J"); /*Clear the terminal*/
    /*We go through the __data variable with pointer arythmetic, adding the number of columns in each iteration*/
    for (src=__data; src < (__data + TOTAL_DATA - FINAL_CHARACTER); src+=COLUMNS){
      memcpy(destination, src, COLUMNS);
      
      /*We set the number of UNICODE characters printed in the line to 0*/
      n_unicode_characters = 0;
      n_separator_lines=0;
      /*We print each character in the column individually*/
      for (i=0; i<COLUMNS; i++){
        if (destination[i] == BG_CHAR){
          if(n_separator_lines == SEPARATOR_LINE_AFTER_MAP){
            /*We compensate the fact that the UNICODE character occupies 16 bytes but only one space in the printed output by printing spaces*/
            for(j=0;j<n_unicode_characters * (GDESCTAM - FINAL_CHARACTER - EMOTICON_SIZE);j++){
              printf("\033%s \033[0m", selected_theme);
            }
          }
          printf("%s%c\033[0m", frame_color_to_string(color), destination[i]); /* fg:blue(34);bg:blue(44) */
          n_separator_lines++;
        }else{
          /*In case we detect an escape sequence indicating the presence of a UNICODE character, we must print this in a particular manner to ensure the terminal prints the image associated to the UNICODE sequence correctly*/
          if (destination[i] == '\\' && destination[i + NEXT_POSITION] == 'x'){
            /*We copy the sequence to an auxiliary variable called sequence*/
            strncpy((char *)sequence, destination + i, GDESCTAM - FINAL_CHARACTER);
            sequence[GDESCTAM] = '\0';
            /*For each of the escape sequences, we store the two hexadecimal values (for instance, F and 0) in aux and use strtol to convert that into one of the hexadecimal values stored in gdesc.*/
            for(j=0;j<N_ESCAPE_SEQ;j++){
              aux[STARTING_POSITION] = (unsigned char)sequence[size_of_escape_seq_start + N_ESCAPE_SEQ*j];
              aux[STARTING_POSITION + NEXT_POSITION] = (unsigned char)sequence[size_of_escape_seq_start + NEXT_POSITION + N_ESCAPE_SEQ*j];
              aux[STARTING_POSITION + NEXT_POSITION + NEXT_POSITION] = '\0';
              gdesc[j] = (unsigned char)strtol((char *)aux, NULL, HEXADECIMAL_BASE);
            }
            gdesc[SIZE_OF_CONVERTED_UNCODE_SEQ] = '\0';
            printf("\033%s%s\033[0m", selected_theme, gdesc);
            i += GDESCTAM - EMOTICON_SIZE;
            n_unicode_characters++;
          }else{
            printf("\033%s%c\033[0m", selected_theme, destination[i]); /* fg white(37);bg:black(40)*/ 
          }
        }
      }
      printf("\n");
    }
  }
  free(destination);
  return;
}

char *frame_color_to_string(Frame_color color){
  switch (color)
  {
    case BLACK:
    return "\033[0;30;40m";
    break;
    case RED:
    return "\033[0;31;41m";
    break;
    case GREEN:
    return "\033[0;32;42m";
    break;
    case YELLOW:
    return "\033[0;34;43m";
    break;
    case BLUE:
    return "\033[0;34;44m";
    break;
    case PURPLE:
    return "\033[0;34;45m";
    break;
    case CYAN:
    return "\033[0;34;46m";
    break;
    case WHITE:
    return "\033[0;34;47m";
    break;

  default:
    return NULL;
  }
}




Area* screen_area_init(int x, int y, int width, int height){
  int i = 0;
  Area* area = NULL;
  /*We assign all of the values given as arguments simultaneously, placing the cursor in the x,y position with respects to the __data pointer*/
  if ( (area  = (Area*) malloc (sizeof(struct _Area))) ){
    *area = (struct _Area) {x, y, width, height, ACCESS(__data, x, y)};

    /*We fill each row with the FG_CHAR character*/
    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }

  return area;
}

void screen_area_destroy(Area* area){
  if(area)
    free(area);
}

void screen_area_clear(Area* area){
  int i = 0;

  if (area){
    screen_area_reset_cursor(area);

    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }
}
/*Places the cursor of an area in the starting position of said area*/
void screen_area_reset_cursor(Area* area){
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

void screen_area_puts(Area* area, char *str){
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  screen_utils_replaces_special_chars(str);

  for (ptr = str; ptr < (str + strlen(str)); ptr+=area->width){
    memset(area->cursor, FG_CHAR, area->width);
    len = (strlen(ptr) < area->width)? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS;
  }
}
/*Checks if the cursor has exceded the size of the area*/
int screen_area_cursor_is_out_of_bounds(Area* area){
  return area->cursor > ACCESS(__data,
			       area->x + area->width,
			       area->y + area->height - 1);
}
/*Copies each line to the one before it*/
void screen_area_scroll_up(Area* area){
  for(area->cursor = ACCESS(__data, area->x, area->y);
      area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
      area->cursor += COLUMNS){
    memcpy(area->cursor, area->cursor+COLUMNS, area->width);
  }
}

void screen_utils_replaces_special_chars(char* str){
  char *pch = NULL;

  /* Replaces acutes and tilde with '??' */
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}

