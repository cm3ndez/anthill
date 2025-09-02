/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Abraham Martín, Carlos Méndez and Jorge Ochoa
 * @version 2.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "command.h"
#include "link.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @def MAX_SPACES
 * @brief Defines the maximum number of spaces in the game
 */
#define MAX_SPACES 50

/**
 * @def MAX_OBJECTS
 * @brief Defines the maximum number of objects in the game
 */
#define MAX_OBJECTS 50

/**
 * @def MAX_CHARACTERS
 * @brief Defines the maximum number of characterss in the game
 */
#define MAX_CHARACTERS 50

/**
 * @def MAX_PLAYERS
 * @brief Defines the size ofthe player's array
 */
#define MAX_PLAYERS 8

/**
 * @def MAX_LINKS
 * @brief Defines the maximum number of links in the game
 */
#define MAX_LINKS 200

/**
 * @brief Game
 *
 * This struct stores all the information related to a game.
 */
typedef struct _Game Game;

/**
 * @brief Initializes all the fields of the game to 0
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game being created
 * @return OK if everyting went well and ERROR otherwise
 */
Status game_create(Game** game);

/**
 * @brief Creates the game and spaces from the file description
 * @author Abraham Martín
 *
 * @param game Pointer to pointer to game being created
 * @param filename with the name of the file
 * @return OK if everyting went well and ERROR otherwise
 */
Status game_create_from_file(Game** game, char* filename);

/**
 * @brief Frees up the memory allocated for the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being destroyed
 * @return OK if it could free the memory and ERROR otherwise
 */
Status game_destroy(Game* game);

/**
 * @brief Gets the number of players in the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @return The number of players or -1 in case of error
 */
int game_get_n_players(Game* game);

/**
 * @brief Returns the player with that id
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game being played
 * @param id id of the player
 * @return The player or NULL in case of error
 */
Player* game_get_player_from_id(const Game* game, Id id);

/**
 * @brief Returns the player in the given position
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @param index Position of the player in the array
 * @return The player or NULL in case of error
 */
Player* game_get_player_from_index(const Game* game, int index);

/**
 * @brief Removes the object from the player
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @param object_id ID of the object
 * @return The object ID extracted or NO_ID if failed
 */
Id game_extract_object_from_player(Game* game, Id object_id);

/**
 * @brief Assigns an object to the player
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @param object_id ID of the object
 * @return OK if successful, ERROR otherwise
 */
Status game_put_object_on_player(Game* game, Id object_id);

/**
 * @brief Handles player attack event
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return OK if successful, ERROR otherwise
 */
Status game_player_gets_attacked(Game* game);

/**
 * @brief Handles player attack from the use of an object
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param new_health New health of the player
 * @return OK if successful, ERROR otherwise
 */
Status game_player_gets_attacked_by_use(Game* game, int new_health);

/**
 * @brief Asigns a location to the player
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @param id Player's location id
 * @return OK if everyting went well and ERROR otherwise
 */
Status game_set_player_location(Game* game, Id id);

/**
 * @brief Gives the player´s location
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @return id The player´s id location or NO_ID if something went wrong
 */
Id game_get_player_location(const Game* game);

/**
 * @brief Sets the player's damage
 * @author Carlos Méndez
 *
 * @param player Pointer to the game being played
 * @param damage The new damage that the player will deal
 * @return id The player´s id location or NO_ID if something went wrong
 */
Status game_set_player_damage(Player* player, int damage);

/**
 * @brief Gives the player currently playing
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @return reference to the current player playing or NULL if there was an error
 */
Player* game_get_current_player(const Game* game);

/**
 * @brief Gives the player that just played
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @return reference to the last player playing or NULL if there was an error
 */
Player* game_get_last_player(const Game* game);

/**
 * @brief Adds a player to the game
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @param player Pointer to the player to be added
 * @return OK if successful, ERROR otherwise
 */
Status game_add_player(Game* game, Player* player);

/**
 * @brief Gets current player health
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @return Health of the player, or -1 if something ocurrs
 */
int game_get_player_health(const Game* game);

