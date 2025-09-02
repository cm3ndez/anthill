/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Carlos Méndez, Abraham Martín and Jorge Ochoa
 * @version 3.0
 * @date 28-03-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link.h"
#include "set.h"

/**
 * @def EMPTY_ROW
 * @brief Defines an empty row for gdesc
 */
#define EMPTY_ROW "               "
/**
 * @def EMPTY_GDESC_ROW
 * @brief Defines an empty row for gdesc
 */
#define EMPTY_GDESC_ROW "         "

/**
 * @brief _Space private struct
 * */

struct _Space {
        Id id;                                    /**< Id number of the space, it must be unique */
        char name[WORD_SIZE + 1];                 /**< Name of the space */
        Bool discovered;                          /**< Boolean to know if we discovered the space or not*/
        Set* objects;                             /**< Pointer to a set of the objects at the space */
        Set* characters;                          /**< Pointer to a set of the characters at the space */
        char gdesc[GDESC_LINES][LINE_LENGTH + 1]; /**< Graphical description of the space*/
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
        Space* newSpace = NULL;

        /* Error control */
        if (id == NO_ID) return NULL;

        newSpace = (Space*)malloc(sizeof(Space));

        if (newSpace == NULL) {
                return NULL;
        }

        /* Initialization of an empty space*/
        newSpace->id = id;
        newSpace->name[0] = '\0';
        newSpace->discovered = FALSE;
        newSpace->objects = set_create();
        if (!((newSpace->objects))) {
                space_destroy(newSpace);
                return NULL;
        }
        newSpace->characters = set_create();
        if (!((newSpace->characters))) {
                space_destroy(newSpace);
                return NULL;
        }
        return newSpace;
}

Status space_destroy(Space* space) {
        if (space) {
                if (space->objects) {
                        set_destroy(space->objects);
                }
                if (space->characters) {
                        set_destroy(space->characters);
                }
                free(space);
        }

        return OK;
}

Id space_get_id(const Space* space) {
        /* Error control */
        if (!space) {
                return NO_ID;
        }
        return space->id;
}

Status space_set_name(Space* space, char* name) {
        /* Error control */
        if ((!space) || (!name)) {
                return ERROR;
        }

        if (!strcpy(space->name, name)) {
                return ERROR;
        }
        return OK;
}

const char* space_get_name(const Space* space) {
        /* Error control */
        if (!space) {
                return NULL;
        }
        return space->name;
}

Status space_set_discovered(Space* space, Bool discovered) {
        /* Error control */
        if (!space) {
                return ERROR;
        }
        space->discovered = discovered;
        return OK;
}

Bool space_get_discovered(const Space* space) {
        /* Error control */
        if (!space) {
                return FALSE;
        }
        return space->discovered;
}

Status space_add_object(Space* space, Id id) {
        /* Error control */
        if (!space || id == NO_ID) {
                return ERROR;
        }
#ifdef DEBUG
        space_print(space);
#endif
        return set_add(space->objects, id);
}

Id space_del_object(Space* space, Id id) {
        /* Error control */
        if (!space || id == NO_ID) {
                return NO_ID;
        }
#ifdef DEBUG
        space_print(space);
#endif
        return set_del(space->objects, id);
}

Status space_add_character(Space* space, Id id) {
        /* Error control */
        if (!space || id == NO_ID) {
                return ERROR;
        }

#ifdef DEBUG
        space_print(space);
#endif
        return set_add(space->characters, id);
}

Id space_del_character(Space* space, Id id) {
        /* Error control */
        if (!space || id == NO_ID) {
                return NO_ID;
        }
#ifdef DEBUG
        space_print(space);
#endif
        return set_del(space->characters, id);
}

Status space_set_gdesc(Space* space, char gdesc[GDESC_LINES][LINE_LENGTH + 1]) {
        int i;
        if (!space || !gdesc) return ERROR;
        for (i = 0; i < GDESC_LINES; i++) strcpy(space->gdesc[i], gdesc[i]);

        return OK;
}

const char* space_get_gdesc(const Space* space, int row_num) {
        if (!space || (row_num < 0 && row_num > GDESC_LINES)) return EMPTY_ROW;
        if (space->discovered == FALSE)
                return EMPTY_GDESC_ROW;
        else
                return space->gdesc[row_num];
}

int space_get_num_objects(const Space* space) {
        if (!space) return 0;
        return set_get_nIds(space->objects);
}

int space_get_num_characters(const Space* space) {
        if (!space) return 0;
        return set_get_nIds(space->characters);
}

Bool space_has_object(const Space* space, Id id) {
        if (!space || id == NO_ID) {
                return FALSE;
        }
        return set_has(space->objects, id);
}

Bool space_has_character(const Space* space, Id id) {
        if (!space || id == NO_ID) {
                return FALSE;
        }
        return set_has(space->characters, id);
}

Status space_set_characters(Space* space, Id id) {
        if (!space) return ERROR;
#ifdef DEBUG
        printf("Space before adding a character\n");
        space_print(space);
#endif
        set_add(space->characters, id);
#ifdef DEBUG
        printf("Space after adding a character\n");
        space_print(space);
#endif
        return OK;
}

Id space_get_id_at_index(const Space* space, int index) {
        if (!space) return NO_ID;
        return set_get_id_at_index(space->objects, index);
}

Status space_print(const Space* space) {
        int i, j;

        /* Error Control */
        if (!space) {
                return ERROR;
        }

        /* 1. Print the id and the name of the space */
        fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

        fprintf(stdout, "Is the space discovered? : %s\n", space->discovered ? "YES" : "NO");

        /*Print the Objects in the space*/
        set_print(space->objects);

        /* 3. Print if there is an object in the space or not */
        if (space->objects) {
                printf("The space %d has the following objects:\n", (int)space->id);
                set_print(space->objects);
        }

        /* 4. Print if there is a character in the space or not */
        if (space->objects) {
                printf("The space %d has the following characters:\n", (int)space->id);
                set_print(space->characters);
        }

        /* 5. Prints the graphic description of the space*/
        fprintf(stdout, "Graphic description of the space: \n");
        for (i = 0; i < GDESC_LINES; i++) {
                for (j = 0; j < LINE_LENGTH; j++) {
                        fprintf(stdout, "%c", space->gdesc[i][j]);
                }
                fprintf(stdout, "\n");
        }

        printf("\n");
        return OK;
}
