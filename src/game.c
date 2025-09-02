/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Abraham Martín, Carlos Méndez and Jorge Ochoa
 * @version 3.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "game_management.h"

/**
 * @def MAX_SPACE_LINKS
 * @brief Defines the size of the link's array
 */
#define MAX_SPACE_LINKS 4

/**
 * @def MAX_ROW_PLAYERS
 * @brief Defines the max number of player gdesc in each row to represent it in graphic_engine.
 */
#define MAX_ROW_PLAYERS 4

/**
 * @def INVALID_INDEX
 * @brief Defines a macro for an invalid index of any array
 */
#define INVALID_INDEX -1

/**
 * @def DUMMY_SIZE
 * @brief Defines the length of general purpose buffer
 */
#define DUMMY_SIZE 800

/**
 * @def EMPTY
 * @brief Defines the strin g with just 1 space
 */
#define EMPTY " \0"

/**
 * @def LIST_LENGTH
 * @brief Defines the length of the object list
 */
#define LIST_LENGTH 50

/**
 * @def CUT_INDEX
 * @brief Defines the index to cut manually the string
 */
#define CUT_INDEX 4

/**
 * @def ARG_SIZE
 * @brief Defines de lenght of the temporary buffer arg_buff
 */
#define ARG_SIZE 100

/**
 * @def MAX_BUFFER1
 * @brief Defines the size of a general purpose buffer1
 */
#define MAX_BUFFER1 17

/**
 * @def MAX_BUFFER2
 * @brief Defines the size of a general purpose buffer2
 */
#define MAX_BUFFER2 6

/**
 * @brief _Game private struct
 * */

struct _Game {
        Player* players[MAX_PLAYERS];          /**< Pointer to a player*/
        int player_indices[MAX_PLAYERS];       /**< Array of player indices*/
        int num_alive_players;                 /**< NUmber of alive players*/
        int n_players;                         /**< Number of players*/
        int turn;                              /**< Current player's turn*/
        Object* objects[MAX_OBJECTS];          /**< Object array*/
        int n_objects;                         /**< Number of objects*/
        Character* characters[MAX_CHARACTERS]; /**< Characters array*/
        int n_characters;                      /**< Number of characters*/
        Space* spaces[MAX_SPACES];             /**< Spaces array*/
        int n_spaces;                          /**< Number of spaces*/
        Command* last_cmd;                     /**< Pointer to a command*/
        Bool finished;                         /**< Bool representing if the game has ended*/
        Link* links[MAX_LINKS];                /**< Links array*/
        int n_links;                           /**< Number of links*/
        int deterministic;                     /**< 1 if yes, 0 if not*/
        Bool combat_succeds;                   /**< 1 if the players has won, 0 if not*/
};

/**
   Private functions
*/

/**
 * @brief Retrieves the index of a player by its ID
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @param id Player's ID
 * @return Index of the player or -1 if not found
 */
int game_get_player_index_from_id(const Game* game, Id id);
/**
 * @brief Gets the space ID at a given position
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param position Index position in the space array
 * @return Id of the space or NO_ID if there was an error
 */
Id game_get_space_id_at(const Game* game, int position);

/**
 * @brief Retrieves the message of the current space
 * @author Abraham Martín
 *
 * @param game Pointer to the game
 * @return String with the space message
 */
const char* game_get_message_of_current_space(const Game* game);

/**
 * @brief Modifies the name parameter to the name of the object corresponding to the id given
 * @author Carlos Méndez
 *
 * @param game Pointer to game
 * @param id The id of the object
 * @param name string that, when leaving the function stores the name of the object
 */
void game_get_object_name_by_id(const Game* game, Id id, char* name);

/**
 * @brief Retrieves the index of an object by its ID
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param id Object ID
 * @return Index of the object or -1 if not found
 */
int game_get_object_index_from_id(const Game* game, Id id);

/**
 * @brief Retrieves the index of an object by its name
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param name Name of the object
 * @return Index of the object or -1 if not found
 */
int game_get_object_index_from_name(const Game* game, const char* name);

/**
 * @brief Retrieves the index of a character by its ID
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param id Character ID
 * @return Index of the character or -1 if not found
 */
int game_get_character_index_from_id(const Game* game, Id id);

/**
 * @brief Retrieves the index of a link by its ID
 * @author Carlos Méndez
 *
 * @param game Pointer to the game
 * @param id Link ID
 * @return Index of the link or -1 if not found
 */
int game_get_link_index_from_id(const Game* game, Id id);

/**
 * @brief Gets an array of IDs of the links connected to a space
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game
 * @param space_id ID of the space
 * @param direction Direction to obtain its space_id
 * @return Index of a link in the link's array or INVALID_INDEX otherwise
 */
int game_get_link_index_from_orig_direct(const Game* game, Id space_id, Direction direction);

/**
 * @brief Moves the alive players one place to the left in the array
 * @author Abraham Martín
 *
 * @param game Pointer to pointer to the game
 */
void game_exclude_player(Game* game);

/**
 *   Game interface implementation
 */

