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
  * @test Test set creation
  * @pre void
  * @post Non NULL pointer to set 
  */
 void test1_set_create();

  /**
  * @test Test set destruction
  * @pre pointer to set
  * @post Output==OK
  */
 void test1_set_destroy();

  /**
  * @test Test set destruction
  * @pre Null pointer
  * @post Output==ERROR
  */
 void test2_set_destroy();
 
 /**
  * @test Test set add
  * @pre pointer to empty set, Id '3' of an element we want to add
  * @post Output == OK when adding 3 as an Id
  */
 void test1_set_add();
 
 /**
  * @test Test set add
  * @pre pointer to set with one element '5', Id '3' of an element we want to add 
  * @post Ouput==OK when adding 3 as an Id
  */
 void test2_set_add();
 
 /**
  * @test Test set del
  * @pre pointer to set with element '5', Id '3' of the element we want to delete
  * @post Output==ERROR when trying to delete 3
  */
 void test1_set_del();
 
 /**
  * @test Test set del
  * @pre pointer to set with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
 void test2_set_del();
 
  /**
  * @test Test set print
  * @pre pointer to NULL
  * @post Output==-1 when trying to print the set
  */
  void test1_set_print();
  /**
  * @test Test set print
  * @pre pointer to set with one element: 3
  * @post Output==1 when printing "3"
  */
  void test2_set_print();
  /**
  * @test Test set print
  * @pre pointer to set with elements 3, 6, 7
  * @post Output==3 when printing "3, 6, 7 "
  */
  void test3_set_print();
  /**
  * @test Test set belongs
  * @pre pointer to NULL and Id 5
  * @post Output==FALSE when looking for 5 in a NULL pointer
  */
  void test1_set_belongs();
  /**
  * @test Test set belongs
  * @pre pointer to set with element 5
  * @post Output==FALSE when checking if 3 belongs to the set
  */
  void test2_set_belongs();
  /**
  * @test Test set belongs
  * @pre pointer to set with element 5
  * @post Output==TRUE when checking if 5 belongs to the set
  */
  void test3_set_belongs();
  /**
  * @test Test set is empty
  * @pre pointer to NULL
  * @post Output==FALSE when receiving a NULL pointer
  */
  void test1_set_is_empty();
  /**
  * @test Test set is empty
  * @pre pointer to empty set 
  * @post Output==OK when checking that the set is empty
  */
  void test2_set_is_empty();
  /**
  * @test Test set is empty
  * @pre pointer to set with element 5
  * @post Output==FALSE when checking if the set is empty
  */
  void test3_set_is_empty();
  /**
  * @test Test set get number of elements
  * @pre pointer to NULL
  * @post Output==-1 when getting the number of elements of a NULL pointer
  */
  void test1_set_get_num_elements();
  /**
  * @test Test set get number of elements
  * @pre pointer to empty set
  * @post Output==0 when returning the number of elements in the set
  */
  void test2_set_get_num_elements();
  /**
  * @test Test set get number of elements
  * @pre pointer to set with elements 3, 5
  * @post Output==2 when returning the number of elements
  */
  void test3_set_get_num_elements();
  /**
  * @test Test set get Id in a position
  * @pre pointer to NULL, position 1
  * @post Output==-1 when trying to find 1 in the set
  */
  void test1_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position
  * @pre pointer to empty set, position 0
  * @post Output==-1 when accessing a position with no element
  */
  void test2_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position
  * @pre pointer to set with element 5, position 0
  * @post Output==5, which is the Id in position 0 in the set
  */
  void test3_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position
  * @pre pointer to set with elements 5 and 3, position 1
  * @post Output==3, which is in position 1
  */
  void test4_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position
  * @pre pointer to set with element 5, position -1
  * @post Output==-1 because of invalid position
  */
  void test5_set_get_Id_in_pos();
  /**
  * @test Test set get Id in a position
  * @pre pointer to set with elements 5 and 3, position 2
  * @post Output==-1 because of invalid position
  */
  void test6_set_get_Id_in_pos();

  /**
  * @test Test set get position of an id
  * @pre pointer to NULL, Id '3'
  * @post Output==-1 because of pointer to NULL
  */
  void test1_set_get_pos_from_Id();

  /**
  * @test Test set get position of an id
  * @pre pointer to empty set, Id '3'
  * @post Output==-1 because of empty set
  */
  void test2_set_get_pos_from_Id();
  
  /**
  * @test Test set get position of an id
  * @pre pointer to set with element '5'L, Id '3'
  * @post Output==-1 because '3' is not in set
  */
  void test3_set_get_pos_from_Id();
  
  /**
  * @test Test set get position of an id
  * @pre pointer to set with elements '5' and '3', Id '3'
  * @post Output==1, which is the position of the Id '3'
  */
  void test4_set_get_pos_from_Id();
 
  #endif  