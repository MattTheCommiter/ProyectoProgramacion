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
Status *set_destroy(Set *s);
/**
 * @brief adds a new element to a given set
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set where the element will be added
 * @param elementId the id of the new element
 * @return returns TRUE if the element is added and FALSE if the element is already in the set or if the given pointer to the set is NULL
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
 * @return TRUE if the element is succesfully deleted or wasn't in the set in the first place, or FALSE if the element could not be deleted
 */
Status set_del(Set *s, Id elementId);
/**
 * @brief prints the elements of the set
 *
 * @date 18-02-2025
 * @author Matteo Artunedo
 *
 * @param s a pointer to the set that will be printed
 */
void set_print(Set *s);


#endif