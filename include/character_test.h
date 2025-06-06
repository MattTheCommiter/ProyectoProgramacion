
/**
 * @brief It declares the tests for the character module
 *
 * @file character_test.h
 * @author Alvaro Iñigo
 * @version 0.0
 * @date 17-03-2025
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

#include "test.h"
#include "character.h"
#include "test.h"

/**
 * @test Test character creation
 * @pre Character ID
 * @post Non NULL pointer to character
 */
void test01_character_create();

/**
 * @test Test character destruction
 * @pre Non NULL character
 * @post OK if successfully destroyed
 */
void test01_character_destroy();

/**
 * @test Test setting character ID
 * @pre Non NULL character, valid ID
 * @post Character ID is correctly updated
 */
void test01_character_set_id();

/**
 * @test Test setting character name
 * @pre Non NULL character, valid name
 * @post Character name is correctly updated
 */
void test01_character_set_name();

/**
 * @test Test setting character graphic description
 * @pre Non NULL character, valid gdesc
 * @post Character graphic description is correctly updated
 */
void test01_character_set_gdesc();

/**
 * @test Test setting dead character graphic description
 * @pre Non NULL character, valid gdesc
 * @post Character graphic description is correctly updated
 */
void test01_character_set_dead_gdesc();

/**
 * @test Test setting character health
 * @pre Non NULL character, valid health value
 * @post Character health is correctly updated
 */
void test01_character_set_health();

/**
 * @test Test setting character friendliness
 * @pre Non NULL character, valid boolean value
 * @post Character friendly status is correctly updated
 */
void test01_character_set_friendly();

/**
 * @test Test setting character message
 * @pre Non NULL character, valid message
 * @post Character message is correctly updated
 */
void test01_character_add_message();

/**
 * @test Test getting character ID
 * @pre Non NULL character
 * @post Correct character ID is returned
 */
void test01_character_get_id();

/**
 * @test Test getting character name
 * @pre Non NULL character with set name
 * @post Correct character name is returned
 */
void test01_character_get_name();

/**
 * @test Test getting character graphic description
 * @pre Non NULL character with set gdesc
 * @post Correct character gdesc is returned
 */
void test01_character_get_gdesc();

/**
 * @test Test getting character graphic description
 * @pre Non NULL character with set gdesc
 * @post Correct character gdesc is returned
 */
void test01_character_get_dead_gdesc();

/**
 * @test Test getting character health
 * @pre Non NULL character with set health
 * @post Correct character health is returned
 */
void test01_character_get_health();

/**
 * @test Test getting character friendliness
 * @pre Non NULL character with set friendliness
 * @post Correct character friendly status is returned
 */
void test01_character_get_friendly();

/**
 * @test Test getting character message
 * @pre Non NULL character with set message
 * @post Correct character message is returned
 */
void test01_character_get_message_in_pos();

/**
 * @test Test printing character
 * @pre Non NULL character
 * @post OK if character prints correctly
 */
void test01_character_print();

/**
 * @test Test character creation with NULL pointer
 * @pre NULL character
 * @post ERROR returned
 */
void test02_character_create();

/**
 * @test Test character destruction with NULL pointer
 * @pre NULL character
 * @post ERROR returned
 */
void test02_character_destroy();

/**
 * @test Test setting character ID with NULL character
 * @pre NULL character, valid ID
 * @post ERROR returned
 */
void test02_character_set_id();

/**
 * @test Test setting character name with NULL character
 * @pre NULL character, valid name
 * @post ERROR returned
 */
void test02_character_set_name();

/**
 * @test Test setting character graphic description with NULL character
 * @pre NULL character, valid gdesc
 * @post ERROR returned
 */
void test02_character_set_gdesc();

/**
 * @test Test setting dead character graphic description with NULL character
 * @pre NULL character, valid gdesc
 * @post ERROR returned
 */
void test02_character_set_dead_gdesc();

/**
 * @test Test setting character health with NULL character
 * @pre NULL character, valid health value
 * @post ERROR returned
 */
void test02_character_set_health();

/**
 * @test Test setting character friendliness with NULL character
 * @pre NULL character, valid boolean value
 * @post ERROR returned
 */
void test02_character_set_friendly();

/**
 * @test Test setting character message with NULL character
 * @pre NULL character, valid message
 * @post ERROR returned
 */
void test02_character_add_message();

/**
 * @test Test getting character ID with NULL character
 * @pre NULL character
 * @post NO_ID returned
 */
void test02_character_get_id();

/**
 * @test Test getting character name with NULL character
 * @pre NULL character
 * @post NULL returned
 */
void test02_character_get_name();

/**
 * @test Test getting character graphic description with NULL character
 * @pre NULL character
 * @post NULL returned
 */
void test02_character_get_gdesc();

/**
 * @test Test getting dead character graphic description with NULL character
 * @pre NULL character
 * @post NULL returned
 */
void test02_character_get_dead_gdesc();

/**
 * @test Test getting character health with NULL character
 * @pre NULL character
 * @post NO_HP returned
 */
void test02_character_get_health();

/**
 * @test Test getting character friendliness with NULL character
 * @pre NULL character
 * @post FALSE returned
 */
void test02_character_get_friendly();

/**
 * @test Test getting character message with NULL character
 * @pre NULL character
 * @post NULL returned
 */
void test02_character_get_message_in_pos();

/**
 * @test Test printing NULL character
 * @pre NULL character
 * @post ERROR returned
 */
void test02_character_print();

/**
 * @brief test setting following atribute of a NULL character
 * @pre NULL character
 * @post ERROR returned
 */
void test01_character_set_following();

/**
 * @brief test setting following atribute of a valid character
 * @pre valid character, valid Id '3'
 * @post OK returned
 */
void test02_character_set_following();

/**
 * @brief test getting the following atribute of a NULL character
 * @pre NULL pointer to character
 * @post OK returned
 */
void test01_character_get_following();

/**
 * @brief test getting the following atribute of a created character
 * @pre valid character with 5 as their 'following' Id value
 * @post Id '5' returned
 */
void test02_character_get_following();

/**
 * @brief test setting location atribute of a NULL character
 * @pre NULL character
 * @post ERROR returned
 */
void test01_character_set_location();

/**
 * @brief test setting location atribute of a valid character
 * @pre valid character, valid Id '3'
 * @post OK returned
 */
void test02_character_set_location();

/**
 * @brief test getting the location atribute of a NULL character
 * @pre NULL pointer to character
 * @post OK returned
 */
void test01_character_get_location();

/**
 * @brief test getting the location atribute of a created character
 * @pre valid character with 5 as their 'location' Id value
 * @post Id '5' returned
 */
void test02_character_get_location();

/**
 * @brief test getting the number of messsages of a NULL character
 * @pre Null pointer to character
 * @post int -1 returned
 */
void test01_character_get_n_messages();

/**
 * @brief test getting the number of messsages of a valid and created character
 * @pre pointer to a created character with 2 messages
 * @post int 2 returnes
 */
void test02_character_get_n_messages();


/**
 * @brief test getting a NULL pointer of character
 * @pre a NULL pointer to the character
 * @post int -1
 */
void test01_character_get_message_turn();


/**
 * @brief tests getting the message of a character created
 * @pre a valid character
 * @post int 0
 */
void test02_character_get_message_turn();


/**
 * @brief test chatting with a NULL character
 * @pre NULL pointer to character
 * @post char * NULL
 */
void test01_character_chat();

/**
 * @brief tests chatting with a valid and created character
 * @pre a valid pointer to character
 * @post char* the messages of the character
 */
void test02_character_chat();
#endif