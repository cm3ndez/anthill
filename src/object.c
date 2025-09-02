/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Carlos Méndez
 * @version 2.0
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def DESCRIPTION_SIZE
 * @brief Defines the maximum for size of the object's description
 */
#define DESCRIPTION_SIZE 400

/**
 * @brief _Object private struct
 */
struct _Object {
        Id id;                                  /**< Unique id*/
        char name[WORD_SIZE];                   /**< Object's name*/
        char description[DESCRIPTION_SIZE + 1]; /**< Message of the desciption*/
        int health;                             /**<Amount of health that modifies to the player*/
        Bool movable;                           /**< Indicates if the object can be moved*/
        Id dependency;                          /**< Indicates if the object depends on another and which one is it*/
        Id open;                                /**< Indicates if the object opens new zones in the map*/
};

/**
 * object_create allocates memory for a new object and
 * initializes its members
 */
Object *object_create(Id id) {
        Object *object = NULL;

        /*Error control*/
        if (id == NO_ID) {
                return NULL;
        }

        object = (Object *)malloc(sizeof(Object));

        /*Error control*/
        if (!object) {
                return NULL;
        }

        object->id = id;
        object->name[0] = '\0';
        object->description[0] = '\0';
        object->health = 0;
        object->movable = FALSE;
        object->dependency = NO_ID;
        object->open = NO_ID;

        return object;
}

Status object_destroy(Object *object) {
        if (!object) return ERROR;
        free(object);

        return OK;
}

Id object_get_id(const Object *object) {
        /*Error control*/
        if (!object) {
                return NO_ID;
        }
        return object->id;
}

Status object_set_name(Object *object, char *name) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        strcpy((object->name), name);
        return OK;
}

const char *object_get_name(const Object *object) {
        /*Error control*/
        if (!object) {
                return NULL;
        }

        return object->name;
}

Status object_set_description(Object *object, char *description) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        strcpy((object->description), description);
        return OK;
}

const char *object_get_description(const Object *object) {
        /*Error control*/
        if (!object) {
                return NULL;
        }

        return object->description;
}

Status object_set_health(Object *object, int health) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        object->health = health;
        return OK;
}

int object_get_health(const Object *object) {
        /*Error control*/
        if (!object) {
                return -1;
        }
        return object->health;
}

Status object_set_movable(Object *object, Bool movable) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        object->movable = movable;
        return OK;
}

Bool object_get_movable(const Object *object) {
        /*Error control*/
        if (!object) {
                return FALSE;
        }
        return object->movable;
}

Status object_set_dependency(Object *object, Id dependency) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        object->dependency = dependency;
        return OK;
}

Id object_get_dependency(const Object *object) {
        /*Error control*/
        if (!object) {
                return NO_ID;
        }
        return object->dependency;
}

Status object_set_open(Object *object, Id open) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        object->open = open;
        return OK;
}

Id object_get_open(const Object *object) {
        /*Error control*/
        if (!object) {
                return NO_ID;
        }
        return object->open;
}

Status object_print(const Object *object) {
        /*Error control*/
        if (!object) {
                return ERROR;
        }

        printf("The name of the object is: %s, and its id is %ld\n", object->name, object->id);
        fprintf(stdout, "The graphic description of the object is %s\n", object->description);
        printf("Its health is %i\n", object->health);
        printf("Is the object movable? : %s\n", object->movable ? "YES" : "NO");
        printf("The Id of the object it depends on is %ld", object->dependency);
        printf("The Id of the space it opens is %ld", object->open);

        return OK;
}
