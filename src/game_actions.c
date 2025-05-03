/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Matteo Artuñedo,Alvaro Inigo, AGL, Guilherme Povedano 
 * @version 0.1
 * @date 22-03-2025
 * @copyright GNU Public License
 */
#include "game_actions.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/**
   Private functions
*/

/**
 * @brief doesn't carry out any actions
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game
 */
void game_actions_unknown(Game *game);

/**
 * @brief doesn't carry out any actions
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game
 */
void game_actions_exit(Game *game);

/**
 * @brief moves the character to the space in the  direction specified by the user
 *
 * @date 30-03-2025
 * @author Alvaro Inigo
 *
 * @param game a pointer to the structure with the game's main information
 */
void game_actions_move(Game *game, char *arg);


/**
 * @brief takes the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo, AGL (modifications to update to player's backpack)
 *
 * @param game a pointer to the structure with the game's main information
 * @param arg the name of the object taken.
 */
void game_actions_take(Game *game, char *arg);

/**
 * @brief drops the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo, AGL (modifications to update to player's backpack)
 *
 * @param game a pointer to the structure with the game's main information
 */
void game_actions_drop(Game *game, char *arg);

/**
 * @brief chats with a character in the same space, assigning the character's message to the message parameter in game
 *
 * @date 04-03-2025
 * @author Matteo Artunedo
 *
 * @param game a pointer to the structure with the game's main information
 * @param arg name of the character the player is going to chat with
 */
void game_actions_chat(Game *game, char *arg);
/**
 * @brief Attack, both the player or a non friendly character at the same space loses health, if the character dies, it cannot be attacked anymore.
 * @date 25-02-2025
 * @author Matteo Artunedo
 * @param game a pointer to the game
 * @param arg name of the character the player is going to attack
 */
void game_actions_attack(Game *game, char *arg);

/**
 * @brief The command that allows the player to inspect an object
 * @date 25-02-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param arg name of the object they are going to inspect
 */
void game_actions_inspect(Game *game, char *arg);

/**
 * @brief Command that allows the player to recruit a character to have them on their team
 * @author Matteo Artunedo
 * @date 12-04-2025
 * @param game pointer to the game
 * @param arg name of the character they are going to recruit
 */
void game_actions_recruit(Game *game, char *arg);

/**
 * @brief Command that allows the player to abandon a character to have them on their team
 * @author Matteo Artunedo
 * @date 12-04-2025
 * @param game pointer to the game
 * @param arg name of the character they are going to abandon
 */
void game_actions_abandon(Game *game, char *arg);

/**
 * @brief Command that allows the player to open links with objects in their backpack
 * @author Guilherme Povedano 
 * @date 25-04-25
 * @param game pointer to the game
 * @param arg name of the character they are going to recruit
*/
void game_actions_open(Game *game, char *arg);

/**
 * @brief saves the current game in the file with the name given in the arg
 * @author Alvaro Inigo
 * @date 18/04/25
 * @param game a pointer to the game
 * @param arg the name of the saving file
 */
void game_actions_save(Game *game, char *arg);


/**
 * @brief loads the game of the file with the name given in the arg
 * @author Alvaro Inigo
 * @date 18/04/25
 * @param game a double pointer to the game
 * @param arg the name of the loading file
 */
void game_actions_load(Game **game, char *arg);

/**
 * @brief allows a player to team with another player
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param arg the name of the player to join the team
 */
void game_actions_team(Game *game, char *arg, Graphic_engine *gengine);

/**
 * @brief Executes the USE command in the game.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 * @param object_name Name of the object to be used.
 * @param character_name Name of the character to which apply the object's effect (optional).
 */
void game_actions_use(Game *game, char *object_name, char *character_name);



/**
 * @brief Command that allows the player to change the turn to the next player
 * @author Matteo Artunedo
 * @date 23-04-2025
 * @param game pointer to the game
 */
void game_actions_turn(Game *game);

/*Game actions implementation*/

