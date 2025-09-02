/**
 * @brief Implements the functions to operate on a player
 *
 * @file player.c
 * @author Abraham Martín y Carlos Méndez
 * @version 2.0
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"

/**
 * @brief _Player private struct
 * */

struct _Player {
        Id id;                           /**< Unique id*/
        char name[WORD_SIZE + 1];        /**< Player's name*/
        Id location;                     /**< Player's location*/
        int health;                      /**< Player's health*/
        Inventory* backpack;             /**< Player's inventory for carrying objects*/
        char g_desc[P_GDESC_LENGTH + 1]; /**< Player's graphical description*/
        int damage;                      /**< Player's  damage when an attack succeeds*/
};

Player* player_create(Id id) {
        Player* newPlayer = NULL;

        /* Error control */
        if (id == NO_ID) return NULL;

        newPlayer = (Player*)malloc(sizeof(Player));
        if (newPlayer == NULL) {
                return NULL;
        }
        newPlayer->backpack = inventory_create();
        if (!newPlayer->backpack) {
                free(newPlayer);
                return NULL;
        }
        /* Initialization of an empty player*/
        newPlayer->id = id;
        newPlayer->location = NO_ID;
        sprintf(newPlayer->name, "%s", "Player");
        newPlayer->health = 0;
        newPlayer->damage = 1;
        return newPlayer;
}

Status player_destroy(Player* player) {
        if (player) inventory_destroy(player->backpack);
        free(player);

        return OK;
}

Id player_get_id(const Player* player) {
        /*Error control*/
        if (!player) {
                return NO_ID;
        }
        return player->id;
}

Status player_set_name(Player* player, char* name) {
        /*Error control*/
        if (!player || !name) {
                return ERROR;
        }

        if (!strcpy(player->name, name)) {
                return ERROR;
        }
        return OK;
}

const char* player_get_name(const Player* player) {
        /*Error control*/
        if (!player) {
                return NULL;
        }
        return player->name;
}

Status player_set_location(Player* player, Id id) {
        /*Error control*/
        if (!player || id == NO_ID) {
                return ERROR;
        }
        player->location = id;
        return OK;
}

Id player_get_location(const Player* player) {
        /*Error control*/
        if (!player) {
                return NO_ID;
        }
        return player->location;
}

Status player_add_object(Player* player, Id id) {
        /*Error control*/
        if (!player) {
                return ERROR;
        }
        return inventory_add_object(player->backpack, id);
}

Id player_del_object(Player* player, Id id) {
        /*Error control*/
        if (!player || id == NO_ID) {
                return NO_ID;
        }
        return inventory_del_object(player->backpack, id);
}

Id player_get_object_at_index(const Player* player, int index) {
        /*Error control*/
        if (!player || index == -1) {
                return NO_ID;
        }

        return inventory_get_object_id_at_index(player->backpack, index);
}

Status player_set_health(Player* player, int health) {
        /*Error control*/
        if (!player || health < 0) {
                return ERROR;
        }
        player->health = health;
        return OK;
}

int player_get_health(const Player* player) {
        /*Error control*/
        if (!player) {
                return NO_ID;
        }
        return player->health;
}

Status player_set_gdesc(Player* player, char* gdesc) {
        if (!player || !gdesc) return ERROR;
        sprintf(player->g_desc, "%6s", gdesc);
        return OK;
}

const char* player_get_gdesc(const Player* player) {
        if (!player) return " ";
        return player->g_desc;
        ;
}

Status player_set_backpack_size(Player* player, int size) {
        if (!player || size < 0) return ERROR;
        return inventory_set_max_objs(player->backpack, size);
}

int player_get_num_objects(const Player* player) {
        if (!player) return 0;
        return inventory_get_num_objects(player->backpack);
}

Bool player_has_object(const Player* player, Id object) {
        if (!player || object == NO_ID) {
                return FALSE;
        }

        return inventory_has_object(player->backpack, object);
}

Status player_set_damage(Player* player, int damage) {
        if (!player || damage < 0) {
                return ERROR;
        }

        player->damage = damage;

        return OK;
}

int player_get_damage(const Player* player) {
        if (!player) {
                return -1;
        }

        return player->damage;
}

Status player_print(const Player* player) {
        if (!player) {
                return ERROR;
        }
        fprintf(stdout,
                "The name of the player is: %s, its id is %d, its location is %d, its health is %d "
                "and his inventory is the following:\n",
                player->name, (int)player->id, (int)player->location, player->health);
        inventory_print(player->backpack);
        fprintf(stdout, "The graphic description of the player is %s\n", player->g_desc);

        return OK;
}
