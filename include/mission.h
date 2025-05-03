/**
 * @file mission.h
 * @author Alvaro Inigo
 * @brief This file sets the definition of all the functions related to the TAD mission
 * @version 0.1
 * @date 2025-04-29
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef MISSION_H
#define MISSION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


#define MAX_MISSION_MESSAGE 100  /*!<The maximum ammount of chars a message can have*/
#define MAX_OBJECTIVES 15        /*!<the maximum objectives a mission can have*/   
#define MAX_DIALOGUES 15         /*!<the maximum dialogues a mission can have*/ 
  

typedef struct _Mission Mission;

/*!<The mission code, each mission in the game has its own code*/

typedef enum{  
    NO_MISSION = -1,
    TEAM_MISSION,
    LANTERN_MISSION,
    GENERATOR_MISSION,
    FATHER_MISSION,
    SECOND_FLOOR_MISSION,
    MEDKIT_MISSION,
    BEDROOM_MISSION,
    REX_MISSION,
    THIRD_FLOOR_MISSION,
    BOSS_MISSION

}Mission_Code;

 
/**
 * @brief creates a new Mission
 * @author Alvaro Inigo
 * @return Mission* a pointer to the new created mission
 */
Mission *mission_create();

/**
 * @brief Destroys a mission and frees all the memory allocated
 * @author Alvaro Inigo
 * @param mission a pointer to the mission to destroy
 * @return Status OK or ERROR
 */
Status mission_destroy(Mission *mission);

/**
 * @brief gets the code of a Mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return Mission_Code the code of the mission
 */
Mission_Code mission_get_code(Mission *mission);

/**
 * @brief sets the code of a mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission to set the code
 * @param code the new code
 * @return Status OK or ERROR
 */
Status mission_set_code(Mission *mission, Mission_Code code);

/**
 * @brief gets the number of dialogues in a mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission to get the dialogues
 * @return int the number of dialogues
 */
int mission_get_n_dialogues(Mission *mission);

/**
 * @brief gets the number of objectives of a mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return int the number of objectives of the mission
 */
int mission_get_n_objectives(Mission *mission);


/**
 * @brief adds a new dialogue line to the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @param dialogue the new dialogue to add
 * @return Status OK or ERROR
 */
Status mission_add_dialogue(Mission *mission, char *dialogue);

/**
 * @brief adds a new objective to the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @param objective the new objective
 * @return Status OK or ERROR
 */
Status mission_add_objective(Mission *mission, char *objective);

/**
 * @brief gets the next dialogue of the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return char* the next dialogue line
 */
char *mission_get_next_dialogue(Mission *mission); 

/**
 * @brief gets the next objective of the mission to show the player
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return char* the next objective
 */
char *mission_get_next_objective(Mission *mission);

/**
 * @brief gets the next state of the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return int the current step
 */
int mission_get_current_step(Mission *mission);

/**
 * @brief sets the next step of the mission
 * @author Alvaro Inigo
 * @param mission the pointer to the mission
 * @param step the step to set
 * @return Status OK or ERROR
 */
Status mission_set_current_step(Mission *mission, int step);

/**
 * @brief sets the next objective of a mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @param objective the nrxt objective to set
 * @return Status Ok or ERROR
 */

Status mission_set_next_objective(Mission *mission, int objective);

/**
 * @brief sets the next dialogue of a mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @param dialogue the next dialogue to set
 * @return Status OK or ERROR
 */
Status mission_set_next_dialogue(Mission *mission, int dialogue);

/**
 * @brief gets the objective in position pos of the array of objectives in the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @param pos the position of the objective
 * @return char* the objective in position selected
 */
char *mission_get_objective_in_pos(Mission *mission, int pos);

/**
 * @brief gets the dialogue in the position wanted of the array of dialogues of the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @param pos the position of the dialogue wanted
 * @return char* the dialogue
 */
char *mission_get_dialogue_in_pos(Mission *mission, int pos);

/**
 * @brief gets the next dialogue index playing in the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return int the next dialogue
 */
int mission_get_next_dialogue_index(Mission *mission);

/**
 * @brief gets the next objective index playing in the mission
 * @author Alvaro Inigo
 * @param mission a pointer to the mission
 * @return int the index of the next objective
 */
int mission_get_next_objective_index(Mission *mission);

#endif