/**
 * @brief It implements the cinematics module
 *
 * @file cinematics.c
 * @author Matteo Artunedo
 * @version 0.1
 * @date 28-04-2025
 * @copyright GNU Public License
 */

#include "cinematics.h"

#define DIFFERENCE_BETWEEN_POS_AND_N_ELEMENTS 1     /*!<This macro is used to take into account the fact that, if an array contains 3 elements, the last position is 2, and therefore any position higher than 2, which is 3-1, is not valid*/

/**
 * @brief Structure that stores the text for each cinematic
 * 
 */
struct _Cinematics_text{
    char cinematic_text[NUMBER_OF_DIALOG_LINES][DIALOGUE_LINE_LENGTH];    /*!<Two-dinemnsional array that stores the dialog lines for each cinematic*/
    int n_lines;                                                          /*!<Number of dialogue lines in the cinematic*/
};


Cinematics_text *cinematics_text_create(){
    Cinematics_text *ct=NULL;

    if(!(ct = (Cinematics_text *)malloc(sizeof(Cinematics_text)))){
        return NULL;
    }
    ct->n_lines = 0;
    return ct;
}

void cinematics_text_destroy(Cinematics_text *ct){
    if(ct){
        free(ct);
    }
}

Status cinematics_text_add_line(Cinematics_text *ct, char *line){
    if(!ct || !line) return ERROR;
    strcpy(ct->cinematic_text[ct->n_lines], line);
    ct->n_lines++;
    return OK;
}

char *cinematics_get_line(Cinematics_text *ct, int pos){
    if(!ct || pos<0 || pos>(ct->n_lines - DIFFERENCE_BETWEEN_POS_AND_N_ELEMENTS)){
        return NULL;
    }
    return ct->cinematic_text[pos];
}

int cinematics_get_n_lines(Cinematics_text *ct){
    if(!ct) return -1;
    return ct->n_lines;
}