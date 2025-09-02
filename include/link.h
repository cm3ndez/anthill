/**
 * @brief It defines the link module
 *
 * @file link.h
 * @author Jorge Ochoa
 * @version 0
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

/**
 * @brief Link
 *
 * This struct stores all the information related to a Link.
 */
typedef struct _Link Link;

/**
 * @brief Allocates memory for a new link and sets every field to 0 or NULL
 * @author Jorge Ochoa
 *
 * @param id Id of the link that we want to create
 * @return Pointer to the link created, or NULL if there was an ERROR
 */
Link *link_create(Id id);

/**
 * @brief Destroys and frees the memory of the link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link we want to destroy
 * @return OK if it is destroyed, ERROR if something happened
 */
Status link_destroy(Link *link);

/**
 * @brief Sets the ID of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @param id The ID to assign
 * @return OK if successful, ERROR otherwise
 */
Status link_set_id(Link *link, Id id);

/**
 * @brief Gets the ID of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @return The ID of the link, or NO_ID if an error occurs
 */
Id link_get_id(const Link *link);

/**
 * @brief Sets the name of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @param name String with the new name to assign
 * @return OK if successful, ERROR otherwise
 */
Status link_set_name(Link *link, char *name);

/**
 * @brief Gets the name of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @return The name of the link, or NULL if an error occurs
 */
const char *link_get_name(const Link *link);

/**
 * @brief Sets the origin of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @param id_origin The origin ID to assign
 * @return OK if successful, ERROR otherwise
 */
Status link_set_origin(Link *link, Id id_origin);

/**
 * @brief Gets the origin of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @return The origin ID, or NO_ID if an error occurs
 */
Id link_get_origin(const Link *link);

/**
 * @brief Sets the destination of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @param id_destination The destination ID to assign
 * @return OK if successful or ERROR otherwise
 */
Status link_set_destination(Link *link, Id id_destination);

/**
 * @brief Gets the destination of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @return The destination ID or NO_ID if an error occurs
 */
Id link_get_destination(const Link *link);

/**
 * @brief Sets the direction of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @param direction The direction to assign
 * @return OK if successful or ERROR otherwise
 */
Status link_set_direction(Link *link, Direction direction);

/**
 * @brief Gets the direction of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @return The direction of the link (N,W,S,E), or 0(N) if an error occurs
 */
Direction link_get_direction(const Link *link);

/**
 * @brief Sets the open status of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @param open The open status to assign
 * @return OK if successful or ERROR otherwise
 */
Status link_set_open(Link *link, Bool open);

/**
 * @brief Gets the open status of a link
 * @author Jorge Ochoa
 *
 * @param link Pointer to the link
 * @return TRUE if the link is open, FALSE otherwise
 */
Bool link_get_open(const Link *link);

/**
 * @brief It prints the link information.
 * @author Jorge Ochoa
 *
 *
 * @param link Pointer to the link
 * @return OK if everything goes well or ERROR if there was some mistake
 */
Status link_print(const Link *link);

#endif
