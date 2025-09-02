/**
 * @brief It implements the specific game rules for our game
 *
 * @file game_management.c
 * @author Carlos Méndez, Jorge Ochoa y Jorge Pastor
 * @version 4.0
 * @date 01-05-2025
 * @copyright GNU Public License
 */

#include "game_rules.h"

#include <stdio.h>
/**
 * @def MAX_BUFFER
 * @brief Defines the length of general purpose buffer
 */
#define MAX_BUFFER 100

/**
 * @def FANG_ID
 * @brief Defines de Id given to the object "fangs"
 */
#define FANG_ID 134

/**
 * @def FANG_NAME
 * @brief Defines the name given to the object "fangs"
 */
#define FANG_NAME "fang"

/**
 * @def FANG_DESCRIPTION
 * @brief Defines the description given to the object "fangs"
 */
#define FANG_DESCRIPTION "Looks pretty sharp and venomous, perfect when dealing with cobwebs"

/**
 * @def FANG_MOVABLE
 * @brief Defines the movable given to the object "fangs"
 */
#define FANG_MOVABLE TRUE

/**
 * @def FANG_DEPENDENCY
 * @brief Defines the dependency given to the object "fangs"
 */
#define FANG_DEPENDENCY NO_ID

/**
 * @def FANG_OPEN
 * @brief Defines the open given to the object "fangs"
 */
#define FANG_OPEN 76

/**
 * @def FANG_DAMAGE
 * @brief Defines the new damage a player deals when holding this item
 */
#define FANG_DAMAGE 3

/**
 * @def STRING_ID
 * @brief Defines de Id given to the object "string"
 */
#define STRING_ID 201

/**
 * @def STRING_NAME
 * @brief Defines the name given to the object "string"
 */
#define STRING_NAME "string"

/**
 * @def STRING_DESCRIPTION
 * @brief Defines the description given to the object "string"
 */
#define STRING_DESCRIPTION "Looks strong enough to build things"

/**
 * @def STRING_MOVABLE
 * @brief Defines the movable given to the object "string"
 */
#define STRING_MOVABLE TRUE

/**
 * @def STRING_DEPENDENCY
 * @brief Defines the dependency given to the object "string"
 */
#define STRING_DEPENDENCY NO_ID

/**
 * @def STRING_OPEN
 * @brief Defines the open given to the object "string"
 */
#define STRING_OPEN 35

/**
 * @def ANT1_ID
 * @brief Defines de Id given to the ant1
 */
#define ANT1_ID 111

/**
 * @def ANT1_NAME
 * @brief Defines de name given to the ant1
 */
#define ANT1_NAME "Group_of_ants"

/**
 * @def ANT_HEALTH
 * @brief Defines the health given to all enemy ants
 */
#define ANT_HEALTH 15

/**
 * @def ANT_GDESC
 * @brief Defines de gdesc given to all enemy ants
 */
#define ANT_GDESC "^mo ^mo ^mo"

/**
 * @def NEW_ANT_ID
 * @brief Defines de Id given to the new born ant
 */
#define NEW_ANT_ID 189

/**
 * @def NEW_ANT_NAME
 * @brief Defines de name given to the new born ant
 */
#define NEW_ANT_NAME "FRED"

/**
 * @def NEW_ANT_MESSAGE
 * @brief Defines the messsage given to the new born ant
 */
#define NEW_ANT_MESSAGE "Lets go defend the colony! For the queen!"

/**
 * @def NEW_ANT_GDESC
 * @brief Defines de gdesc given to the new born ant
 */
#define NEW_ANT_GDESC "Mmo^"

/**
 * @def ANTS_SPAWN_LOCATION
 * @brief Defines where the group of ants spawns
 */
#define ANTS_SPAWN_LOCATION 14

/**
 * @def SPIDER_LOCATION
 * @brief Defines where the group of ants spawns
 */
#define SPIDER_LOCATION 7

/**
 * @def QUEEN_ANT_LOCATION
 * @brief Defines where the queen ant is hiding
 */
#define QUEEN_ANT_LOCATION 52

#define PROVISIONAL_ID 1