/**
 * @brief Sets/Modify given player's health
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game.
 * @param new_health New health of the player
 * @param player Pointer to the player to be affected
 * @return OK if successful, ERROR otherwise
 */
Status game_set_player_new_health(Game* game, int new_health, Player* player);

/**
 * @brief Gets current player name
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @return name of the player, or NULL if something ocurrs
 */
const char* game_get_player_name(const Game* game);

/**
 * @brief Retrieves if the last player has won the combat encounter
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return TRUE if the player won, FALSE otherwise
 */
Bool game_get_last_player_won_combat(const Game* game);

/**
 * @brief Updates if the last player has won the combat encounter
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param won The result of the encounter
 * @return OK if it could be set, or ERROR otherwise
 */
Status game_set_last_player_won_combat(Game* game, Bool won);

/**
 * @brief It states if a player has an object
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param object ID of the object to be checked
 * @return The TRUE if the player has the object or ERROR otherwise
 */
Bool game_player_has_object(const Game* game, Id object);

/**
 * @brief Returns the number of objects in the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return The number of objects or -1 in case of error
 */
int game_get_n_objects(Game* game);

/**
 * @brief It retrieves an object given its position in the array
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param index Position in the array of the object
 * @return The object or NULL in case of error
 */
Object* game_get_object_from_index(Game* game, int index);

/**
 * @brief Retrieves an object given its ID
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param id Object ID
 * @return Pointer to the object or NULL there was an error
 */
Object* game_get_object_from_id(const Game* game, Id id);

/**
 * @brief Adds an object to the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param object Pointer to the object to be added
 * @return OK if successful, ERROR otherwise
 */
Status game_add_object(Game* game, Object* object);

/**
 * @brief Retrieves the location of an object given its ID
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param id Object ID
 * @return ID of the object's location or NO_ID if not found
 */
Id game_get_object_location(const Game* game, Id id);

/**
 * @brief Establishes the location of an object
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param object_id Object ID
 * @param space_id Space ID where the object will be placed
 * @return OK if successful, ERROR otherwise
 */
Status game_set_object_location(Game* game, Id object_id, Id space_id);

/**
 * @brief Retrieves the location of an object by its name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param name Name of the object
 * @return ID of the object's location or NO_ID if not found
 */
Id game_get_object_location_from_name(const Game* game, char* name);

/**
 * @brief Retrieves the ID of an object by its name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param name Name of the object
 * @return ID of the object or NO_ID if not found
 */
Id game_get_object_id_from_name(const Game* game, const char* name);

/**
 * @brief Retrieves the health of an object by its name
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param name Name of the object
 * @return Health of the object or -1 if not found
 */
int game_get_object_health_from_name(const Game* game, const char* name);

/**
 * @brief Deletes an object from the game
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param name Name of the object
 * @return OK if it is destroyed, ERROR something ocurrs
 */
Status game_object_destroy_from_name(Game* game, char* name);

/**
 * @brief Retrieves the description of an object by its name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param name Name of the object
 * @return Description of the object or NULL if not found
 */
const char* game_get_description_of_current_object(const Game* game, const char* name);

/**
 * @brief Retrieves the open of an object by its name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param object_name Name of the object
 * @return If of the open field or NO_ID if not found
 */
Id game_get_object_open_from_name(const Game* game, char* object_name);

/**
 * @brief Retrieves the number of characters in the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return The number of characters or -1 in case of error
 */
int game_get_n_characters(const Game* game);

/**
 * @brief Retrieves a character given its position in the array
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param index Position of the character in the array
 * @return The character or NULL in case of error
 */
Character* game_get_character_from_index(const Game* game, int index);

/**
 * @brief Retrieves a character given its id
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param character_id Id of the character to be found
 * @return The character or NULL in case of error
 */
Character* game_get_character_from_id(const Game* game, Id character_id);

/**
 * @brief Sets the new the location of a character
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param loc The location to which the character is moved
 * @param character_id Character ID
 * @return OK if the location could be set or ERROR otherwise
 */
Status game_set_character_location(Game* game, Id loc, Id character_id);