Status game_actions_update(Game **game, Command *command, Graphic_engine *gengine)
{
  CommandCode cmd;

  game_interface_data_set_last_command(*game, command);

  cmd = command_get_code(command);

  switch (cmd)
  {
  case UNKNOWN:
    game_actions_unknown(*game);
    break;

  case EXIT:
    game_actions_exit(*game);
    break;

  case MOVE:
    game_actions_move(*game, command_get_argument(command));
    break;

  case TAKE:
    game_actions_take(*game, command_get_argument(command));
    break;
  case CHAT:
    game_actions_chat(*game, command_get_argument(command));
    break;
  case DROP:
    game_actions_drop(*game, command_get_argument(command));
    break;
  case ATTACK:
    game_actions_attack(*game, command_get_argument(command));
    break;
  case INSPECT:
    game_actions_inspect(*game, command_get_argument(command));
    break;
  case RECRUIT:
    game_actions_recruit(*game, command_get_argument(command));
    break;
  case ABANDON:
    game_actions_abandon(*game, command_get_argument(command));
    break;
  case SAVE:
    game_actions_save(*game, command_get_argument(command));
    break;
  case LOAD:
    game_actions_load(game, command_get_argument(command));
    break;
  case TEAM:
    game_actions_team(*game, command_get_argument(command), gengine);
  case USE:
    game_actions_use(*game, command_get_argument(command), command_get_argument2(command));
    break;
  case OPEN:
    game_actions_open(*game, command_get_argument(command));
    break;
  case TURN:
    game_actions_turn(*game);
    break;
  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_move(Game *game, char *arg)
{
  Direction direction = UNKNOWN_DIR;
  Id current_id = NO_ID;
  Id next_space_id = NO_ID;
  if (!game)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  if(!strcasecmp(arg, "NORTH") || !strcasecmp(arg, "N")){
    direction = N;
  }
  if(!strcasecmp(arg, "SOUTH") || !strcasecmp(arg, "S")){
    direction = S;
  }
  if(!strcasecmp(arg, "EAST") || !strcasecmp(arg, "E")){
    direction = E;
  }
  if(!strcasecmp(arg, "WEST") || !strcasecmp(arg, "W")){
    direction = W;
  }
    if(!strcasecmp(arg, "UP") || !strcasecmp(arg, "U")){
    direction = U;
  }
  if(!strcasecmp(arg, "DOWN") || !strcasecmp(arg, "D")){
    direction = D;
  }
  if(direction == UNKNOWN_DIR){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  
  current_id = game_get_current_player_location(game);
  if (current_id == NO_ID)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  if(game_connection_is_open(game, current_id, direction) ==  FALSE){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  next_space_id = game_get_connection(game, current_id, direction);
  if(next_space_id != NO_ID)
  {
    game_move_followers(game, next_space_id);
    game_set_current_player_location(game, next_space_id);
    space_set_discovered(game_get_space(game, next_space_id), TRUE);
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
    return;
  }
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
  return;
}


void game_actions_take(Game *game, char *arg)
{
  Id objectId = NO_ID;
  int i;
  Bool found = FALSE;
  Object *object = NULL;

  /*If the arguments (pointers) are NULL or the bacpack of the current player is full, nothing happens*/
  if (!game || arg == NO_ARG || player_backpack_is_full(game_get_current_player(game)))
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  /*Find the object with the specified name "arg" in the game */
  for (i = 0; i < game_get_n_objects(game) && found == FALSE; i++)
  {
    if (strcasecmp(arg, object_get_name(game_get_object_in_pos(game, i))) == 0)
    {
      found = TRUE;
      i--;
    }
  }
  if (found == FALSE)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*Now, that we have found the object with the name, we get its Id
  and its pointer*/
  objectId = game_get_object_id_at(game, i);
  object = game_get_object_in_pos(game, i);

  /* Check if the object is movable */
  if (object_get_movable(object) == FALSE)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /* Check if the object has a dependency and if the dependent object is in the player's backpack */
  if (object_get_dependency(object) != NO_ID && !player_backpack_contains(game_get_current_player(game), object_get_dependency(object)))
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  if (game_get_object_location(game, objectId) == NO_ID)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*We check that the player and the object are in the same space*/
  if (game_get_current_player_location(game) == game_get_object_location(game, objectId))
  {
    /*We add the object to the player's backpack*/
    if (player_add_object_to_backpack(game_get_current_player(game), objectId) == OK)
    {
      /* We change the objectId of the space where the object was located to NO_ID */
      space_delete_object(game_get_space(game, game_get_current_player_location(game)), objectId);
      command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
      return;
    }
  }
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
  return;
}

void game_actions_drop(Game *game, char *arg)
{
  Id objectId = NO_ID;
  int i;
  Bool found = FALSE;
  Player *player = NULL;
  Id dependentObjectId = NO_ID;
  Object *dependentObject = NULL;

  /* If the arguments (pointers) are NULL, nothing happens */
  if (!game || arg == NO_ARG)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  /* Check if the player's backpack is empty */
  if (player_backpack_is_empty(game_get_current_player(game)))
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /* Find the object with the given name in the player's backpack  */
  player = game_get_current_player(game);
  for (i = 0; i < player_get_num_objects_in_backpack(player) && found == FALSE; i++)
  {
    objectId = player_get_backpack_object_id_at(player, i);
    if (strcasecmp(arg, object_get_name(game_get_object(game, objectId))) == 0)
    {
      found = TRUE;
      i--;
    }
  }
  if (found == FALSE)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /* Check if the object has dependencies.
  Iterate through the player's backpack to check if any object depends on the object being dropped.
  If a dependent object is found, the function returns an error. */
  for (i = 0; i < player_get_num_objects_in_backpack(player); i++)
  {
    dependentObjectId = player_get_backpack_object_id_at(player, i);
    dependentObject = game_get_object(game, dependentObjectId);
    if (object_get_dependency(dependentObject) == objectId)
    {
      command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
      return;
    }
  }

  /* Add the object to the space where the player is located */
  if (space_add_objectId(game_get_space(game, game_get_current_player_location(game)), objectId) == OK)
  {
    /* Remove the object from the player's backpack */
    player_remove_object_from_backpack(game_get_current_player(game), objectId);
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  }
  else
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
  }
  return;
}

void game_actions_chat(Game *game, char *arg)
{
  Character *cha = NULL;
  if (!game)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*Por que no hablar con personajes no amistosos¿?
  if (!character_get_friendly(game_get_character_from_name(game, arg)))
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  */
  cha = game_get_character_from_name(game, arg);
  if(cha != NULL){
    game_set_show_message(game, TRUE);
    game_set_message(game, character_chat(cha));
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  }else{
    /*reset if we want the game to show the message*/
    game_set_show_message(game, FALSE);
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
  }
  
  return;
}

void game_actions_attack(Game *game, char *arg)
{
  int num, i, attacked_ally, teammates = 0, team;
  Character *enemy = NULL, *character=NULL;
  Id characterId;
  Space *player_space=NULL;
  Set *followers=NULL;
  num = rand() % 10;

  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  /*Error control*/
  if (!game)
  {
    return;
  }
  enemy = game_get_character_from_name(game, arg);
  if(enemy == NULL || character_get_location(enemy) != player_get_location(game_get_current_player(game)) || character_get_friendly(enemy) == TRUE || character_get_health(enemy) <= 0)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }


  player_space = game_get_space(game, game_get_current_player_location(game));
  if(player_space == NULL)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }



  /*Once we have checked the conditions are valid, we gather all of the player's allies in a set*/
  if(!(followers = set_create())){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*The player counts as a follower of themselves*/
  set_add(followers, player_get_id(game_get_current_player(game)));

  /*We add the rest of the followers in the space to the set*/
  for(i=0;i<space_get_n_characters(player_space);i++){
    characterId = space_get_character_in_pos(player_space, i);
    if(character_get_following(game_get_character(game, characterId)) == player_get_id(game_get_current_player(game))){
      set_add(followers, characterId);
    }
  }

  /*Depending on the number genered, either the enemy loses health or the player's team is damaged*/
  if (num <= ATTACK_CHANCE)
  {
    /*We generate a random number to determine who will receive damage from the enemy*/
    attacked_ally = rand() % (set_get_num_elements(followers));
    /*If the number is 0, it is the player who receives damage*/
    if(attacked_ally == 0){
      player_set_health(game_get_current_player(game), player_get_health(game_get_current_player(game)) - ENEMY_DAMAGE);
    }
    /*If the number is higher the 1, one of the allies receives damage*/
    else
    {
      character = game_get_character(game, set_get_Id_in_pos(followers, attacked_ally));
      character_set_health(character, character_get_health(character) - ENEMY_DAMAGE);
      if(character_get_health(character) <= 0){
        character_set_following(character, NO_ID);
      }
    }
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  }
  else
  {
    team = player_get_team(game_get_current_player(game));
    /* We look for teammates at the same space, this number will multiply the damage done to the character*/
    for(i = 0; i < game_get_n_players(game); i++){
      if(player_get_team(game_get_player_in_pos(game, i)) == team && player_get_location(game_get_player_in_pos(game, i)) == space_get_id(player_space)){
        teammates ++;
      }
    }
    /*if there are teammates attacking with the player, we show that there was a team attack*/
    if(teammates > 1){
      game_set_show_message(game, TRUE);
      game_set_message(game, "TEAM ATTACK!");
    }
    character_set_health(enemy, character_get_health(enemy) - (PLAYER_DAMAGE * set_get_num_elements(followers)) - (PLAYER_DAMAGE * (teammates - 1)));
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  }
  set_destroy(followers);
  return;
}

void game_actions_inspect(Game *game, char *arg)
{
  Id objectId = NO_ID;
  Space *current_space = NULL;
  int i;
  Object *object = NULL;
  Bool found = FALSE;

  if (!game || !arg)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  /*We find the object with tha name arg*/
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object = game_get_object_in_pos(game, i);
    if (strcasecmp(object_get_name(object), arg) == 0)
    {
      found = TRUE;
      break;
    }
  }

  if (found == FALSE)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  objectId = object_get_id(object);
  current_space = game_get_space(game, game_get_current_player_location(game));
  if (current_space == NULL)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  if (space_object_belongs(current_space, objectId) == FALSE && player_backpack_contains(game_get_current_player(game), objectId) == FALSE)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  game_set_description(game, object_get_description(game_get_object(game, objectId)));
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  return;
}

void game_actions_recruit(Game *game, char *arg){
  char message[MAX_MESSAGE];
  if(!game || !arg){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  /*In case the character is not friendly or it is already recruited, it cannot be recruited*/
  if(character_get_friendly(game_get_character_from_name(game, arg)) == FALSE || character_get_following(game_get_character_from_name(game, arg)) != NO_ID){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  if(!character_set_following(game_get_character_from_name(game, arg), player_get_id(game_get_current_player(game)))){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  sprintf(message, "%s recluited", arg);
  game_set_message(game, message);
  game_set_show_message(game, TRUE);
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  return;
}

void game_actions_abandon(Game *game, char *arg){
  if(!game || !arg){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  if(character_get_following(game_get_character_from_name(game, arg)) != player_get_id(game_get_current_player(game))){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  if(!character_set_following(game_get_character_from_name(game, arg), NO_ID)){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  return;
}

void game_actions_open(Game *game, char *arg) {
  char *second_arg = NULL;
  long name_length = 0;
  int i = 0;
  Object *o = NULL;
  Link *l = NULL;
  Id origin_id;

  /*argument validation*/
  if (!game || !arg) {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  if (strstr(arg, OPEN_ARG) != NULL) {
    second_arg = strstr(arg, OPEN_ARG) + strlen(OPEN_ARG);
  } else {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  origin_id = game_get_current_player_location(game);
  name_length = strlen(arg) - strlen(strstr(arg, OPEN_ARG));

  /*find the corresponding link*/
  for (i = 0 ; i < game_get_n_links(game) ; i++) {
    l = game_get_link(game, game_get_link_id_at(game, i));

    /*check if link name matches first argument in the command*/ 
    if (strncasecmp(link_get_name(l), arg, name_length) == 0) break;
  }

  /* check if link corresponds to current space, or if exit condition for loop was not found */
  if (link_get_origin_id(l) != origin_id || i == game_get_n_links(game)) {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*look for object in backpàck */
  for (i = 0 ; i < player_get_num_objects_in_backpack(game_get_current_player(game)) ; i++) {
    o = game_get_object(game, player_get_backpack_object_id_at(game_get_current_player(game), i));

    /*check if it is the correct object*/
    if (strcasecmp(object_get_name(o), second_arg) == 0 ) {

      /* check if object opens link*/
      if (object_get_open(o) != link_get_id(l)) {
        command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
        return;
      }

      /*check if player has the object dependency in case it exists*/
      if (object_get_dependency(o) != NO_ID && player_backpack_contains(game_get_current_player(game), object_get_dependency(o)) == FALSE) {
        command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
        return;
      }

      /* open link and remove object from backpack */
      link_set_is_open(l, TRUE);
      player_remove_object_from_backpack(game_get_current_player(game), object_get_id(o));
      command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
      return;
    }
  }

  /*in case function has not been exited, return with ERROR*/
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
  return;
}

void game_actions_save(Game *game, char *arg){
  if(!game || !arg){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  if(gameManagement_save(game, arg) == ERROR){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  return;

}

void game_actions_load(Game **game, char *arg){
  if(!game || !(*game) || !arg){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(*game, LAST), ERROR);
    return;
  }

  if(gameManagement_load(game, arg) == ERROR){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(*game, LAST), ERROR);
    return;
  }else{
    game_set_turn(*game, game_get_turn(*game) - 1);
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(*game, LAST), OK);
  }

  return;
}


void game_actions_team(Game *game, char *arg, Graphic_engine *gengine){
  Player *teammate = NULL;
  int i, turn = 0, current_turn; /*initialized turn to remove warnings - theoretically if there are no player in the game this could create issues in this function, but come on*/
  Bool show;
  char previous_message[MAX_MESSAGE], message[MAX_MESSAGE];
  Bool acceptance;

  if(!game || !arg) return;

  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  /*We found the player whose name is the argument given*/
  teammate = game_get_player_from_name(game, arg);
  if (teammate == NULL){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  /*We found the turn corresponding to the new teammate*/

  for(i = 0; i < game_get_n_players(game); i++){
    if(game_get_player_in_pos(game, i) == teammate){
      turn = i;
      break;
    }
  }
  current_turn = game_get_turn(game);

  game_set_turn(game, turn);
  /*copy the previous values for the last command used*/
  strcpy(previous_message, game_get_message(game));
  show = game_get_show_message(game);

  sprintf(message, "Player %d wants to team, accept or decline?(Y/N)", current_turn + 1);

  game_set_message(game, message);
  game_set_show_message(game, TRUE);

  graphic_engine_paint_game(gengine, game);
  acceptance = command_get_confirmation();

  /*set the values back */
  game_set_message(game, previous_message);
  game_set_show_message(game, show);
  /*get back to the turn*/
  game_set_turn(game, current_turn);

  if(acceptance == FALSE){
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }else{
    player_set_team(teammate, player_get_id(game_get_current_player(game)));
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
    return;
  }
}

void game_actions_turn(Game *game){
  if(!game) return;
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);

  game_next_turn(game);
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  return;
}


void game_actions_use(Game *game, char *object_name, char *character_name)
{

  Object *object = NULL;
  Character *character = NULL;

  if (game == NULL || object_name == NULL)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*Find the object by its name*/
  object = game_get_object_from_name(game, object_name);
  if (!object)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*Check if the object can be used (health is not 0)*/
  if (object_get_health(object) == 0)
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }

  /*If an optional character name is given, update the character's health*/
  if (character_name && character_name[0] != '\0')
  {
    character = game_get_character_from_name(game, character_name);
    if (character == NULL || character_get_friendly(character) == FALSE)
    {
      command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
      return;
    }
    if (character_set_health(character, character_get_health(character) + object_get_health(object)) == ERROR)
    {
      command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
      return;
    }
  }
  else
  {
    /*If there is no character's name passed, update player's health*/
    if (player_set_health(game_get_current_player(game), player_get_health(game_get_current_player(game)) + object_get_health(object)) == ERROR)
    {
      command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
      return;
    }
  }

  /*Remove the object from the game after use*/
  player_remove_object_from_backpack(game_get_current_player(game), object_get_id(object));
  if (!game_remove_object(game, object))
  {
    command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), ERROR);
    return;
  }
  command_set_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST), OK);
  /*reset if we want the game to show the message*/
  game_set_show_message(game, FALSE);
  return;

}