Status game_rule_update(Game* game, Command* last_cmd, int turn, int* times_feeded, Bool* spider_is_dead) {
        char arg[MAX_BUFFER + 1];
        /*int frequency = 0;*/

        if (!game) {
                return ERROR;
        }

        last_cmd = game_get_last_command((const Game*)game);
        if (!last_cmd) {
                command_set_success(game_get_last_command((const Game*)game), ERROR);
                return ERROR;
        }

        strcpy(arg, command_get_arg((const Command*)last_cmd));

        /*if ((game_get_n_players(game)) == 1) {
                frequency = 5;
        } else {
                frequency = (2 * game_get_n_players(game)) + 1;
        }*/

        /*Crumbling_roof condition*/ /*Sí funciona*/
        /*if ((turn) % frequency == 0) {

                game_rule_crumbling_roof(game);
                if ((strcasecmp(command_get_string_code(last_cmd), "move") == 0) ||
                    (strcasecmp(command_get_string_code(last_cmd), "take") == 0) ||
                    (strcasecmp(command_get_string_code(last_cmd), "drop") == 0)) {
                        return OK;
                }

                game_pass_turn(game);
                return OK;
        }*/

        /*Spider venom damage condition*/ /*Sí funciona*/
        if ((command_get_code(last_cmd) == ATTACK) && (strcasecmp(arg, "spider") == 0) &&
            (game_get_last_player_won_combat(game) == FALSE) && (command_get_success(last_cmd) == OK)) {
                return game_rule_spiders_venom_damage(game);
        }

        /*Spider dies condition*/ /*NO funciona (Seg_Fault)*/
        if (character_get_name(game_get_character_from_name(game, "spider")) != NULL) {
                if ((strcasecmp(character_get_name(game_get_character_from_name(game, "spider")), arg) == 0) &&
                    ((character_get_health(game_get_character_from_name(game, arg))) <= 0) && ((*spider_is_dead) == FALSE)) {
                        *spider_is_dead = TRUE;
                        character_set_name(game_get_character_from_name(game, "spider"), "spider_");
                }
        }

        if ((*spider_is_dead) == TRUE) {
                if (game_rule_spider_dies(game) == OK) {
                        *spider_is_dead = FALSE;
                        return OK;
                }
        }

        /*Feed queen condition*/ /*No testeado, (Error en Use)*/
        if ((command_get_code(last_cmd) == USE) && (strcasecmp(command_get_arg(last_cmd), "Food over Queen_Ant") == 0) &&
            (command_get_success(last_cmd) == OK)) {
                ++(*times_feeded);
        }

        if (*times_feeded == 5) {
                return game_rule_feed_queen(game);
        }

        /*Ant invasion condition*/ /*Da un error tocho: make: *** [execute] Trace/BPT trap: 5*/
        if ((player_get_location(game_get_current_player((const Game*)game)) == 13) ||
            (player_get_location(game_get_last_player((const Game*)game)) == 13)) {
                return game_rule_ant_invasion(game);
        }

        /*Attack with fangs condition*/ /*No testeado, necesito que se spawnenen primero las fangs*/
        if (player_has_object(game_get_last_player((const Game*)game), FANG_ID) == FALSE) {
                return game_rule_attack_with_fangs(game);
        }

        return OK;
}

Status game_rule_crumbling_roof(Game* game) {
        Player* current_player = NULL;

        if (!game) {
                return ERROR;
        }

        current_player = game_get_last_player((const Game*)game);
        if (!current_player) {
                return ERROR;
        }

        return game_set_player_new_health(game, player_get_health(current_player) - 1, current_player);
}

Status game_rule_spiders_venom_damage(Game* game) {
        Player* current_player = NULL;

        if (!game) {
                return ERROR;
        }

        current_player = game_get_last_player((const Game*)game);
        if (!current_player) {
                return ERROR;
        }

        return game_set_player_new_health(game, player_get_health(current_player) - 1, current_player);
}

Status game_rule_spider_dies(Game* game) {
        Object* fangs = NULL;
        Object* string = NULL;

        fangs = object_create(FANG_ID);
        string = object_create(STRING_ID);

        if (object_set_name(fangs, FANG_NAME) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_description(fangs, FANG_DESCRIPTION) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_open(fangs, FANG_OPEN) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_dependency(fangs, FANG_DEPENDENCY) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_movable(fangs, FANG_MOVABLE) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_name(string, STRING_NAME) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_description(string, STRING_DESCRIPTION) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_movable(string, STRING_MOVABLE) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_dependency(string, STRING_DEPENDENCY) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        if (object_set_open(string, STRING_OPEN) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        /*printf("String address: %p\t, fangs address %p\n", string, fangs);
        object_print(fangs);
        object_print(string);*/
        if (game_add_object(game, string) != OK || game_add_object(game, fangs) != OK) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }

        /*CAMBIAR POR SPIDER_LOCATION*/
        if (space_add_object(game_get_space((const Game*)game, 3), FANG_ID) == ERROR ||
            space_add_object(game_get_space((const Game*)game, 3), STRING_ID) == ERROR) {
                object_destroy(fangs);
                object_destroy(string);
                return ERROR;
        }
        return OK;
}

Status game_rule_feed_queen(Game* game) {
        Character* ally_ant = NULL;

        if (!game) {
                return ERROR;
        }

        ally_ant = character_create(NEW_ANT_ID);

        if (character_set_name(ally_ant, NEW_ANT_NAME) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (character_set_health(ally_ant, ANT_HEALTH) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (character_set_gdesc(ally_ant, NEW_ANT_GDESC) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (character_set_message(ally_ant, NEW_ANT_MESSAGE) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (character_set_following(ally_ant, player_get_id(game_get_current_player((const Game*)game))) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (character_set_friendly(ally_ant, TRUE) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (space_add_character(game_get_space((const Game*)game, QUEEN_ANT_LOCATION), NEW_ANT_ID) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        if (game_add_character(game, ally_ant) == ERROR) {
                character_destroy(ally_ant);
                return ERROR;
        }

        return OK;
}

Status game_rule_ant_invasion(Game* game) {
        Character* ant1 = NULL;

        if (!game) {
                return ERROR;
        }

        ant1 = character_create(ANT1_ID);

        if (character_set_name(ant1, ANT1_NAME) == ERROR) {
                character_destroy(ant1);
                return ERROR;
        }

        if (character_set_health(ant1, ANT_HEALTH) == ERROR) {
                character_destroy(ant1);
                return ERROR;
        }

        if (character_set_gdesc(ant1, ANT_GDESC) == ERROR) {
                character_destroy(ant1);
                return ERROR;
        }
        if ((space_add_character(game_get_space((const Game*)game, ANTS_SPAWN_LOCATION), ANT1_ID) == ERROR)) {
                character_destroy(ant1);
                return ERROR;
        }

        if (game_add_character(game, ant1) == ERROR) {
                character_destroy(ant1);
                return ERROR;
        }

        return OK;
}

Status game_rule_attack_with_fangs(Game* game) {
        if (!game) {
                return ERROR;
        }

        return game_set_player_damage(game_get_last_player((const Game*)game), FANG_DAMAGE);
}