/*Manejo de Games*/
Status game_create(Game** game) {
        int i = 0;

        /*Error control*/
        if (!game) {
                return ERROR;
        }

        *game = (Game*)malloc(sizeof(Game));
        if (!(*game)) {
                return ERROR;
        }
        /*Create spaces*/
        for (i = 0; i < MAX_SPACES; i++) {
                (*game)->spaces[i] = NULL;
        }
        (*game)->n_spaces = 0;

        /*nitialize player's array and other related fields*/
        for (i = 0; i < MAX_PLAYERS; i++) {
                (*game)->players[i] = NULL;
                (*game)->player_indices[i] = i;
        }
        (*game)->n_players = 0;
        (*game)->num_alive_players = 0;
        (*game)->turn = 0;
        /*Create objects*/
        for (i = 0; i < MAX_OBJECTS; i++) {
                (*game)->objects[i] = NULL;
        }
        (*game)->n_objects = 0;

        /*Create links*/
        for (i = 0; i < MAX_LINKS; i++) {
                (*game)->links[i] = NULL;
        }
        (*game)->n_links = 0;

        /*Create command*/
        (*game)->last_cmd = command_create();
        for (i = 0; i < MAX_CHARACTERS; i++) {
                (*game)->characters[i] = NULL;
        }
        (*game)->n_characters = 0;
        (*game)->finished = FALSE;

        return OK;
}

Status game_create_from_file(Game** game, char* filename) {
        FILE* file = NULL;
        /*Error control*/
        if (!game || !filename) {
                return ERROR;
        }

        if (game_create(game) == ERROR) {
                return ERROR;
        }

        file = fopen(filename, "r");
        if (!file) {
                return ERROR;
        }

        if (game_management_load_spaces(game, filename) == ERROR) {
                fclose(file);
                return ERROR;
        }
        fseek(file, 0L, SEEK_SET);

        if (game_management_load_objects(game, filename) == ERROR) {
                fclose(file);
                return ERROR;
        }
        fseek(file, 0L, SEEK_SET);

        if (game_management_load_characters(game, filename) == ERROR) {
                fclose(file);
                return ERROR;
        }
        fseek(file, 0L, SEEK_SET);

        if (game_management_load_links(game, filename) == ERROR) {
                fclose(file);
                return ERROR;
        }
        fseek(file, 0L, SEEK_SET);

        if (game_management_load_players(game, filename) == ERROR) {
                fclose(file);
                return ERROR;
        }

        fclose(file);
        return OK;
}

Status game_destroy(Game* game) {
        int i = 0;
        if (game) {
                if (game->n_spaces > 0) {
                        for (i = 0; i < game->n_spaces; i++) {
                                space_destroy((game->spaces)[i]);
                                (game->spaces)[i] = NULL;
                        }
                }
                command_destroy(game->last_cmd);
                game->last_cmd = NULL;
                if (game->n_players > 0) {
                        for (i = 0; i < game->n_players; i++) {
                                player_destroy(game->players[i]);
                                game->players[i] = NULL;
                        }
                }
                if (game->n_objects > 0) {
                        for (i = 0; i < game->n_objects; i++) {
                                object_destroy((game->objects)[i]);
                                (game->objects)[i] = NULL;
                        }
                }
                if (game->n_characters > 0) {
                        for (i = 0; i < game->n_characters; i++) {
                                character_destroy(game->characters[i]);
                                (game->characters)[i] = NULL;
                        }
                }
                if (game->n_links > 0) {
                        for (i = 0; i < game->n_links; i++) {
                                link_destroy(game->links[i]);
                                (game->links)[i] = NULL;
                        }
                }

                free(game);
        }

        return OK;
}

/*-----------------------------Manejo de Players-----------------------------*/
int game_get_n_players(Game* game) {
        if (!game) {
                return -1;
        }

        return game->n_players;
}

Player* game_get_player_from_id(const Game* game, Id id) {
        int index = 0;

        if (!game || id != NO_ID) {
                return NULL;
        }
        index = game_get_player_index_from_id(game, id);
        return game_get_player_from_index(game, index);
}

Player* game_get_player_from_index(const Game* game, int index) {
        if (!game || index < 0) {
                return NULL;
        }

        return game->players[index];
}

Id game_extract_object_from_player(Game* game, Id object_id) {
        Id object_aux = NO_ID;
        if (!game || object_id == NO_ID) return NO_ID;
        object_aux = player_del_object(game->players[game->turn], object_id);
        if (object_aux == NO_ID) return NO_ID;
        return object_aux;
        ;
}

Status game_put_object_on_player(Game* game, Id object_id) {
        if (!game || object_id == NO_ID) {
                return ERROR;
        }
        return player_add_object(game->players[game->turn], object_id);
}

