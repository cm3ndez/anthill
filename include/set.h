/**
 * @brief It defines the set module
 *
 * @file set.h
 * @author Abraham Martín
 * @version 1.0
 * @date 21-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

/**
 * @def LIST_LENGTH
 * @brief The length of the string representing the list of objects
 */
#define LIST_LENGTH 50

/**
 * @brief Set
 *
 * This struct stores all the info related to a Set
 */
typedef struct _Set Set;

/**
 * @brief Allocates memory for an initialized set
 * @author Abraham Martín
 *
 * @return Pointer, Pointer to the created Set
 */
Set *set_create(void);

/**
 * @brief Frees the memory used by the given set
 * @author Abraham Martín
 *
 * @param s Pointer to the set it has to free
 * @return OK if it could be destroyed, ERROR otherwise
 */
Status set_destroy(Set *s);

/**
 * @brief Retrieves the number of ids of a given set
 * @author Abraham Martín
 *
 * @param s Pointer to a set
 * @return Number of ids of the given set, or -1 if there was any error
 */
int set_get_nIds(const Set *s);

/**
 * @brief It adds an Id to a given set
 * @author Abraham Martín
 *
 * @param s Pointer to a set
 * @param id Id to be added to the set
 * @return OK if the Id could be added, ERROR otherwise
 */
Status set_add(Set *s, Id id);

/**
 * @brief It deletes and Id given in a given set
 * @author Abraham Martín
 *
 * @param s Pointer to a set
 * @param id Id to be deleted to the set
 * @return The id that has been removed
 */
Id set_del(Set *s, Id id);

/**
 * @brief It asserts wether it belongs to the set
 * @author Abraham Martín
 *
 * @param s Pointer to a set
 * @param id Id we want to check
 * @return TRUE if the object belongs to the set, FALSE otherwise
 */
Bool set_has(const Set *s, Id id);

/**
 * @brief Gets the id in a set given its position
 * @author Abraham Martín
 *
 * @param set Pointer to set
 * @param index Int storing the position of the id to be found
 * @return The id corresponding to the given position or NO_ID if there was an error
 */
Id set_get_id_at_index(const Set *set, int index);

/**
 * @brief It prints a given set
 * @author Abraham Martín
 *
 * @param s Pointer to a set
 * @return OK if the Id could be printed, ERROR otherwise
 */
Status set_print(const Set *s);

#endif