/**
 * @brief Retrieves the location of a character
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param character_id Character ID
 * @return ID of the character's location or NO_ID if not found
 */
Id game_get_character_location(const Game* game, Id character_id);

/**
 * @brief Returns the number of characters recruited by the currently active player
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return the number of characters following or -1 in case of error
 */
int game_get_n_characters_following_current_player(const Game* game);

/**
 * @brief Returns an array of Ids of all the characters recruited by the currently active player
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return The array with the Ids or NULL if there was an error
 */
Id* game_get_characters_following_current_player(const Game* game);

/**
 * @brief Handles character attack event
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param character_id Id of the character being attacked
 * @return OK if successful, ERROR otherwise
 */
Status game_character_gets_attacked(Game* game, Id character_id);

/**
 * @brief Handles character attack from object when we use the command use
 * @author JOrge Ochoa
 *
 * @param game Pointer to the game
 * @param new_health New health of the character
 * @param character_name Name of the character being afected by use
 * @return OK if successful, ERROR otherwise
 */
Status game_character_gets_attacked_by_use(Game* game, int new_health, char* character_name);

/**
 * @brief Adds a character to the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param character Pointer to the character to be added
 * @return OK if successful, ERROR otherwise
 */
Status game_add_character(Game* game, Character* character);

/**
 * @brief Destroys a character from the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param character Pointer to the character to be removed
 * @return OK if successful, ERROR otherwise
 */
Status game_del_character(Game* game, Character* character);

/**
 * @brief Checks if a character is alive
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param character_id The id of the character to be checked
 * @return TRUE if alive, FALSE otherwise
 */
Bool game_get_character_is_alive(const Game* game, Id character_id);

/**
 * @brief Retrieves the enemy character at a given space
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param location the space
 * @return The enemy or NULL if there was an error
 */
Character* game_get_enemy_character_at_space(const Game* game, Id location);

/**
 * @brief Gets the index of the character with his name
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param name Name of the character
 * @return Index, -1 otherwise
 */
int game_get_character_index_from_name(const Game* game, char* name);

/**
 * @brief Sets new health of the character
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param new_health New health of the character
 * @param name Name of the character
 * @return TRUE, FALSE otherwise
 */
Status game_set_character_new_health(const Game* game, int new_health, char* name);

/**
 * @brief Gets character health from name
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param name Name of the character
 * @return Health, -1 otherwise
 */
int game_get_character_health_from_name(const Game* game, char* name);

/**
 * @brief Gets character from name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param name Name of the character
 * @return The character or NULL in case of error
 */
Character* game_get_character_from_name(Game* game, char* name);

/**
 * @brief Returns the number of spaces in the game
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @return The number of spaces or -1 in case of error
 */
int game_get_n_spaces(Game* game);

/**
 * @brief Returns a space given its position in the array
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param index The position of the space
 * @return The space or NULL in case of error
 */
Space* game_get_space_from_index(Game* game, int index);

/**
 * @brief Retrieves the list of objects at a given space
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @param space_id ID of the space
 * @param list Buffer to store the object list
 */
void game_get_object_list_at_space(const Game* game, Id space_id, char* list);

/**
 * @brief Gives the space given its Id
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param id the space´s Id
 * @return Pointer to the space, or NULL if there was a problem
 */
Space* game_get_space(const Game* game, Id id);

/**
 * @brief Add a new space to the game
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 * @param space Pointer to the space to be added
 * @return OK if everyting went well and ERROR otherwise
 */
Status game_add_space(Game* game, Space* space);

/**
 * @brief Gives back the last command entered
 * @author Abraham Martín
 *
 * @param game A Pointer to the game being played
 * @return Pointer to the last command introduced by the user
 */
Command* game_get_last_command(const Game* game);

/**
 * @brief Establishes the last command
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 * @param command Pointer to the command
 * @return OK if everyting went well and ERROR otherwise
 */
Status game_set_last_command(Game* game, Command* command);

/**
 * @brief Checks if the game ended
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @return TRUE if the game is finished and FALSE otherwise
 */