Status game_player_gets_attacked(Game* game) {
        int health;
        int character_health;
        int number;
        Id* characters_following = NULL;
        int n_chararcters = 0;
        int index_character_attacked = 0;
        Player* player_attacked = NULL;
        Character* character_attacked = NULL;

        if (!game) return ERROR;

        n_chararcters = game_get_n_characters_following_current_player(game);

        player_attacked = game_get_current_player((const Game*)game);
        if (!player_attacked) {
                return ERROR;
        }

        if (n_chararcters == 0) {
                number = 0;
        } else {
                number = rand() % n_chararcters + 1;
        }

        if (number == 0) {
                health = player_get_health(player_attacked);
                player_set_health(player_attacked, --health);
                if (health == 0) {
                        game_exclude_player(game);
                        if (game->num_alive_players == 0) game_set_finished(game, TRUE);
                } else {
                        game_pass_turn(game);
                }
        } else {
                characters_following = game_get_characters_following_current_player((const Game*)game);
                index_character_attacked = number;

                character_attacked =
                    game_get_character_from_id((const Game*)game, characters_following[index_character_attacked - 1]);

                if (!character_attacked) {
                        return ERROR;
                }

                character_health = character_get_health(character_attacked);
                character_set_health(character_attacked, --character_health);

                if (character_health == 0) {
                        game_del_character(game, character_attacked);
                } else {
                        game_pass_turn(game);
                }
        }

        return OK;
}

Status game_player_gets_attacked_by_use(Game* game, int new_health) {
        if (!game) return ERROR;
        player_set_health(game->players[game->player_indices[game->turn]], new_health);
        if (new_health <= 0) {
                game_exclude_player(game);
                if (game->num_alive_players == 0) game_set_finished(game, TRUE);
        } else {
                game_pass_turn(game);
        }
        return OK;
}

Status game_set_player_location(Game* game, Id id) {
        /*Error control*/
        if (!game) {
                return ERROR;
        }

        if (id == NO_ID) {
                return ERROR;
        }

        return player_set_location(game->players[game->turn], id);
}

Id game_get_player_location(const Game* game) {
        /*Error control*/
        if (!game) {
                return NO_ID;
        }

        return player_get_location(game->players[game->turn]);
}

Status game_set_player_damage(Player* player, int damage) {
        if (!player || damage < 0) {
                return ERROR;
        }

        return player_set_damage(player, damage);
}

Player* game_get_current_player(const Game* game) {
        /*Error control*/
        if (!game) {
                return NULL;
        }

        return game->players[game->turn];
}

Player* game_get_last_player(const Game* game) {
        Player* last_player = NULL;
        int turn;

        /*Error control*/
        if (!game) {
                return NULL;
        }

        turn = game_get_current_turn(game);

        last_player = (game->players[turn - 1 % game->num_alive_players]);
        if (player_get_health(last_player) <= 0) {
                return NULL;
        }

        return last_player;
}

Status game_add_player(Game* game, Player* player) {
        Id id_aux = NO_ID;
        int index;
        /*Error control*/
        if (!game || !player || (game->n_players == MAX_PLAYERS)) {
                return ERROR;
        }
        id_aux = player_get_id(player);
        index = game_get_player_index_from_id((const Game*)game, id_aux);
        if (index == -1) {
                game->players[game->n_players++] = player;
                if (player_get_health(player) > 0) {
                        game->player_indices[game->num_alive_players++] = game->n_players - 1;
                }
        } else
                return ERROR;
        return OK;
}

int game_get_player_health(const Game* game) {
        if (!game) return -1;
        return player_get_health(game_get_current_player(game));
}

Status game_set_player_new_health(Game* game, int new_health, Player* player) {
        if (!game) return ERROR;

        player_set_health(player, new_health);
        if (new_health <= 0) {
                game_exclude_player(game);
                if (game->num_alive_players == 0) game_set_finished(game, TRUE);
        }

        return OK;
}

const char* game_get_player_name(const Game* game) {
        if (!game) return NULL;
        return player_get_name(game_get_current_player(game));
}

Bool game_player_has_object(const Game* game, Id object) {
        if (!game || object == NO_ID) {
                return FALSE;
        }

        return player_has_object(game->players[game->turn], object);
}

Bool game_get_last_player_won_combat(const Game* game) {
        if (!game) {
                return FALSE;
        }

        return game->combat_succeds;
}

Status game_set_last_player_won_combat(Game* game, Bool won) {
        if (!game) {
                return ERROR;
        }

        game->combat_succeds = won;

        return OK;
}

/*-----------------------------Manejo de Objects-----------------------------*/
int game_get_n_objects(Game* game) {
        if (!game) {
                return -1;
        }

        return game->n_objects;
}

Object* game_get_object_from_index(Game* game, int index) {
        if (!game || index < 0) {
                return NULL;
        }

        return game->objects[index];
}

Object* game_get_object_from_id(const Game* game, Id id) {
        int index;

        if ((!game) || (id == NO_ID)) {
                return NULL;
        }
        index = game_get_object_index_from_id(game, id);

        if (index != -1) return game->objects[index];

        return NULL;
}

Status game_add_object(Game* game, Object* object) {
        /*Just for inserting after reading*/
        int index;
        Id id_aux = NO_ID;
        /*Error control*/
        if (!game || !object || (game->n_objects == MAX_OBJECTS)) {
                return ERROR;
        }
        id_aux = object_get_id(object);
        if (id_aux == NO_ID) {
                return ERROR;
        }

        index = game_get_object_index_from_id((const Game*)game, id_aux);

        if (index == -1) {
                (game->objects)[game->n_objects] = object;
                game->n_objects++;
        } else {
                return ERROR;
        }
        return OK;
}

Id game_get_object_location(const Game* game, Id id) {
        int i;
        if (!game || id == NO_ID) {
                return NO_ID;
        }

        for (i = 0; i < game->n_spaces; i++) {
                if (space_has_object(game->spaces[i], id)) {
                        return space_get_id(game->spaces[i]);
                }
        }
        return NO_ID;
}

