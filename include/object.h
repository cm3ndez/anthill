/**
 * @brief It defines the object module
 *
 * @file object.h
 * @author Carlos Méndez
 * @version 2.0
 * @date 21-03-2025
 * @copyright GNU Public License
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

/**
 * @brief Object
 *
 * This struct stores all the information related to an Object
 */
typedef struct _Object Object;

/**
 * @brief It creates a new object, allocating memory and initializing its parts
 * @author Carlos Méndez
 *
 * @param id the identification number for the new object
 * @return object a new object, initialized
 */
Object *object_create(Id id);

/**
 * @brief It destroys a given object, freeing its memory
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @return OK if the object has been sucssefully destroyed and an ERROR otherwise
 */
Status object_destroy(Object *object);

/**
 * @brief It determines the Id of a given object
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @return id of the given object
 */
Id object_get_id(const Object *object);

/**
 * @brief It sets de name of the object
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @param name a string that contains the name
 * @return OK if the name was set correctly and ERROR otherwise
 */
Status object_set_name(Object *object, char *name);

/**
 * @brief It gets the name of a given object
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return string name of the object
 */
const char *object_get_name(const Object *object);

/**
 * @brief It sets de description of the object
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @param description a string that contains the description
 * @return OK if the description was set correctly and ERROR otherwise
 */
Status object_set_description(Object *object, char *description);

/**
 * @brief It gets the description of a given object
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return string description of the object
 */
const char *object_get_description(const Object *object);

/**
 * @brief It sets the health value of the object
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @param health Integer value representing the object's health
 * @return OK if the health was set correctly and ERROR otherwise
 */
Status object_set_health(Object *object, int health);

/**
 * @brief It gets the health value of the object
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return Integer health value of the object
 */
int object_get_health(const Object *object);

/**
 * @brief It sets whether the object is movable or not
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @param movable Boolean value indicating if the object can be moved
 * @return OK if the value was set correctly and ERROR otherwise
 */
Status object_set_movable(Object *object, Bool movable);

/**
 * @brief It gets whether the object is movable or not
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return Boolean value indicating if the object is movable
 */
Bool object_get_movable(const Object *object);

/**
 * @brief It sets the dependency of the object on another object by its ID
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @param dependency ID of the object this object depends on
 * @return OK if the dependency was set correctly and ERROR otherwise
 */
Status object_set_dependency(Object *object, Id dependency);

/**
 * @brief It gets the ID of the object this object depends on, if any
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return ID of the object it depends on, or NO_ID if none
 */
Id object_get_dependency(const Object *object);

/**
 * @brief It sets the ID of the object that opens this one (e.g., a key or switch ID)
 * @author Carlos Méndez
 *
 * @param object Pointer to an object
 * @param open ID of the object that can open this one
 * @return OK if the open ID was set correctly and ERROR otherwise
 */
Status object_set_open(Object *object, Id open);

/**
 * @brief It gets the ID of the object that opens this one
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return ID of the object that opens it, or NO_ID if none
 */
Id object_get_open(const Object *object);

/**
 * @brief It prints the contents of an object
 * @author Carlos Méndez
 *
 * @param object Pointer to object
 * @return OK if it was able to print and ERROR otherwise
 */
Status object_print(const Object *);

#endif
