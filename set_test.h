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
  * @pre
  * @post Non NULL pointer to set 
  */
 void test1_set_create();

  /**
  * @test Test set creation
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
  * @pre pointer to set
  * @post Output == OK when adding 3 as an Id
  */
 void test1_set_add();
 
 /**
  * @test Test set add
  * @pre pointer to set with one element: 5 
  * @post Ouput==OK when adding 3
  */
 void test2_set_add();
 
 /**
  * @test Test set del
  * @pre pointer to set with element 5
  * @post Output==ERROR when trying to delete 3
  */
 void test1_set_del();
 
 /**
  * @test Test set del
  * @pre pointer to set_name with element 5
  * @post Output==OK when deleting 5
  */
 void test2_set_del();


 #endif  