/*Just for first setting after creation*/
Status game_set_object_location(Game* game, Id object_id, Id space_id) {
        int i;
        /*Error control*/
        if (!game || object_id == NO_ID || space_id == NO_ID) {
                return ERROR;
        }
        for (i = 0; i < game->n_spaces; i++) {
                if (space_id == space_get_id((const Space*)game->spaces[i])) {
                        return space_add_object(game->spaces[i], object_id);
                }
        }
        return ERROR;
}

Id game_get_object_location_from_name(const Game* game, char* name) {
        Id id_aux = NO_ID;
        int index;

        /*Error control*/
        if (!game || !name) {
                return NO_ID;
        }
        index = game_get_object_index_from_name(game, name);
        if (index != -1)
                id_aux = object_get_id(game->objects[index]);
        else
                return NO_ID;

        return game_get_object_location(game, id_aux);
}

Id game_get_object_id_from_name(const Game* game, const char* name) {
        int index;
        if (!game || !name) return NO_ID;
        index = game_get_object_index_from_name(game, (const char*)name);
        if (index != -1) return object_get_id(game->objects[index]);
        return NO_ID;
}

int game_get_object_health_from_name(const Game* game, const char* name) {
        int index;

        if (!game || !name) {
                return -1;
        }

        index = game_get_object_index_from_name(game, name);

        return object_get_health(game->objects[index]);
}

Status game_object_destroy_from_name(Game* game, char* name) {
        int index;
        if (!game || !name) return -1;
        index = game_get_object_index_from_name(game, name);
        return object_destroy(game->objects[index]);
}

Id game_get_object_open_from_name(const Game* game, char* object_name) {
        int i = 0;

        if (!game || !object_name) {
                return NO_ID;
        }

        for (i = 0; i < game->n_objects; i++) {
                if (strcasecmp(object_name, object_get_name(game->objects[i]))) {
                        return object_get_open(game->objects[i]);
                }
        }

        return NO_ID;
}

/*-----------------------------Manejo de Characters-----------------------------*/

int game_get_n_characters(const Game* game) {
        if (!game) {
                return -1;
        }

        return game->n_characters;
}

Character* game_get_character_from_index(const Game* game, int index) {
        if (!game || index < 0) {
                return NULL;
        }

        return game->characters[index];
}

Character* game_get_character_from_id(const Game* game, Id character_id) {
        int i = 0;

        if (!game || character_id == NO_ID) {
                return NULL;
        }

        for (i = 0; i < game->n_characters; i++) {
                if (character_id == character_get_id(game->characters[i])) {
                        return game->characters[i];
                }
        }

        return NULL;
}

Status game_set_character_location(Game* game, Id loc, Id character_id) {
        if (!game || loc == NO_ID || character_id == NO_ID) {
                return ERROR;
        }

        space_del_character(game_get_space((const Game*)game, loc), game_get_character_location((const Game*)game, character_id));
        return space_add_character(game_get_space((const Game*)game, loc), character_id);
}

Id game_get_character_location(const Game* game, Id character_id) {
        int i = 0;

        if (!game || character_id == NO_ID) {
                return NO_ID;
        }

        for (i = 0; i < game->n_spaces; i++) {
                if (space_has_character(game->spaces[i], character_id) == TRUE) {
                        return space_get_id(game->spaces[i]);
                }
        }

        return NO_ID;
}

int game_get_n_characters_following_current_player(const Game* game) {
        int i = 0;
        int number = 0;
        if (!game) {
                return -1;
        }

        for (i = 0; i < game->n_characters; i++) {
                if (character_get_following(game->characters[i]) == player_get_id(game_get_current_player(game))) {
                        number++;
                }
        }

        return number;
}

Id* game_get_characters_following_current_player(const Game* game) {
        Id* ids;
        int n_followers;
        int total_chars;
        int i;
        int j;
        Player* me;
        Id my_id;
        Character* c;

        if (!game) return NULL;

        n_followers = game_get_n_characters_following_current_player(game);
        if (n_followers <= 0) return NULL;

        ids = (Id*)malloc(n_followers * sizeof(Id));
        if (!ids) return NULL;

        me = game_get_current_player(game);
        my_id = player_get_id(me);
        total_chars = game_get_n_characters(game);
        j = 0;

        for (i = 0; i < total_chars; i++) {
                c = game_get_character_from_index(game, i);
                if (c && character_get_following(c) == my_id) ids[j++] = character_get_id(c);
        }

        return ids;
}

Status game_character_gets_attacked(Game* game, Id character_id) {
        int health, index, damage = 0;
        int i = 0;

        if (!game || character_id == NO_ID) {
                return ERROR;
        }

        damage = player_get_damage(game_get_current_player((const Game*)game));
        for (i = 0; i < game->n_characters; i++) {
                if ((game_get_character_location(game, character_get_id(game->characters[i])) ==
                     game_get_player_location(game)) &&
                    (character_id == character_get_id(game->characters[i]))) {
                        index = game_get_character_index_from_id(game, character_id);
                }
        }

        if (index != -1) {
                health = character_get_health((const Character*)game->characters[index]);

                damage = damage + game_get_n_characters_following_current_player((const Game*)game);

                if (health > 0) {
                        game_pass_turn(game);
                        return character_set_health(game->characters[index], health - damage);
                } else
                        return ERROR;
        }
        return ERROR;
}

