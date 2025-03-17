/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Matteo Artunedo
 * @version 0.1
 * @date 24-02-2025
 * @copyright GNU Public License
 */

 #ifndef SET_TEST_H
 #define SET_TEST_H
 
 /**
 * @test Test the creation of a set
 * @pre No input parameters
 * @post A non-NULL pointer to a newly created set is returned
 */
 void test1_set_create();

/**
 * @test Test the creation of a set
 * @pre No input parameters
 * @post A non-NULL pointer to a newly created set is returned
 */
void test2_set_create();

 /**
 * @test Test the destruction of a set
 * @pre A valid pointer to a set
 * @post The function returns OK, indicating successful destruction
 */
 void test1_set_destroy();

 /**
 * @test Test the destruction of a NULL set
 * @pre A NULL pointer is passed as input
 * @post The function returns ERROR, indicating failure to destroy
 */
 void test2_set_destroy();
 
 /**
 * @test Test adding an element to an empty set
 * @pre A pointer to an empty set and an Id '3' to add
 * @post The function returns OK after successfully adding the Id
 */
 void test1_set_add();
 
 /**
 * @test Test adding an element to a non-empty set
 * @pre A pointer to a set containing one element ('5') and an Id '3' to add
 * @post The function returns OK after successfully adding the Id
 */
 void test2_set_add();
 
 /**
 * @test Test deleting an element not present in the set
 * @pre A pointer to a set containing the element '5' and an Id '3' to delete
 * @post The function returns ERROR, as the Id '3' is not in the set
 */
 void test1_set_del();
 
 /**
 * @test Test deleting an element present in the set
 * @pre A pointer to a set containing the element '5' and an Id '5' to delete
 * @post The function returns OK after successfully deleting the Id
 */
 void test2_set_del();

 /**
 * @test Test deleting an element from a NULL set
 * @pre A NULL pointer and an Id '5' to delete
 * @post The function returns ERROR, as the set pointer is NULL
 */
 void test3_set_del();

 /**
 * @test Test deleting an invalid Id (NO_ID) from a set
 * @pre A valid pointer to a set and an Id 'NO_ID'
 * @post The function returns ERROR, as NO_ID is invalid
 */
 void test4_set_del();
 
 /**
 * @test Test printing a NULL set
 * @pre A NULL pointer to a set
 * @post The function returns -1, indicating failure to print
 */
  void test1_set_print();
 /**
 * @test Test printing a set with one element
 * @pre A pointer to a set containing the element '3'
 * @post The function returns 1, indicating successful printing of "3"
 */
  void test2_set_print();
 /**
 * @test Test printing a set with multiple elements
 * @pre A pointer to a set containing the elements '3', '6', and '7'
 * @post The function returns 3, indicating successful printing of "3, 6, 7"
 */
  void test3_set_print();
 /**
 * @test Test checking if an element belongs to a NULL set
 * @pre A NULL pointer to a set and an Id '5'
 * @post The function returns FALSE, as the set pointer is NULL
 */
  void test1_set_belongs();
 /**
 * @test Test checking if an element belongs to a set
 * @pre A pointer to a set containing the element '5' and an Id '3'
 * @post The function returns FALSE, as the Id '3' is not in the set
 */
  void test2_set_belongs();
 /**
 * @test Test checking if an element belongs to a set
 * @pre A pointer to a set containing the element '5' and an Id '5'
 * @post The function returns TRUE, as the Id '5' is in the set
 */
  void test3_set_belongs();
 /**
 * @test Test checking if a NULL set is empty
 * @pre A NULL pointer to a set
 * @post The function returns FALSE, as the set pointer is NULL
 */
  void test1_set_is_empty();
 /**
 * @test Test checking if an empty set is empty
 * @pre A pointer to an empty set
 * @post The function returns OK, indicating the set is empty
 */
  void test2_set_is_empty();
  /**
  * @test Test set is empty
  * @pre pointer to set with element 5
  * @post Output==FALSE when checking if the set is empty
  */
  void test3_set_is_empty();

  /**
  * @test Test set is full with NULL set
  * @pre pointer to NULL set
  * @post Output==TRUE 
  */
  void test1_set_is_full();
  
  /**
  * @test Test set is full with empty set
  * @pre pointer to set with no elements
  * @post Output==FALSE 
  */
  void test2_set_is_full();
  
  /**
  * @test Test set is full with full set
  * @pre pointer to set with maximum number of elements
  * @post Output==TRUE
  */
  void test3_set_is_full();
  /**
  * @test Test set get number of elements from NULL pointer
  * @pre pointer to NULL
  * @post Output==-1 when getting the number of elements of a NULL pointer
  */
  void test1_set_get_num_elements();
  /**
  * @test Test set get number of elements from empty set
  * @pre pointer to empty set
  * @post Output==0 when returning the number of elements in the set
  */
  void test2_set_get_num_elements();
  /**
  * @test Test set get number of elements from set with 2 elements
  * @pre pointer to set with elements 3, 5
  * @post Output==2 when returning the number of elements
  */
  void test3_set_get_num_elements();
  /**
  * @test Test set get Id in a position with NULL pointer to set
  * @pre pointer to NULL, position 1
  * @post Output==-1 when trying to find 1 in the set
  */
  void test1_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position with empty set
  * @pre pointer to empty set, position 0
  * @post Output==-1 when accessing a position with no element
  */
  void test2_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position with a set containing one element and a valid position
  * @pre pointer to set with element 5, position 0
  * @post Output==5, which is the Id in position 0 in the set
  */
  void test3_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position with a set containing two elements and a valid position
  * @pre pointer to set with elements 5 and 3, position 1
  * @post Output==3, which is in position 1
  */
  void test4_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position, invalid position, valid pointer to set
  * @pre pointer to set with element 5, position -1
  * @post Output==-1 because of invalid position
  */
  void test5_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position, invalid position, valid pointer to set
  * @pre pointer to set with elements 5 and 3, position 2
  * @post Output==-1 because of invalid position
  */
  void test6_set_get_Id_in_pos();

  /**
  * @test Test set get position of an id with NULL pointer to set
  * @pre pointer to NULL, Id '3'
  * @post Output==-1 because of pointer to NULL
  */
  void test1_set_get_pos_from_Id();

  /**
  * @test Test set get position of an id with empty set
  * @pre pointer to empty set, Id '3'
  * @post Output==-1 because of empty set
  */
  void test2_set_get_pos_from_Id();
  
  /**
  * @test Test set get position of an id that is not present in the set
  * @pre pointer to set with element '5', Id '3'
  * @post Output==-1 because '3' is not in set
  */
  void test3_set_get_pos_from_Id();
  
  /**
  * @test Test set get position of an id that is present in the set
  * @pre pointer to set with elements '5' and '3', Id '3'
  * @post Output==1, which is the position of the Id '3'
  */
  void test4_set_get_pos_from_Id();
 
  #endif  