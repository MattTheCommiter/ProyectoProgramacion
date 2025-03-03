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
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
 void test2_set_del();
 
  /**
  * @test Test set print
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test1_set_print();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test2_set_print();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test3_set_print();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test1_set_belongs();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test2_set_belongs();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test3_set_belongs();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test1_set_is_empty();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test2_set_is_empty();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test3_set_is_empty();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test1_set_get_num_elements();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test2_set_get_num_elements();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test3_set_get_num_elements();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test1_set_get_Id_in_pos();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test2_set_get_Id_in_pos();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test3_set_get_Id_in_pos();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test4_set_get_Id_in_pos();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test5_set_get_Id_in_pos();
   /**
  * @test Test set del
  * @pre pointer to set_name with element 5, Id '5' of the element we want to delete
  * @post Output==OK when deleting 5
  */
  void test6_set_get_Id_in_pos();


 #endif  