Status game_character_gets_attacked_by_use(Game* game, int new_health, char* character_name) {
        int index;
        Character* character = NULL;

        if (!game) {
                return ERROR;
        }

        character = game_get_character_from_name(game, character_name);
        if (!character) {
                return ERROR;
        }

        index = game_get_character_index_from_id((const Game*)game, character_get_id(character));
        if (index != -1) {
                if (new_health > 0) {
                        game_pass_turn(game);
                        return character_set_health(game->characters[index], new_health);
                } else /*Habrá que matar al character, no?*/
                        return ERROR;
        }
        return ERROR;
}

Status game_add_character(Game* game, Character* character) {
        int index;
        Id id_aux = NO_ID;
        /*Error control*/
        if (!game || !character || (game->n_characters == MAX_CHARACTERS)) {
                return ERROR;
        }
        id_aux = character_get_id(character);
        index = game_get_character_index_from_id((const Game*)game, id_aux);
        if (index == -1)
                (game->characters)[(game->n_characters)++] = character;
        else
                return ERROR;
        return OK;
}

Status game_del_character(Game* game, Character* character) {
        if (!game || !character) {
                return ERROR;
        }

        return character_destroy(character);
}

Bool game_get_character_is_alive(const Game* game, Id character_id) {
        int health;
        int index = 0;

        if (!game) {
                return FALSE;
        }

        index = game_get_character_index_from_id(game, character_id);

        health = character_get_health(game->characters[index]);
        if (health <= 0) {
                return FALSE;
        } else {
                return TRUE;
        }
}

Character* game_get_enemy_character_at_space(const Game* game, Id location) {
        int i = 0;
        if (!game || location == NO_ID) {
                return NULL;
        }

        for (i = 0; i < game->n_characters; i++) {
                if (game_get_character_location(game, character_get_id(game->characters[i])) == location &&
                    character_get_friendly(game->characters[i]) == FALSE && character_get_health(game->characters[i]) > 0) {
                        return game->characters[i];
                }
        }

        return NULL;
}

int game_get_character_index_from_name(const Game* game, char* name) {
        int i;
        if (!game || !name) {
                return INVALID_INDEX;
        }

        for (i = 0; i < game->n_characters; i++) {
                if (strcasecmp(character_get_name(game->characters[i]), name) == 0) return i;
        }
        return INVALID_INDEX;
}

Status game_set_character_new_health(const Game* game, int new_health, char* name) {
        if (!game || !new_health) return ERROR;
        return character_set_health(game->characters[game_get_character_index_from_name(game, name)], new_health);
}

int game_get_character_health_from_name(const Game* game, char* name) {
        if (!game || !name) return -1;
        return character_get_health(game->characters[game_get_character_index_from_name(game, name)]);
}

Character* game_get_character_from_name(Game* game, char* name) {
        int i = 0;
        if (!game || !name) {
                return NULL;
        }

        for (i = 0; i < game->n_characters; i++) {
                if (strcasecmp(name, character_get_name(game->characters[i])) == 0) {
                        return game->characters[i];
                }
        }

        return NULL;
}

/*-----------------------------Manejo de Spaces-----------------------------*/
int game_get_n_spaces(Game* game) {
        if (!game) {
                return -1;
        }

        return game->n_spaces;
}

Space* game_get_space_from_index(Game* game, int index) {
        if (!game || index < 0) {
                return NULL;
        }

        return game->spaces[index];
}

void game_get_object_list_at_space(const Game* game, Id space_id, char* list) {
        int num_elems, i;
        Space* space = NULL;
        char dummy[DUMMY_SIZE];
        Id id_aux = NO_ID;
        if (!game || space_id == NO_ID) return;

        space = game_get_space(game, space_id);
        if (space_get_discovered(space) == TRUE) {
                if (!space) return;
                num_elems = space_get_num_objects((const Space*)space);
                if (num_elems > 0)
                        list[0] = '\0';
                else
                        return;
                for (i = 0; i < num_elems; i++) {
                        id_aux = space_get_id_at_index((const Space*)space, i);
                        game_get_object_name_by_id(game, id_aux, dummy);
                        dummy[CUT_INDEX - 1] = ' ';
                        dummy[CUT_INDEX] = '\0';
                        strcat(list, dummy);
                }
                list[strlen(list) - 1] = '\0';
                return;
        }
        return;
}

Space* game_get_space(const Game* game, Id id) {
        int i = 0;
        /*Error control*/
        if (!game || id == NO_ID) {
                return NULL;
        }

        for (i = 0; i < game->n_spaces; i++) {
                if (id == space_get_id(game->spaces[i])) {
                        return game->spaces[i];
                }
        }

        return NULL;
}

