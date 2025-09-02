/**
 * @brief It defines the inventory module
 *
 * @file inventory_test.h
 * @author Carlos Méndez
 * @version 1.0
 * @date 20-03-2025
 * @copyright GNU Public License
 */
#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

/**
 * @brief Inventory
 *
 * This struct stores all the information related to an Inventory
 */
typedef struct _Inventory Inventory;

/**
 * @brief It creates a new inventory, allocating memory and initializing its parts
 * @author Carlos Méndez
 *
 * @return A pointer to the new inventory
 */
Inventory *inventory_create(void);

/**
 * @brief It destroys a given inventory, freeing its memory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @return OK if the inventory has been sucssefully destroyed and an ERROR otherwise
 */
Status inventory_destroy(Inventory *inventory);

/**
 * @brief It gets the maximum number of objects an inventory can hold
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @return The maximum number of objects or -1 if an error occurs
 */
int inventory_get_max_objs(const Inventory *inventory);

/**
 * @brief It gets the current number of objects of the inventory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @return The current number of objects or -1 if an error occurs
 */
int inventory_get_num_objects(const Inventory *inventory);

/**
 * @brief It sets the maximum number of objects an inventory can hold
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @param n The new maximum number of objects
 * @return OK if the value has been successfully set and ERROR otherwise
 */
Status inventory_set_max_objs(Inventory *inventory, int n);

/**
 * @brief It gets the object ID stored at a specific index in the inventory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @param index Index position to retrieve the object ID
 * @return The object ID at the given index or NO_ID if an error occurs
 */
Id inventory_get_object_id_at_index(const Inventory *inventory, int index);

/**
 * @brief It adds an object ID to the inventory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @param id ID of the object to be added
 * @return OK if the object has been successfully added and ERROR otherwise
 */
Status inventory_add_object(Inventory *inventory, Id id);

/**
 * @brief It deletes an object ID from the inventory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @param id ID of the object to be removed
 * @return The ID of the deleted object or NO_ID if an error occurs
 */
Id inventory_del_object(Inventory *inventory, Id id);

/**
 * @brief It states if an object ID is in the inventory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to an inventory
 * @param object ID of the object to be checked
 * @return The TRUE if the Object is in the inventory or ERROR otherwise
 */
Bool inventory_has_object(const Inventory *inventory, Id object);

/**
 * @brief It prints the contents of an inventory
 * @author Carlos Méndez
 *
 * @param inventory Pointer to inventory
 * @return OK if it was able to print and ERROR otherwise
 */

Status inventory_print(const Inventory *);
#endif
