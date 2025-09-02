/**
 * @brief It implements the inventory module
 *
 * @file inventory.c
 * @author Carlos Méndez
 * @version 1.0
 * @date 20-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

/**
 * @def MAX_OBJECTS
 * @brief Defines the maximum amount of objects
 */
#define MAX_OBJECTS 25

/**
 * @brief Inventory
 *
 * This struct stores all the information of an inventory.
 */
struct _Inventory {
        Set *objs;    /**< A set for managing object ids*/
        int max_objs; /**< An int to store the number of ids in the set*/
};

/**
 * inventory_create allocates memory for a new inventory and
 * initializes its members
 */
Inventory *inventory_create(void) {
        Inventory *inventory = NULL;

        inventory = (Inventory *)malloc(sizeof(Inventory));

        /*Error control*/
        if (!inventory) {
                return NULL;
        }

        inventory->objs = set_create();
        inventory->max_objs = MAX_OBJECTS;

        return inventory;
}

Status inventory_destroy(Inventory *inventory) {
        set_destroy(inventory->objs);
        free(inventory);

        return OK;
}

int inventory_get_max_objs(const Inventory *inventory) {
        /*Error control*/
        if (!inventory) {
                return -1;
        }

        return inventory->max_objs;
}

int inventory_get_num_objects(const Inventory *inventory) {
        /*Error control*/
        if (!inventory) {
                return -1;
        }
        return set_get_nIds(inventory->objs);
}

Status inventory_set_max_objs(Inventory *inventory, int n) {
        /*Error control*/
        if (!inventory) {
                return ERROR;
        }

        inventory->max_objs = n;
        return OK;
}

Id inventory_get_object_id_at_index(const Inventory *inventory, int index) {
        /*Error control*/
        if (!inventory) {
                return NO_ID;
        }
        return set_get_id_at_index(inventory->objs, index);
}

Status inventory_add_object(Inventory *inventory, Id id) {
        /*Error control*/
        if ((!inventory) || (id == NO_ID) || set_get_nIds(inventory->objs) == inventory->max_objs) {
                return ERROR;
        }

        set_add(inventory->objs, id);
        return OK;
}

Id inventory_del_object(Inventory *inventory, Id id) {
        /*Error control*/
        if (!inventory || id == NO_ID) {
                return NO_ID;
        }

        return set_del(inventory->objs, id);
}

Bool inventory_has_object(const Inventory *inventory, Id object) {
        if (!inventory || object == NO_ID) {
                return FALSE;
        }

        return set_has(inventory->objs, object);
}

Status inventory_print(const Inventory *inventory) {
        /*Error control*/
        if (!inventory) {
                return ERROR;
        }

        printf("The maximum amount of objects of the inventory is: %d", inventory->max_objs);
        set_print(inventory->objs);
        return OK;
}
