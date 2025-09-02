/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author Jorge Ochoa
 * @version 0
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief _Link private struct
 * */

struct _Link {
        char name[WORD_SIZE]; /**<Link's name */
        Id id;                /**< Link's unique id*/
        Id origin;            /**< Link's origin*/
        Id destination;       /**< Link's destination */
        Direction direction;  /**< Link's direction*/
        Bool open;            /**< Link's open or closed status*/
};

Link *link_create(Id id) {
        Link *NewLink = NULL;

        if (id == NO_ID) {
                return NULL;
        }

        NewLink = (Link *)malloc(sizeof(Link));
        if (NewLink == NULL) {
                return NULL;
        }

        NewLink->id = id;
        NewLink->name[0] = '\0';
        NewLink->origin = NO_ID;
        NewLink->destination = NO_ID;
        NewLink->direction = 0;
        NewLink->open = FALSE;

        return NewLink;
}

Status link_destroy(Link *link) {
        if (link == NULL) {
                return ERROR;
        }

        free(link);
        return OK;
}

Status link_set_id(Link *link, Id id) {
        if (link == NULL || id == NO_ID) {
                return ERROR;
        }

        link->id = id;
        return OK;
}

Id link_get_id(const Link *link) {
        if (link == NULL) {
                return NO_ID;
        }

        return link->id;
}

Status link_set_name(Link *link, char *name) {
        if (!link || !name) {
                return ERROR;
        }

        strcpy(link->name, name);
        return OK;
}

const char *link_get_name(const Link *link) {
        if (link == NULL) {
                return NULL;
        }

        return link->name;
}

Status link_set_origin(Link *link, Id id_origin) {
        if (link == NULL || id_origin == NO_ID) {
                return ERROR;
        }

        link->origin = id_origin;
        return OK;
}

Id link_get_origin(const Link *link) {
        if (link == NULL) {
                return NO_ID;
        }

        return link->origin;
}

Status link_set_destination(Link *link, Id id_destination) {
        if (link == NULL || id_destination == NO_ID) {
                return ERROR;
        }

        link->destination = id_destination;
        return OK;
}

Id link_get_destination(const Link *link) {
        if (link == NULL) {
                return NO_ID;
        }

        return link->destination;
}

Status link_set_direction(Link *link, Direction NewDirection) {
        if (link == NULL) {
                return ERROR;
        }

        link->direction = NewDirection;
        return OK;
}

Direction link_get_direction(const Link *link) {
        if (link == NULL) {
                return NO_DIRECTION;
        }

        return link->direction;
}

Status link_set_open(Link *link, Bool open) {
        if (link == NULL) {
                return ERROR;
        }

        link->open = open;
        return OK;
}

Bool link_get_open(const Link *link) {
        if (link == NULL) {
                return FALSE;
        }

        return link->open;
}

Status link_print(const Link *link) {
        if (!link) {
                return ERROR;
        }

        fprintf(stdout,
                "The link id is %ld and its name is %s.\n The origin is %ld, the destination %ld and the direction is %c.\n Is "
                "the link open?: %s\n",
                link->id, link->name, link->origin, link->destination, link->direction, link->open ? "YES" : "NO");

        return OK;
}