Status game_add_space(Game* game, Space* space) {
        int i;
        Id id_aux = NO_ID;
        /*Error control*/
        if (!game || !space || (game->n_spaces == MAX_SPACES)) {
                return ERROR;
        }
        id_aux = space_get_id(space);
        for (i = 0; i < game->n_spaces; i++) {
                if (space_get_id(game->spaces[i]) == id_aux) return OK;
        }
        (game->spaces)[(game->n_spaces)++] = space;

        return OK;
}

/*-----------------------------Manejo de Commands-----------------------------*/
Command* game_get_last_command(const Game* game) {
        /*Error control*/
        if (!game) {
                return NULL;
        }

        return game->last_cmd;
}

Status game_set_last_command(Game* game, Command* command) {
        /*Error control*/
        if (!game) {
                return ERROR;
        }

        game->last_cmd = command;

        return OK;
}

Bool game_get_finished(const Game* game) {
        /*Error control*/
        if (!game) {
                return TRUE;
        }

        return game->finished;
}

Status game_set_finished(Game* game, Bool finished) {
        /*Error control*/
        if (!game) {
                return ERROR;
        }
        game->finished = finished;

        return OK;
}

/*-----------------------------Manejo de Links-----------------------------*/
int game_get_n_links(Game* game) {
        if (!game) {
                return -1;
        }

        return game->n_links;
}

Link* game_get_link_from_index(Game* game, int index) {
        if (!game || index < 0) {
                return NULL;
        }

        return game->links[index];
}

Bool game_connection_is_open(const Game* game, Id current_space_id, Direction direction) {
        int index;
        if (!game || current_space_id == NO_ID || direction == NO_DIRECTION) {
                return FALSE;
        }

        index = game_get_link_index_from_orig_direct(game, current_space_id, direction);
        if (index == INVALID_INDEX) return FALSE;
        return link_get_open((const Link*)game->links[index]);
}

Id game_get_connection(const Game* game, Id current_space_id, Direction direction) {
        int index = INVALID_INDEX;
        if (!game || current_space_id == NO_ID || direction == NO_DIRECTION) {
                return FALSE;
        }
        index = game_get_link_index_from_orig_direct(game, current_space_id, direction);
        if (index == INVALID_INDEX) return NO_ID;
        return link_get_destination((const Link*)game->links[index]);
}

Status game_add_link(Game* game, Link* link) {
        int index;
        Id id_aux = NO_ID;
        /*Error control*/
        if (!game || !link || (game->n_links == MAX_LINKS)) {
                return ERROR;
        }
        id_aux = link_get_id(link);
        index = game_get_link_index_from_id((const Game*)game, id_aux);
        if (index == INVALID_INDEX)
                (game->links)[(game->n_links)++] = link;
        else
                return ERROR;
        return OK;
}

int game_get_link_index_from_orig_direct(const Game* game, Id space_id, Direction direction) {
        int i = 0;
        if (!game || space_id == NO_ID || direction == NO_DIRECTION) {
                return INVALID_INDEX;
        }
        for (i = 0; i < game->n_links; i++) {
                if (space_id == link_get_origin(game->links[i]) && direction == link_get_direction(game->links[i])) {
                        return i;
                }
        }

        return INVALID_INDEX;
}

Id game_get_link(const Game* game, Id space_id, Direction direction) {
        int i = 0;

        if (!game) {
                return NO_ID;
        }

        for (i = 0; i < game->n_links; i++) {
                if ((link_get_origin(game->links[i]) == space_id) && link_get_direction(game->links[i]) == direction) {
                        return link_get_id(game->links[i]);
                }
        }

        return NO_ID;
}

Link* game_get_link_from_name(const Game* game, char* name) {
        int i = 0;

        if (!game || !name) {
                return NULL;
        }

        for (i = 0; i < game->n_links; i++) {
                if (strcasecmp(name, link_get_name(game->links[i])) == 0) {
                        return game->links[i];
                }
        }

        return NULL;
}

