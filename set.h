/**
 * @brief It defines the set module
 *
 * @file set.h
 * @author Matteo Artunedo
 * @version 0
 * @date 18-02-2025
 * @copyright GNU Public License
 */

 #ifndef SET_H
 #define SET_H

 #include <stdio.h>
 #include <stdlib.h>
 #include "types.h"

typedef struct _Set Set;
/**
 * @brief creates an empty set
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @return a pointer to the created set
 */
Set *set_create();
/**
 * @brief destroys an existing set
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @param s pointer to the set that is going to be destroyed
 * @return Status: whether the function was completed succesfully
 */
Status set_destroy(Set *s);
/**
 * @brief adds a new element to a given set
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set where the element will be added
 * @param elementId the id of the new element
 * @return returns OK if the element is added or if the element is already in the set and ERROR if the given pointer to the set is NULL
 */
Status set_add(Set *s, Id elementId);
/**
 * @brief Deletes an element of a set. If the element is not in the set, the function does nothing.
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set where the element will be deleted
 * @param elementId the id of the element we want to delete
 * @return OK if the element is succesfully deleted or wasn't in the set in the first place, or ERROR if the element could not be deleted
 */
Status set_del(Set *s, Id elementId);

/**
 * @brief prints the elements of the set
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set that will be printed
 * @return number of elements printed or -1 if an error occurrs
 */
int set_print(Set *s);

/**
 * @brief Returns whether an element is found in a set or not
 *
 * @date 27-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set where the element will be looked for
 * @param elementId the id of the element we want to look for
 * @return TRUE if the element is in s and FALSE if it is not
 */
Bool set_belongs(Set *s, Id elementId);

/**
 * @brief Returns whether a set is empty or not
 *
 * @date 27-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set 
 * @return TRUE if the set is empty and FALSE if it contains element(s)
 */
Bool set_is_empty(Set *s);

/**
 * @brief Returns the number of elements in the set
 *
 * @date 27-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set 
 * @return number of elements in set or -1 if error occurs
 */
int set_get_num_elements(Set *s);

/**
 * @brief Returns the Id of the element in a determined position
 *
 * @date 27-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set 
 * @param pos position of the Id we want
 * @return Id of the element in position pos and -1 if the position is not valid or an error occurred
 */
Id set_get_Id_in_pos(Set *s, int pos);

test1_set_print();
test2_set_print();
test3_set_print();
test1_set_belongs();
test2_set_belongs();
test3_set_belongs();
test1_set_is_empty();
test2_set_is_empty();
test3_set_is_empty();
test1_set_get_num_elements();
test2_set_get_num_elements();
test3_set_get_num_elements();
test1_set_get_Id_in_pos();
test2_set_get_Id_in_pos();
test3_set_get_Id_in_pos();
test4_set_get_Id_in_pos();
test5_set_get_Id_in_pos();
test6_set_get_Id_in_pos();







#endif