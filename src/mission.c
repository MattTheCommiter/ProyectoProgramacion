
#include "mission.h"


struct _Mission{
    Mission_Code code;                                      /*!<The code of the mission, this codes are defined on the enumeration in mission.h*/
    char dialogues[MAX_DIALOGUES][MAX_MISSION_MESSAGE];     /*!<The dialogues in a mission, this will be messages 'said' by the characters in the missions*/
    int n_dialogues;                                        /*!<the number of dialogues a mission has*/
    int next_dialogue_index;                             /*!<the position in the array of the current dialogue*/
    char objectives[MAX_OBJECTIVES][MAX_MISSION_MESSAGE];   /*!<the objectives of a mission, text to be shown in order for the player to see what to do*/
    int n_objectives;                                       /*!<the number of objectives a mission has*/
    int next_objective_index;                            /*!<the position in the array of the current objective text*/
    int step;                                               /*!<the current step in the mission, each mission has own steps to follow*/
};



Mission *mission_create(){
    Mission *new_mission = NULL;
    new_mission = (Mission*)malloc(sizeof(Mission));
    if(!new_mission) return NULL;
    new_mission->code = NO_MISSION;
    new_mission->next_dialogue_index = 0;
    new_mission->next_objective_index = 0;
    new_mission->n_dialogues = 0;
    new_mission->n_objectives = 0;
    new_mission->step = 0;

    return new_mission;
}


Status mission_destroy(Mission *mission){
    if(!mission) return ERROR;
    free(mission);
    return OK;
}


Mission_Code mission_get_code(Mission *mission){
    if(!mission) return NO_MISSION;
    return mission->code;
}


Status mission_set_code(Mission *mission, Mission_Code code){
    if(!mission) return ERROR;
    mission->code = code;
    return OK;
}


int mission_get_n_dialogues(Mission *mission){
    if(!mission) return -1;
    return mission->n_dialogues;
}


int mission_get_n_objectives(Mission *mission){
    if(!mission) return -1;
    return mission->n_objectives;
}



Status mission_add_dialogue(Mission *mission, char *dialogue){
    if(!mission || !dialogue || mission->n_dialogues >= MAX_DIALOGUES) return ERROR;

    strcpy(mission->dialogues[mission->n_dialogues], dialogue);
    mission->n_dialogues++;
    return OK;
}


Status mission_add_objective(Mission *mission, char *objective){
    if(!mission || !objective || mission->n_objectives  >= MAX_OBJECTIVES) return ERROR;

    strcpy(mission->objectives[mission->n_objectives], objective);
    mission->n_objectives++;
    return OK;
}


char *mission_get_next_dialogue(Mission *mission){
    if(!mission || mission->next_dialogue_index >= mission->n_dialogues) return NULL;
    mission->next_dialogue_index++;
    return mission->dialogues[mission->next_dialogue_index - 1];
}


char *mission_get_next_objective(Mission *mission){
    if(!mission || mission->next_objective_index >= mission->n_objectives) return NULL;
    mission->next_objective_index ++;
    return mission->objectives[mission->next_objective_index - 1];
}

int mission_get_current_step(Mission *mission){
    if(!mission) return -1;
    return mission->step;
}

Status mission_set_current_step(Mission *mission, int step){
    if(!mission || step < 0) return ERROR;
    mission->step = step;
    return OK;
}

Status mission_set_next_objective(Mission *mission, int objective){
    if(!mission || objective < 0) return ERROR;
    mission->next_objective_index = objective;
    return OK;
}

Status mission_set_next_dialogue(Mission *mission, int dialogue){
    if(!mission || dialogue < 0) return ERROR;
    mission->next_dialogue_index = dialogue;
    return OK;
}

int mission_get_next_dialogue_index(Mission *mission){
    if(!mission) return ERROR;
    return mission->next_dialogue_index;
}

int mission_get_next_objective_index(Mission *mission){
    if(!mission) return ERROR;
    return mission->next_dialogue_index;
}

char *mission_get_objective_in_pos(Mission *mission, int pos){
    if(!mission || pos < 0 || pos >= mission->n_objectives) return NULL;
    return mission->objectives[pos];
}
char *mission_get_dialogue_in_pos(Mission *mission, int pos){
    if(!mission || pos < 0 || pos >= mission->n_dialogues) return NULL;
    return mission->dialogues[pos];
}

char *mission_get_name(Mission *mission) {
    if (!mission) return NULL;

    switch (mission->code) {
        case NO_MISSION:
            return "NO MISSION";
        case TEAM_MISSION:
            return "TEAM MISSION";
        case LANTERN_MISSION:
            return "LANTERN MISSION";
        case GENERATOR_MISSION:
            return "GENERATOR MISSION";
        case FATHER_MISSION:
            return "FATHER MISSION";
        case SECOND_FLOOR_MISSION:
            return "SECOND FLOOR MISSION";
        case MEDKIT_MISSION:
            return "MEDKIT MISSION";
        case BEDROOM_MISSION:
            return "BEDROOM MISSION";
        case REX_MISSION:
            return "REX MISSION";
        case THIRD_FLOOR_MISSION:
            return "THIRD FLOOR MISSION";
        case BOSS_MISSION:
            return "BOSS MISSION";
        default:
            return "UNKNOWN MISSION";
    }
}
