/**
 * @brief It defines the game's cinematics module
 *
 * @file cinematics.h
 * @author Matteo Artunedo
 * @version 0
 * @date 28-04-2025
 * @copyright GNU Public License
 */

#ifndef CINEMATICS_H
#define CINEMATICS_H
#include "types.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Data structure for managing the cinematics of the game
 * @author Matteo Artunedo
 */
typedef enum {
    INTRODUCTION,   /*!<Corresponds to the cinematic that will be played at the beggining of the game*/
    FIRST_STAIRS,   /*!<Corresponds to the cinematic that will be played when the characters go up the stairs from the firsst to the second floor*/
    BOBS_ROOM,      /*!<Corresponds to the cinematic that will be played when the Bob enters his room*/
    FINAL_BOSS,     /*!<Corresponds to the cinematic that when Alice and Bob meet the Final Boss*/
    TREASURE,       /*!<Corresponds to the cinematic that when Alice and Bob get the final treasure*/
    NO_CINEMATIC    /*!<Value that describes that no cinematics have to be displayed in the current moment*/
} Cinematics;

#define N_CINEMATICS NO_CINEMATIC   /*!<Value that describes the number of cinematics in the game*/
#define NUMBER_OF_DIALOG_LINES 20   /*!<Corresponds to the maximum number of interventions that can take place in a cinematic*/
#define DIALOGUE_LINE_LENGTH 180      /*!<Corresponds to the maximum length of each intervention*/
#define TIME_BETWEEN_CINEMATICS 1  /*!< Ammount of seconds the game gives the player to read each dialogue line in a cinematic*/
/**
 * @brief Definition of Cinematics_text type
 * @author Matteo Artunedo
 */
typedef struct _Cinematics_text Cinematics_text;

/**
 * @brief Creates a new Cinematics_text structure to store the dialogue of a certain cinematic
 * @author Matteo Artunedo
 * @return pointer to the created structure
 */
Cinematics_text *cinematics_text_create();

/**
 * @brief frees the memory of a Cinematics_text structure
 * @author Matteo Artunedo
 * @param ct pointer to the structure
 */
void cinematics_text_destroy(Cinematics_text *ct);

/**
 * @brief adds a dialog line to a certain cinematics_text structure
 * @author Matteo Artunedo
 * @param ct the structure corresponding to the cinematic
 * @param line the line to be added
 * @return Status OK or ERROR
 */
Status cinematics_text_add_line(Cinematics_text *ct, char *line);

/**
 * @brief returns the dialog line from a cinematic in a certain position
 * @author Matteo Artunedo
 * @param ct pointer to the structure that stores the cinematic's dialogue
 * @param pos position of the line in the cinematic
 * @return char* the line in the given position 
 */
char *cinematics_get_line(Cinematics_text *ct, int pos);

/**
 * @brief gets the number of lines in a cinematic's dialogue
 * @author Matteo Artunedo
 * @param ct pointer to the structure that stores the cinematic's text
 * @return int number of dialogue lines in the cinematic
 */
int cinematics_get_n_lines(Cinematics_text *ct);

/**
 * @brief Runs the cinematic currently present in the game through the given graphic engine
 * @author Matteo Artunedo
 * @param game pointer to the game
 * @param gengine pointer to the graphic engine that runs the game
 */
/*void cinematics_run(Game *game, Graphic_engine *gengine);*/

#endif