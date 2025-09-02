/**
 * @brief Defines the functions to operate on a player
 *
 * @file player.h
 * @author Abraham Martin y Carlos Méndez
 * @version 2.0
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/**
 * @def P_GDESC_LENGTH
 * @brief Defines the length of the player's g_desc
 */
#define P_GDESC_LENGTH 6

/**
 * @brief Player
 *
 * This struct stores all the information related to a Player
 */
typedef struct _Player Player;

/**
 * @brief Allocates memory for a new player and sets every field to 0 or NULL except the id
 * @author Abraham Martín
 *
 * @param id Id of the player being created
 * @return Pointer to the player created, or NULL if there was an ERROR
 */
Player* player_create(Id id);

/**
 * @brief Frees up the memory of the player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return OK if it could destroy the player, and ERROR otherwise
 */
Status player_destroy(Player* player);

/**
 * @brief Gives back the id of a given player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return The player´s id or NO_ID if there was an error
 */
Id player_get_id(const Player* player);

/**
 * @brief Asigns the name field of the player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param name String of the name
 * @return OK if it could set it or ERROR otherwise
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Retrieves the name of a given player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return The player´s name or NULL if there was an error
 */
const char* player_get_name(const Player* player);

/**
 * @brief Establishes the player´s location
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param id Id of the location
 * @return OK if it could set it and ERROR otherwise
 */
Status player_set_location(Player* player, Id id);

/**
 * @brief Retrieves the location of a given player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return The player´s location or NO_ID if there was an error
 */
Id player_get_location(const Player* player);

/**
 * @brief Adds an object to the backpack
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param id Id of the object
 * @return OK if it could set it and ERROR otherwise
 */
Status player_add_object(Player* player, Id id);

/**
 * @brief Retrieves an object of the backpack of a given player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param id Id of the object to delete
 * @return The deleted object id or NO_ID if there was an error
 */
Id player_del_object(Player* player, Id id);

/**
 * @brief Retrieves objects ids from the backpack of a given player using indices only for displaying purposes
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param index Ordered index of the object to retrieve
 * @return The id of the object at the provided index
 */

Id player_get_object_at_index(const Player* player, int index);

/**
 * @brief Gives a value to the player's health field
 * @author Carlos Méndez
 *
 * @param player Pointer to player
 * @param health int storing the value of the new player´s health
 * @return OK if it could set it correctly or ERROR otherwise
 */
Status player_set_health(Player* player, int health);

/**
 * @brief Retrieves the value of the playérs health field
 * @author Carlos Méndez
 *
 * @param player Pointer to player
 * @return Int the player's health or 0 if there was an error
 */
int player_get_health(const Player* player);

/**
 * @brief  Sets the gdesc of the players
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param gdesc String with the gdesc of the player
 * @return OK if the player's gdesc is set or ERROR otherwise
 */
Status player_set_gdesc(Player* player, char* gdesc);

/**
 * @brief  Gets the gdesc of the player
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return The string representing the gdesc of the player or " " otherwise
 */
const char* player_get_gdesc(const Player* player);

/**
 * @brief  Sets the size of the player's inventory
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @param size Max number of objects of the inventory
 * @return OK if everthing went well or ERROR otherwise
 */
Status player_set_backpack_size(Player* player, int size);

/**
 * @brief  Gets the number of objects currently in the backpack
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return The number of objects currently in the backpack
 */
int player_get_num_objects(const Player* player);

/**
 * @brief It states if a player has an object
 * @author Carlos Méndez
 *
 * @param player Pointer to a player
 * @param object ID of the object to be checked
 * @return The TRUE if the player has the object or ERROR otherwise
 */
Bool player_has_object(const Player* player, Id object);

/**
 * @brief It sets a new value for the player's damage field
 * @author Carlos Méndez
 *
 * @param player Pointer to a player
 * @param damage The new damage for the given player
 * @return OK if it could be set or ERROR otherwise
 */
Status player_set_damage(Player* player, int damage);

/**
 * @brief It get the value of the player's damage field
 * @author Carlos Méndez
 *
 * @param player Pointer to a player
 * @return The damage or -1 if something went wrong
 */
int player_get_damage(const Player* player);

/**
 * @brief Outputs the player´s attributes
 * @author Abraham Martín
 *
 * @param player Pointer to player
 * @return OK if it could print it or ERROR otherwise
 */
Status player_print(const Player* player);

#endif