/*-----------------------------Other-----------------------------*/
void game_get_info(const Game* game, char* info) {
        int i, j, n_objects;
        char dummy[DUMMY_SIZE + 1];
        char object_name[DUMMY_SIZE + 1];
        char character_name[DUMMY_SIZE + 1];
        Id loc = NO_ID, id_aux = NO_ID;
        Command* command = NULL;
        int index_aux = 0;
        Space* space = NULL;
        Object* object = NULL;

        if (!game || !info) {
                return;
        }

        sprintf(info, "%s", "Objects:|");
        for (i = 0; i < game->n_objects; i++) {
                id_aux = object_get_id(game->objects[i]);
                loc = game_get_object_location(game, id_aux);
                if (loc != NO_ID) {
                        space = game_get_space((const Game*)game, loc);
                        if (!space) return;
                        if (space_get_discovered(space) == TRUE) {
                                sprintf(dummy, "%s", object_get_name(game->objects[i]));
                                strcat(info, "   ");
                                strcat(info, dummy);
                                sprintf(dummy, ":  %3ld|", loc);
                                strcat(info, dummy);
                        }
                }
        }
        strcat(info, "Characters:|");
        for (i = 0; i < game->n_characters; i++) {
                id_aux = character_get_id(game->characters[i]);
                loc = game_get_character_location(game, id_aux);
                space = game_get_space((const Game*)game, loc);
                if (!space) return;
                if (space_get_discovered(space) == TRUE) {
                        sprintf(dummy, "%-6s", character_get_gdesc(game->characters[i]));
                        strcat(info, "   ");
                        strcat(info, dummy);
                        sprintf(dummy, ":  %3ld", loc);
                        strcat(info, dummy);
                        sprintf(dummy, " (%d)|", character_get_health(game->characters[i]));
                        strcat(info, dummy);
                }
        }
        strcat(info, "Players   :|");
        for (i = 0; i < game->n_players; i++) {
                loc = player_get_location(game->players[i]);
                sprintf(dummy, " %6s %3ld (%d)|", player_get_gdesc(game->players[i]), loc, player_get_health(game->players[i]));
                strcat(info, dummy);
                if (i == game->player_indices[game->turn]) {
                        n_objects = player_get_num_objects(game->players[i]);
                        strcat(info, "          Inventory:|");
                        for (j = 0; j < n_objects; j++) {
                                object = game_get_object_from_id(game, player_get_object_at_index(game->players[i], j));
                                sprintf(dummy, "               %s|", object_get_name(object));
                                strcat(info, dummy);
                        }
                }
        }

        command = game_get_last_command((const Game*)game);
        if (!command) {
                command_set_success(game_get_last_command((const Game*)game), ERROR);
                return;
        }

        strcpy(object_name, command_get_arg((const Command*)command));
        id_aux = game_get_object_id_from_name((const Game*)game, object_name);

        index_aux = game_get_object_index_from_id(game, id_aux);

        if (command_get_code(command) == INSPECT && command_get_success(command) == OK) {
                sprintf(dummy, "Inspection of the object %s is: %s", object_get_name(game->objects[index_aux]),
                        game_get_description_of_current_object(game, object_get_name(game->objects[index_aux])));
                strcat(info, dummy);
        }

        command = game_get_last_command((const Game*)game);
        if (!command) {
                command_set_success(game_get_last_command((const Game*)game), ERROR);
                return;
        }
        strcpy(character_name, command_get_arg((const Command*)command));

        i = game_get_character_index_from_name(game, character_name);
        if (command_get_code(command) == CHAT && command_get_success(command) == OK) {
                sprintf(dummy, "Message: %s", character_get_message(game->characters[i]));
                strcat(info, dummy);
        }
}

void game_print(const Game* game) {
        int i = 0;

        if (!game) {
                return;
        }

        printf("\n\n-------------\n\n");
        printf("=> Players: \n");
        for (i = 0; i < game->n_players; i++) player_print(game->players[i]);

        printf("=> Objects: \n");
        for (i = 0; i < game->n_objects; i++) {
                object_print(game->objects[i]);
                printf("\n");
        }
        printf("The number of objects is: %d\n", game->n_objects);
        printf("\n");
        printf("=> Characters: \n");
        for (i = 0; i < game->n_characters; i++) {
                character_print(game->characters[i]);
                printf("\n");
        }
        printf("The number of characters is: %d\n", game->n_characters);
        printf("\n");
        printf("=> Spaces: \n");
        for (i = 0; i < game->n_spaces; i++) {
                space_print(game->spaces[i]);
        }
        printf("The number of spaces is: %d\n", game->n_spaces);
        printf("The finished status is: %d\n", game->finished);
        command_print(game->last_cmd);

        return;
}

/**
   Implementation of private functions
*/

const char* game_get_description_of_current_object(const Game* game, const char* name) {
        Object* object = NULL;

        if (!game || !name) {
                return "";
        }

        object = game_get_object_from_id(game, game_get_object_id_from_name(game, name));

        return object_get_description(object);
}

Id game_get_space_id_at(const Game* game, int position) {
        /*Error control*/
        if (!game) {
                return NO_ID;
        }
        if (position < 0 || position >= game->n_spaces) {
                return NO_ID;
        }

        return space_get_id(game->spaces[position]);
}

void game_get_object_name_by_id(const Game* game, Id id, char* name) {
        int i;
        if (!game || id == NO_ID) return;
        for (i = 0; i < game->n_objects; i++) {
                if (object_get_id(game->objects[i]) == id) {
                        strcpy(name, object_get_name(game->objects[i]));
                        return;
                }
        }
        return;
}

int game_get_object_index_from_name(const Game* game, const char* name) {
        int i;
        if (!game || !name) {
                return INVALID_INDEX;
        }

        for (i = 0; i < game->n_objects; i++) {
                if (strcasecmp(object_get_name(game->objects[i]), name) == 0) return i;
        }
        return INVALID_INDEX;
}

int game_get_object_index_from_id(const Game* game, Id id) {
        int i;
        if (!game || id == NO_ID) return INVALID_INDEX;
        for (i = 0; i < game->n_objects; i++) {
                if (object_get_id(game->objects[i]) == id) return i;
        }
        return INVALID_INDEX;
}

int game_get_character_index_from_id(const Game* game, Id id) {
        int i;
        if (!game || id == NO_ID) return INVALID_INDEX;
        for (i = 0; i < game->n_characters; i++) {
                if (character_get_id(game->characters[i]) == id) return i;
        }
        return INVALID_INDEX;
}

