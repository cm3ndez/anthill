/**
 * @brief It defines the space module
 *
 * @file space.h
 * @author Carlos Méndez, Abraham Martín and Jorge Ochoa
 * @version 3.0
 * @date 28-03-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "set.h"
#include "types.h"

/**
 * @def GDESC_LINES
 * @brief Represents the number of rows of the graphical representation of the space
 */
#define GDESC_LINES 8

/**
 * @def LINE_LENGTH
 * @brief Represents the number of columnss of each row
 */
#define LINE_LENGTH 30

/**
 * @brief Space
 *
 * This struct stores all the information related to a space.
 */
typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Carlos Méndez
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Carlos Méndez
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(const Space* space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return a string with the name of the space
 */
const char* space_get_name(const Space* space);

/**
 * @brief Sets the discovered status of a space
 * @author Jorge Ochoa
 *
 * @param space a pointer to the space
 * @param discovered a boolean value indicating whether the space is discovered
 * @return OK if the operation was successful, ERROR otherwise
 */
Status space_set_discovered(Space* space, Bool discovered);

/**
 * @brief Gets the discovered status of a space
 * @author Jorge Ochoa
 *
 * @param space a pointer to the space
 * @return TRUE or FALSE, depending if the space is discovered or not, FALSE otherwise
 */
Bool space_get_discovered(const Space* space);

/**
 * @brief It adds an object to the space
 * @author Abraham Martín
 *
 * @param space a pointer to the space
 * @param id the Id of the obejct to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space* space, Id id);

/**
 * @brief It deletes an object with an especific id
 * @author Abraham Martín
 *
 * @param space a pointer to the space
 * @param id the Id of the object to be removed
 * @return The id of the object that has been removed
 */
Id space_del_object(Space* space, Id id);

/**
 * @brief It adds a new character to the space
 * @author Jorge Ochoa
 *
 * @param space a pointer to the space
 * @param id the Id of the character to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_character(Space* space, Id id);

/**
 * @brief It deletes a character with an especific id
 * @author Jorge Ochoa
 *
 * @param space a pointer to the space
 * @param id the Id of the character to be removed
 * @return The id of the character that has been removed
 */
Id space_del_character(Space* space, Id id);

/**
 * @brief Set the graphical description of a space
 * @author Carlos Méndez
 *
 * @param space Pointer to the space
 * @param gdesc Array containing the graphical description
 * @return OK if successful, ERROR otherwise
 */
Status space_set_gdesc(Space* space, char gdesc[GDESC_LINES][LINE_LENGTH + 1]);

/**
 * @brief Get the graphical description of a space for a given row
 * @author Carlos Méndez
 *
 * @param space Pointer to the space
 * @param row_num Row index
 * @return Pointer to the graphical row description or EMPTY_ROW if invalid
 */
const char* space_get_gdesc(const Space* space, int row_num);

/**
 * @brief Get the number of objects in a space
 * @author Abraham Martín
 *
 * @param space Pointer to the space
 * @return Number of objects in the space or 0 if NULL
 */
int space_get_num_objects(const Space* space);

/**
 * @brief Get the number of characters in a space
 * @author Jorge Ochoa
 *
 * @param space Pointer to the space
 * @return Number of characters in the space or 0 if NULL
 */
int space_get_num_characters(const Space* space);

/**
 * @brief States if a space has a certain object or not
 * @author Abraham Martín
 *
 * @param space Pointer to a space
 * @param id the Id of the object to be checked
 * @return TRUE if the object is in the space or FALSE otherwise
 */
Bool space_has_object(const Space* space, Id id);

/**
 * @brief States if a space has a certain character or not
 * @author Jorge Ochoa
 *
 * @param space Pointer to a space
 * @param id the Id of the character to be checked
 * @return TRUE if the character is in the space or FALSE otherwise
 */
Bool space_has_character(const Space* space, Id id);

/**
 * @brief Get the character ID in a space
 * @author Abraham Martín
 *
 * @param space Pointer to the space
 * @return Character ID or NO_ID if NULL
 */
Id space_get_character_id(const Space* space);

/**
 * @brief Set the characters in a space
 * @author Abraham Martín
 *
 * @param space Pointer to the space
 * @param id Character ID
 * @return OK if successful, ERROR otherwise
 */
Status space_set_characters(Space* space, Id id);

/**
 * @brief Get the ID of an object at a given index in a space
 * @author Abraham Martín
 *
 * @param space Pointer to the space
 * @param index Index position
 * @return Object ID or NO_ID if invalid
 */
Id space_get_id_at_index(const Space*, int index);

/**
 * @brief It prints the space information about the id and name of the space, the spaces that
 * surrounds it and wheter it has an object or not.
 * @author Carlos Méndez
 *
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(const Space* space);

#endif
