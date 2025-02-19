/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

 #ifndef GAME_H
 #define GAME_H
 
 #include "command.h"
 #include "space.h"
 #include "types.h"
 #include "player.h"
 #include "Object.h"
 
 #define MAX_SPACES 100 /*The maximum ammount of spaces that can exist in the game*/
 
 typedef struct _Game Game;
 
 /**
  * @brief adds a new space to the array of spaces in the game structure
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a double pointer to the structure with the game's main information
  * @param space a pointer to the space that is going to be added
  * @return Status: if the function was completed succesfully
  */
 Status game_add_space(Game **game, Space *space);
 
 /**
  * @brief Dynamically allocates memory for the game and initializes all the structures components
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a double pointer to the structure with the game's main information
  * @return Status: if the function was completed succesfully
  */
 Status game_create(Game **game);
 
 /**
  * @brief creates the game calling game_create and reads a text file to get information about the spaces
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a double pointer to the structure with the game's main information
  * @param filename
  * @return Status: if the function was completed succesfully
  */
 Status game_create_from_file(Game **game, char *filename);
 
 /**
  * @brief frees all the dynamically allocated memory in the game structure
  *
  * @date 27-01-2025
  * @author Alvaro Inigo
  *
  * @param game a double pointer to the structure with the game's main information
  * @return Status: if the function was completed succesfully
  */
 Status game_destroy(Game **game);
 
 /**
  * @brief returns a pointer to the space that has the id passed as an argument
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a pointer to the structure with the game's main information
  * @param id the id of the desired space
  * @return a pointer to the desired space
  */
 Space *game_get_space(Game **game, Id id);
 
 /**
  * @brief returns the id of the player's location
  *
  * @date 27-01-2025
  * @author Alvaro Inigo
  *
  * @param game a pointer to the structure with the game's main information
  * @return the id of the player's location
  */
 Id game_get_player_location(Game **game);
 
 /**
  * @brief changes the id of the player's location to the one passed as an argument
  *
  * @date 27-01-2025
  * @author Alvaro Inigo
  *
  * @param game a pointer to the structure with the game's main information
  * @param id the id of the new location
  * @return Status: if the function was completed succesfully
  */
 Status game_set_player_location(Game **game, Id id);
 
 /**
  * @brief returns the id of the object's location
  *
  * @date 27-01-2025
  * @author Alvaro Inigo
  *
  * @param game a pointer to the structure with the game's main information
  * @return the id of the object's location
  */
 Id game_get_object_location(Game **game);
 
 /**
  * @brief changes the id of the object's location to the one passed as an argument
  *
  * @date 27-01-2025
  * @author Alvaro Inigo
  *
  * @param game a pointer to the structure with the game's main information
  * @param id the id of the new location
  * @return Status
  */
 Status game_set_object_location(Game **game, Id id);
 
 /**
  * @brief returns the last command of the game
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a pointer to the structure with the game's main information
  * @return a pointer to the last command
  */
 Command *game_get_last_command(Game **game);
 
 /**
  * @brief changes the game's last_cmd parameter to a pointer to a new last_cmd
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a pointer to the structure with the game's main information
  * @param command the new last_cmd
  * @return Status: if the function was completed succesfully
  */
 Status game_set_last_command(Game **game, Command *command);
 
 /**
  * @brief returns a boolean value that describes if the game has finished or not
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a pointer to the structure with the game's main information
  * @return Bool (TRUE or FALSE) that describes if the game is finished or not
  */
 Bool game_get_finished(Game **game);
 
 /**
  * @brief Changes the state of the game, starting or finishing it
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a pointer to the structure with the game's main information
  * @param finished the new boolean value that describes whether the game has finished or not
  * @return Status if the function has been completed succesfully
  */
 Status game_set_finished(Game *game, Bool finished);
 
 /**
  * @brief prints the id of the player's location, the object's location and prints the information regarding all the spaces in the game
  *
  * @date 27-01-2025
  * @author Profesores
  *
  * @param game a double pointer to the structure with the game's main information
  */
 void game_print(Game **game);
 /**
  * @brief Gets the player of the game(pointer)
  *
  * @date 12-02-2025
  * @author Alvaro Inigo
  *
  * @param game a double pointer to the strucuture.
  * @return a pointer to the player.
  */
 Player *game_get_player(Game **game);
 /**
  * @brief gets the object of the game(pointer)
  *
  * @date 12-02-2025
  * @author Alvaro Inigo
  *
  * @param game a double pointer
  * @return a pointer to the object
  */
 Object *game_get_object(Game **game);
 
 #endif