int game_get_link_index_from_id(const Game* game, Id id) {
        int i;
        if (!game || id == NO_ID) return INVALID_INDEX;
        for (i = 0; i < game->n_links; i++) {
                if (link_get_id(game->links[i]) == id) return i;
        }
        return INVALID_INDEX;
}
int game_get_player_index_from_id(const Game* game, Id id) {
        int i;
        if (!game || id == NO_ID) {
                return INVALID_INDEX;
        }

        for (i = 0; i < game->n_players; i++) {
                if (player_get_id(game->players[i]) == id) {
                        return i;
                }
        }
        return INVALID_INDEX;
}

void game_pass_turn(Game* game) {
        if (!game) {
                return;
        }
        if (game->num_alive_players > 0) {
                game->turn = (game->turn + 1) % game->num_alive_players;
        }
        return;
}

void game_exclude_player(Game* game) {
        int i;
        for (i = game->turn; i < game->num_alive_players - 1; i++) {
                game->player_indices[i] = game->player_indices[i + 1];
        }
        game->player_indices[i] = 0;
        game->num_alive_players--;

        if (game->turn >= game->num_alive_players && game->num_alive_players != 0) {
                game->turn--;
        }
        return;
}

const char* game_get_current_player_gdesc(const Game* game) {
        if (!game) {
                return " ";
        }
        if (player_get_health(game->players[game->player_indices[game->turn]]) <= 0) {
                return "   /+\\";
        } else {
                return player_get_gdesc(game->players[game->player_indices[game->turn]]);
        }
}

int game_get_current_turn(const Game* game) {
        if (!game) {
                return INVALID_INDEX;
        }
        return game->player_indices[game->turn];
}

void game_write_recent_log(const Game* game, const char* file) {
        Command* command = NULL;
        char arg_buff[ARG_SIZE];
        FILE* f = NULL;
        if (!game || !file) {
                return;
        }
        command = game_get_last_command(game);
        if (!command) {
                return;
        }

        strcpy(arg_buff, command_get_arg(command));
        f = fopen(file, "a");
        if (!f) {
                return;
        }

        fprintf(f, "%s %s: %s (%s)\n", command_get_string_code(command), arg_buff[0] == '\0' ? "" : arg_buff,
                command_get_success(command) == OK ? "OK" : "ERROR", game_get_player_name(game));
        fclose(f);
        return;
}

void game_get_players_row_at_space(const Game* game, Id id, char* first_row, char* second_row) {
        int i, count = 0;
        char buffer1[MAX_BUFFER1 + 1], buffer2[MAX_BUFFER2 + 1];
        if (!game || !first_row || !second_row) return;
        if (id != NO_ID) {
                for (i = 0; i < game->n_players && count < MAX_ROW_PLAYERS; i++) {
                        if (player_get_location(game->players[i]) == id && i != game->player_indices[game->turn]) {
                                strcpy(buffer1, player_get_gdesc(game->players[i]));
                                strcpy(buffer2, &buffer1[CUT_INDEX - 1]);
                                if (count < 3)
                                        sprintf(buffer1, "%3s|", player_get_health(game->players[i]) == 0 ? "/+\\" : buffer2);
                                else
                                        sprintf(buffer1, "%3s  ", player_get_health(game->players[i]) == 0 ? "/+\\" : buffer2);
                                strcat(first_row, buffer1);
                                count++;
                        }
                }
        }
        if (count < MAX_ROW_PLAYERS) {
                for (; count < MAX_ROW_PLAYERS; count++) {
                        if (count < 3)
                                strcat(first_row, id == -1 ? "    " : "   |");
                        else
                                strcat(first_row, id == -1 ? "     " : "   | ");
                }
        }

        count = 0;
        if (id != NO_ID) {
                for (; i < game->n_players; i++) {
                        if (player_get_location(game->players[i]) == id && i != game->player_indices[game->turn]) {
                                strcpy(buffer1, player_get_gdesc(game->players[i]));
                                strcpy(buffer2, &buffer1[CUT_INDEX - 1]);
                                if (count < 3)
                                        sprintf(buffer1, "%3s|", player_get_health(game->players[i]) == 0 ? "/+\\" : buffer2);
                                else
                                        sprintf(buffer1, "%3s  ", player_get_health(game->players[i]) == 0 ? "/+\\" : buffer2);
                                strcat(second_row, buffer1);
                                count++;
                        }
                }
        }
        if (count < MAX_ROW_PLAYERS) {
                for (; count < MAX_ROW_PLAYERS; count++) {
                        if (count < 3)
                                strcat(second_row, id == -1 ? "    " : "   |");
                        else
                                strcat(second_row, "     ");
                }
        }
}

Status game_set_deterministic_mode(Game* game, int deterministic) {
        if (!game || !deterministic) {
                return ERROR;
        }
        game->deterministic = deterministic;
        return OK;
}

Status game_set_turn(Game* game, int turn) {
        if (turn <= -1) {
                return ERROR;
        }
        game->turn = turn;
        return OK;
}

int game_get_turn(Game* game) { return game->turn; }

Status game_game_management_save(Game* game, char* filename) {
        if (!game || filename == NULL) {
                return ERROR;
        }
        return game_management_save(&game, filename);
}

Status game_game_management_load(Game* game, char* filename) {
        if (!game || filename == NULL) {
                return ERROR;
        }
        return game_management_load(&game, filename);
}