Bool game_get_finished(const Game* game);

/**
 * @brief Establishes the new value of its field 'finished'
 * @author Carlos Méndez
 *
 * @param game A Pointer to the game being played
 * @param finished which forces the game to finish
 * @return OK if everyting went well and ERROR otherwise
 */
Status game_set_finished(Game* game, Bool finished);

/**
 * @brief Returns the number of links in the game
 * @author Carlos Méndez
 *
 * @param game A Pointer to the game being played
 * @return The number of links or -1 in case of error
 */
int game_get_n_links(Game* game);

/**
 * @brief Retrieves a link given its position in the array
 * @author Carlos Méndez
 *
 * @param game A Pointer to the game being played
 * @param index Position of the link
 * @return The link or NULL in case of error
 */
Link* game_get_link_from_index(Game* game, int index);

/**
 * @brief Checks if a space link in a game is open in a given direction
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param current_space_id ID of the space
 * @param direction Direction to check the link
 * @return TRUE if the connection is open, FALSE otherwise
 */
Bool game_connection_is_open(const Game* game, Id current_space_id, Direction direction);

/**
 * @brief Retrieves the ID of the space connected in a given direction
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param current_space_id ID of the space to check
 * @param direction Direction of the connection
 * @return ID of the connected space if found, NO_ID otherwise
 */
Id game_get_connection(const Game* game, Id current_space_id, Direction direction);

/**
 * @brief Adds a link to the game
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @param link Pointer to the link to be added
 * @return OK if successful, ERROR otherwise
 */
Status game_add_link(Game* game, Link* link);

/**
 * @brief Retrieves a link's Id given its origin space and its direction
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param space_id the origin space's id
 * @param direction the direction of the link to be found
 * @return Id of the link or NO_ID if there was an error
 */
Id game_get_link(const Game* game, Id space_id, Direction direction);

/**
 * @brief Retrieves a link given its name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param name the link's name
 * @return The Link or NULL if there was an error
 */
Link* game_get_link_from_name(const Game* game, char* name);

/**
 * @brief Retrieves all the information about the game player, characters, their messages, objects
 * and all their locations
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param info Buffer to store the game information
 */
void game_get_info(const Game* game, char* info);

/**
 * @brief Passes the turn to the next alive player
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
void game_pass_turn(Game* game);

/**
 * @brief Retrieves the current player's gdesc
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
const char* game_get_current_player_gdesc(const Game* game);

/**
 * @brief Retrieves the current turn
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 * @return The integer representing the current turn
 */
int game_get_current_turn(const Game* game);

/**
 * @brief Updates log-file if requested with the result of the last command
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 * @param file name of an open file descriptor
 */

void game_write_recent_log(const Game* game, const char* file);

/**
 * @brief Outputs the information of the game´s fields
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
void game_print(const Game* game);

/**
 * @brief Builds a string representation of all the players at same space in 2 rows
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 * @param id The space id
 * @param first_row An input/output string corresponding with the first row
 * @param second_row An input/output string coreesponding with the second row
 */
void game_get_players_row_at_space(const Game* game, Id id, char* first_row, char* second_row);

/**
 * @brief Sets the mode of the game
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game being played
 * @param deterministic 1 if yes or 0 if not
 * @return OK if successful, ERROR otherwise
 */
Status game_set_deterministic_mode(Game* game, int deterministic);

/**
 * @brief Sets the turn
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game being played
 * @param turn number of turn
 * @return OK if successful, ERROR otherwise
 */
Status game_set_turn(Game* game, int turn);

/**
 * @brief Gets current turn
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game being played
 * @return The number of the turn
 */
int game_get_turn(Game* game);

/**
 * @brief Saves a game
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game being played
 * @param filename Filename were we save
 * @return OK if is correct or ERROR otherwise
 */
Status game_game_management_save(Game* game, char* filename);

/**
 * @brief Loads a game
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game
 * @param filename Filename that we load
 * @return OK if is correct or ERROR otherwise
 */
Status game_game_management_load(Game* game, char* filename);

#endif
