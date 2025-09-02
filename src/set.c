/**
 * @brief It implements the set module
 *
 * @file set.c
 * @author Abraham Martín
 * @version 1.0
 * @date 21-02-2025
 * @copyright GNU Public License
 */

#include "set.h"

#include <stdio.h>

/**
 * @def MAX_IDS
 * @brief Defines the maximum number of ids
 */
#define MAX_IDS 50

/**
 * @brief _Set private struct
 * */
struct _Set {
        Id ids[MAX_IDS]; /**< Id array*/
        int n_ids;       /**< Number of ids in the array*/
};

Set* set_create(void) {
        Set* s = NULL;
        int i = 0;
        s = (Set*)malloc(sizeof(Set));
        /*Error control*/
        if (!s) {
                return NULL;
        }
        for (i = 0; i < MAX_IDS; i++) {
                s->ids[i] = NO_ID;
        }
        s->n_ids = 0;
        return s;
}

Status set_destroy(Set* s) {
        free(s);

        return OK;
}

int set_get_nIds(const Set* s) {
        /*Error control*/
        if (!s) {
                return -1;
        }

        return s->n_ids;
}

Status set_add(Set* s, Id id) {
        int i = 0;

        /*Error control*/
        if (!s || s->n_ids == MAX_IDS || id == NO_ID) {
                return ERROR;
        }
#ifdef DEBUG
        printf("Set before adding %d.\n", (int)id);
        set_print(s);
#endif
        for (i = 0; i < s->n_ids; i++) {
                if (id == s->ids[i]) {
#ifdef DEBUG
                        printf("The element belongs to the set already.\n");
#endif
                        return OK;
                }
        }
        s->ids[s->n_ids] = id;
        s->n_ids++;
#ifdef DEBUG
        printf("Set after adding %d.\n", (int)id);
        set_print(s);
#endif
        return OK;
}

Id set_del(Set* s, Id id) {
        int i = 0;
        /*Error control*/
        if (!s || id == NO_ID) {
                return NO_ID;
        }
#ifdef DEBUG
        printf("Set before deleting %d.\n", (int)id);
        set_print(s);
#endif

        for (i = 0; i < s->n_ids; i++) {
                if (s->ids[i] == id) {
                        s->ids[i] = s->ids[s->n_ids - 1];
                        s->ids[s->n_ids - 1] = NO_ID;
                        s->n_ids--;
#ifdef DEBUG
                        printf("Set after deleting %d.\n", (int)id);
                        set_print(s);
#endif
                        return id;
                }
        }
#ifdef DEBUG
        printf("The element %d doesn't belong to the set.\n", (int)id);
#endif

        return NO_ID;
}

Bool set_has(const Set* s, Id id) {
        int i;
        if (!s || id == NO_ID) {
                return FALSE;
        }
        for (i = 0; i < s->n_ids; i++) {
                if (s->ids[i] == id) {
                        return TRUE;
                }
        }
        return FALSE;
}

Id set_get_id_at_index(const Set* set, int index) {
        if (!set || index < 0 || index > set->n_ids) return NO_ID;
        return set->ids[index];
}

Status set_print(const Set* s) {
        int i = 0;

        /*Error control*/
        if (!s) {
                return ERROR;
        }

        printf("There are %d ids in the set. The list is the following: \n", s->n_ids);
        for (i = 0; i < s->n_ids; i++) {
                printf("%ld ", s->ids[i]);
        }
        printf("\n");
        return OK;
}
