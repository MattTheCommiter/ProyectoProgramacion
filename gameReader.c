/**
 * @file It implements the reading and loading of spaces
 * @author Alvaro Inigo
 * @version 0.1
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 /* Se incluyen los archivos .h pertinentes para el funcionamiento del programa*/
 #include "gameReader.h"
 #include "game.h"
 
 Status gameReader_load_spaces(Game *game, char *filename)
 {
   FILE *file = NULL;
   char line[WORD_SIZE] = "";
   char name[WORD_SIZE] = "";
   char **read_gdesc;
   char *toks = NULL;
   int i;
   Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
   Space *space = NULL;
   Status status = OK;
 
   if(!(read_gdesc = (char **)calloc(N_LINES_IN_GDESC, sizeof(char *)))){
    return ERROR;
   }
   if(!(read_gdesc[0] = (char *)calloc(N_LINES_IN_GDESC*(N_ROWS_IN_GDESC + 1), sizeof(char)))){
    free(read_gdesc);
    return ERROR;
   }
   for(i=1;i<5;i++){
       read_gdesc[i] = read_gdesc[0] + (N_ROWS_IN_GDESC + 1)*i;
   }

  

   if (!filename)
   {
     return ERROR;
   }
 
   file = fopen(filename, "r");
   if (file == NULL)
   {
     return ERROR;
   }
   /**
    * @brief reads the file and load each data individually.
    *
    */
   while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
   {
     if (strncmp("#s:", line, 3) == 0)
     {
       toks = strtok(line + 3, "|");
       id = atol(toks);
       toks = strtok(NULL, "|");
       strcpy(name, toks);
       toks = strtok(NULL, "|");
       north = atol(toks);
       toks = strtok(NULL, "|");
       east = atol(toks);
       toks = strtok(NULL, "|");
       south = atol(toks);
       toks = strtok(NULL, "|");
       west = atol(toks);

       if((toks = strtok(NULL, "|\n\r")) != NULL){
          strcpy(read_gdesc[0], toks);
          toks = strtok(NULL, "|");
          if(toks){
            strcpy(read_gdesc[1], toks);
          }else{
            game_set_finished(game, TRUE);
            fprintf(stdout, "Invalid graphic description");
          }
          toks = strtok(NULL, "|");
          if (toks) {
            strcpy(read_gdesc[2], toks);
          }else{
            game_set_finished(game, TRUE);
            fprintf(stdout, "Invalid graphic description");
          }
          toks = strtok(NULL, "|");
          if (toks) {
            strcpy(read_gdesc[3], toks);
          }else{
            game_set_finished(game, TRUE);
            fprintf(stdout, "Invalid graphic description");
          }
          toks = strtok(NULL, "|");
          if (toks) {
            strcpy(read_gdesc[4], toks);
          }else{
            game_set_finished(game, TRUE);
            fprintf(stdout, "Invalid graphic description");
          }
          }else{
          strcpy(read_gdesc[0], "         ");
          strcpy(read_gdesc[1], "         ");
          strcpy(read_gdesc[2], "         ");
          strcpy(read_gdesc[3], "         ");
          strcpy(read_gdesc[4], "         ");
       }


 #ifdef DEBUG
       printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
 #endif
       /*
        * It creates the space with the data that has been read
        */
       space = space_create(id); /*calls to space_create providing the id written in the file*/
       if (space != NULL)
       { /*Sets the information related to the space and adds it to the game*/
         space_set_name(space, name);
         space_set_north(space, north);
         space_set_east(space, east);
         space_set_south(space, south);
         space_set_west(space, west);
         game_add_space(game, space);
         space_set_gdesc(space, read_gdesc);
       }else{
        fclose(file);
        free(read_gdesc[0]);
        free(read_gdesc);
        return ERROR;
       }
      }
   }
   free(read_gdesc[0]);
   free(read_gdesc);
   if (ferror(file))
   {
     status = ERROR;
   }
 
   fclose(file);
 
   return status;
 }

 Status gameReader_load_objects(Game *game, char *filename)
 {
   FILE *file = NULL;
   char line[WORD_SIZE] = "";
   char name[WORD_SIZE] = "";
   char *toks = NULL;
   Id id = NO_ID, spaceId = NO_ID;
   Object *object = NULL;
   Status status = OK;
 
   if (!filename)
   {
     return ERROR;
   }
 
   file = fopen(filename, "r");
   if (file == NULL)
   {
     return ERROR;
   }
   /**
    * @brief reads the file and load each data individually.
    *
    */
   while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
   {
     if (strncmp("#o:", line, 3) == 0)
     {
       toks = strtok(line + 3, "|");
       id = atol(toks);
       toks = strtok(NULL, "|");
       strcpy(name, toks);
       toks = strtok(NULL, "|");
       spaceId = atol(toks);
       
       
 #ifdef DEBUG
       printf("Leido: %ld|%s|%ld\n", id, name, spaceId);
 #endif
       /*
        * It creates the space with the data that has been read
        */
       object = object_create(id); /*calls to object_create providing the id written in the file*/
       if (object != NULL)
       { /*Sets the information related to the object and adds it to the game*/
         object_set_name(object, name);
         space_add_objectId(game_get_space(game,spaceId),id);
         game_add_object(game, object);
       }
     }
   }
 
   if (ferror(file))
   {
     status = ERROR;
   }
 
   fclose(file);
 
   return status;
 }