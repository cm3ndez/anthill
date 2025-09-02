/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Abraham Martín and Carlos Méndez
 * @version 3.0
 * @date 30-03-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>

/**
 * @def MAX_BUFFER
 * @brief Defines the length of general purpose buffer
 */
#define MAX_BUFFER 100

/**
 * @def LONG_NORTH
 * @brief Defines a constant long string for NORTH
 */
#define LONG_NORTH "north"

/**
 * @def LONG_SOUTH
 * @brief Defines a constant long string for SOUTH
 */
#define LONG_SOUTH "south"

/**
 * @def LONG_EAST
 * @brief Defines a constant long string for EAST
 */
#define LONG_EAST "east"

/**
 * @def LONG_WEST
 * @brief Defines a constant long string for WEST
 */
#define LONG_WEST "west"

/**
 * @def LONG_UP
 * @brief Defines a constant long string for UP
 */
#define LONG_UP "up"

/**
 * @def LONG_DOWN
 * @brief Defines a constant long string for DOWN
 */
#define LONG_DOWN "down"

/**
 * @def SHORT_NORTH
 * @brief Defines a constant short string for NORTH
 */
#define SHORT_NORTH "N"

/**
 * @def SHORT_SOUTH
 * @brief Defines a constant short string for SOUTH
 */
#define SHORT_SOUTH "S"

/**
 * @def SHORT_EAST
 * @brief Defines a constant short string for EAST
 */
#define SHORT_EAST "E"

/**
 * @def SHORT_WEST
 * @brief Defines a constant short string for WEST
 */
#define SHORT_WEST "W"
/**
   Private functions
*/

/**
 * @def SHORT_UP
 * @brief Defines a constant short string for UP
 */
#define SHORT_UP "U"

/**
 * @def SHORT_DOWN
 * @brief Defines a constant short string for DOWN
 */
#define SHORT_DOWN "D"

/* Private Functions*/

/**
 * @brief Calls itself to drop every object that depends on the one droped
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 * @param object_id Object to be removed
 */
Status drop_rec(Game *game, Id object_id);

/**
 * @brief Implements what happens if the player enters an unknown input
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
void game_actions_unknown(Game *game);

/**
 * @brief Implements what happens if the player enters the exit input
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
void game_actions_exit(Game *game);

/**
 * @brief Implements what happens if the player enters the take input
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
void game_actions_take(Game *game);

/**
 * @brief Implements what happens if the player enters the drop input
 * @author Abraham Martín
 *
 * @param game Pointer to the game being played
 */
void game_actions_drop(Game *game);

/**
 * @brief Implements what happens if the player enters the chat input. Does not consume turn.
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_chat(Game *game);

/**
 * @brief Implements what happens if the player enters the attack input
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_attack(Game *game);

/**
 * @brief Implements what happens if the player enters the move input
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_move(Game *game);

/**
 * @brief Implements what happens if the player enters the inspect input. Does not consume turn.
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_inspect(Game *game);

/**
 * @brief Implements what happens if the player enters the use input
 * @author Jorge Ochoa
 *
 * @param game Pointer to the game being played
 */
void game_actions_use(Game *game);

/**
 * @brief Implements what happens if the player enters the recruit input
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_recruit(Game *game);

/**
 * @brief Implements what happens if the player enters the abandon input
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_abandon(Game *game);

/**
 * @brief Implements what happens if the player enters the open input
 * @author Carlos Méndez
 *
 * @param game Pointer to the game being played
 */
void game_actions_open(Game *game);

/**
 * @brief Implements what happens if the player loads a game
 * @author JOrge Ochoa
 *
 * @param game Pointer to the game being played
 */
Status game_actions_load(Game *game);

/**
 * @brief Implements what happens if the player saves a game
 * @author JOrge Ochoa
 *
 * @param game Pointer to the game being played
 */
Status game_actions_save(Game *game);
/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
        CommandCode cmd;
        /*Error control*/
        if ((!game) || (!command)) {
                return ERROR;
        }
        game_set_last_command(game, command);

        cmd = command_get_code(command);

        switch (cmd) {
                case UNKNOWN:
                        game_actions_unknown(game);
                        break;
                case EXIT:
                        game_actions_exit(game);
                        break;
                case TAKE:
                        game_actions_take(game);
                        break;
                case DROP:
                        game_actions_drop(game);
                        break;
                case CHAT:
                        game_actions_chat(game);
                        break;
                case ATTACK:
                        game_actions_attack(game);
                        break;
                case MOVE:
                        game_actions_move(game);
                        break;
                case INSPECT:
                        game_actions_inspect(game);
                        break;
                case USE:
                        game_actions_use(game);
                        break;
                case RECRUIT:
                        game_actions_recruit(game);
                        break;
                case ABANDON:
                        game_actions_abandon(game);
                        break;
                case OPEN:
                        game_actions_open(game);
                        break;
                case LOAD:
                        game_actions_load(game);
                        break;
                case SAVE:
                        game_actions_save(game);
                        break;
                default:
                        break;
        }

        return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {
        command_set_success(game_get_last_command((const Game *)game), OK);
        return;
}

void game_actions_exit(Game *game) {
        Command *cmd = NULL;

        if (!game) return;

        cmd = game_get_last_command((const Game *)game);
        if (cmd) {
                command_set_success(cmd, OK);
        }

        return;
}

void game_actions_take(Game *game) {
        Id id_loc = NO_ID, object_id = NO_ID;
        Command *last_cmd = NULL;
        Space *space = NULL;
        Player *current_player = NULL;
        Object *object = NULL;
        Id necessary_object = 0;
        char arg[MAX_BUFFER + 1];
        Bool condition = FALSE;

        /*Error control*/
        if (!game) {
                return;
        }

        last_cmd = game_get_last_command((const Game *)game);
        space = game_get_space((const Game *)game, game_get_player_location((const Game *)game));
        strcpy(arg, command_get_arg((const Command *)last_cmd));
        id_loc = game_get_object_location_from_name((const Game *)game, (char *)arg);
        if (!last_cmd || !space || id_loc == NO_ID) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        current_player = game_get_current_player(game);
        if (id_loc == game_get_player_location((const Game *)game)) {
                object_id = game_get_object_id_from_name((const Game *)game, arg);
                object = game_get_object_from_id(game, object_id);

                necessary_object = object_get_dependency(object);
                if (player_has_object(current_player, necessary_object) == TRUE) {
                        condition = TRUE;
                }
                if (condition == TRUE || necessary_object == NO_ID) {
                        if (game_put_object_on_player(game, space_del_object(space, object_id)) == OK &&
                            (object_get_movable(object) == TRUE)) {
                                game_pass_turn(game);
                                command_set_success(game_get_last_command((const Game *)game), OK);
                                return;
                        }
                } else {
                        space_add_object(space, object_id);
                        command_set_success(game_get_last_command((const Game *)game), ERROR);
                        return;
                }

        } else {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
        }

        return;
}

void game_actions_drop(Game *game) {
        Command *last_cmd = NULL;
        char arg[MAX_BUFFER + 1];
        Id object_id = NO_ID;

        /*Error control*/
        if (!game) {
                return;
        }
        last_cmd = game_get_last_command((const Game *)game);
        strcpy(arg, command_get_arg((const Command *)last_cmd));
        object_id = game_get_object_id_from_name((const Game *)game, arg);

        if (!last_cmd) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        if (drop_rec(game, object_id) == OK) {
                game_pass_turn(game);
                command_set_success(last_cmd, OK);
        } else {
                command_set_success(last_cmd, ERROR);
        }
        return;
}

Status drop_rec(Game *game, Id object_id) {
        Space *space = NULL;
        Object *object = NULL;
        Player *current_player = NULL;

        int i = 0;

        if (!game) {
                return ERROR;
        }

        space = game_get_space((const Game *)game, game_get_player_location((const Game *)game));
        if (!space) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return ERROR;
        }

        object = game_get_object_from_id(game, object_id);
        if (!object) {
                return ERROR;
        }

        current_player = game_get_current_player(game);
        if (!current_player) {
                return ERROR;
        }

        if (game_extract_object_from_player(game, object_id) == object_id && space_add_object(space, object_id) == OK) {
                for (i = 0; i < player_get_num_objects(current_player); i++) {
                        if (object_get_dependency(game_get_object_from_id(game, player_get_object_at_index(current_player, i))) ==
                            object_id) {
                                drop_rec(game, player_get_object_at_index(current_player, i));
                        }
                }
                return OK;
        } else {
                if (object_id != NO_ID) {
                        space_del_object(space, object_id);
                }
        }
        return ERROR;
}

void game_actions_chat(Game *game) {
        Id character_id = NO_ID;
        char arg[MAX_BUFFER + 1];
        Command *last_cmd = NULL;

        if (!game) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        last_cmd = game_get_last_command((const Game *)game);
        if (!last_cmd) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        strcpy(arg, command_get_arg((const Command *)last_cmd));
        character_id = character_get_id(game_get_character_from_name(game, arg));

        if (character_id != NO_ID) {
                command_set_success(game_get_last_command((const Game *)game), OK);
                return;
        } else {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        command_set_success(game_get_last_command((const Game *)game), ERROR);
        return;
}

void game_actions_attack(Game *game) {
        int number;
        Command *last_cmd = NULL;
        char arg[MAX_BUFFER + 1];
        Id character_id;
        Character *character = NULL;
        const char *cmd_arg = NULL;
        int divisor = 10;

        if (!game) {
                return;
        }

        last_cmd = game_get_last_command(game);
        if (!last_cmd) {
                return;
        }

        cmd_arg = command_get_arg((const Command *)last_cmd);
        if (!cmd_arg) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        strcpy(arg, cmd_arg);

        character = game_get_character_from_name(game, arg);
        if (!character) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        character_id = character_get_id(character);

        if (game_get_character_is_alive(game, character_id) && character_get_friendly(character) == FALSE &&
            player_get_location(game_get_current_player(game)) == game_get_character_location((const Game *)game, character_id)) {
                number = rand() % divisor;

                if (number >= 0 && number <= 4) {
                        game_set_last_player_won_combat(game, FALSE);
                        command_set_success(last_cmd, game_player_gets_attacked(game));
                } else {
                        game_set_last_player_won_combat(game, TRUE);
                        command_set_success(last_cmd, game_character_gets_attacked(game, character_id));
                }

                return;
        }

        command_set_success(last_cmd, ERROR);
        return;
}

void game_actions_move(Game *game) {
        Command *last_cmd = NULL;
        char arg[MAX_BUFFER + 1];
        Id space_id = NO_ID;
        Id new_location = NO_ID;
        Direction direction = NO_DIRECTION;
        Space *space = NULL;
        Bool open = FALSE;
        int i = 0;
        int n_characters_following = 0;
        Id *characters_following;

        /*Error control*/
        if (!game) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        last_cmd = game_get_last_command((const Game *)game);
        if (!last_cmd) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }
        strcpy(arg, command_get_arg((const Command *)last_cmd));

        space_id = game_get_player_location((const Game *)game);
        if (space_id == NO_ID) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        if (strcasecmp(arg, SHORT_NORTH) == 0 || strcasecmp(arg, LONG_NORTH) == 0) {
                direction = N;
        } else if (strcasecmp(arg, SHORT_SOUTH) == 0 || strcasecmp(arg, LONG_SOUTH) == 0) {
                direction = S;
        } else if (strcasecmp(arg, SHORT_EAST) == 0 || strcasecmp(arg, LONG_EAST) == 0) {
                direction = E;
        } else if (strcasecmp(arg, SHORT_WEST) == 0 || strcasecmp(arg, LONG_WEST) == 0) {
                direction = W;
        } else if (strcasecmp(arg, SHORT_UP) == 0 || strcasecmp(arg, LONG_UP) == 0) {
                direction = U;
        } else if (strcasecmp(arg, SHORT_DOWN) == 0 || strcasecmp(arg, LONG_DOWN) == 0) {
                direction = D;
        } else {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        new_location = game_get_connection((const Game *)game, space_id, direction);
        open = game_connection_is_open((const Game *)game, space_id, direction);

        if (new_location != NO_ID) {
                if (open == TRUE) {
                        if (game_set_player_location(game, new_location) == OK) {
                                space = game_get_space(game, new_location);
                                if (!space) {
                                        command_set_success(game_get_last_command((const Game *)game), ERROR);
                                        return;
                                }
                                space_set_discovered(space, TRUE);

                                n_characters_following = game_get_n_characters_following_current_player((const Game *)game);
                                if (n_characters_following == -1) {
                                        command_set_success(game_get_last_command((const Game *)game), ERROR);
                                        return;
                                }

                                characters_following = game_get_characters_following_current_player((const Game *)game);

                                for (i = 0; i < n_characters_following; i++) {
                                        if (game_set_character_location(game, new_location, characters_following[i]) == ERROR) {
                                                command_set_success(game_get_last_command((const Game *)game), ERROR);
                                                free(characters_following);
                                                return;
                                        }
                                }

                                free(characters_following);
                                game_pass_turn(game);
                                command_set_success(game_get_last_command((const Game *)game), OK);
                                return;
                        }

                        else {
                                command_set_success(game_get_last_command((const Game *)game), ERROR);
                                return;
                        }
                }
        }

        command_set_success(game_get_last_command((const Game *)game), ERROR);
        return;
}

void game_actions_inspect(Game *game) {
        const Space *space = NULL;
        Id object_id = NO_ID;
        Id space_id = NO_ID;
        char arg[MAX_BUFFER + 1];
        Command *last_cmd = NULL;

        if (!game) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        last_cmd = game_get_last_command((const Game *)game);
        if (!last_cmd) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        strcpy(arg, command_get_arg((const Command *)last_cmd));
        object_id = game_get_object_id_from_name((const Game *)game, arg);
        if (object_id == NO_ID) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }
        space_id = game_get_player_location((const Game *)game);
        if (space_id == NO_ID) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }
        space = game_get_space((const Game *)game, space_id);

        if ((space_has_object(space, object_id) || game_get_object_location((const Game *)game, object_id) == NO_ID)) {
                command_set_success(game_get_last_command((const Game *)game), OK);
                return;
        } else {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        command_set_success(game_get_last_command((const Game *)game), ERROR);
        return;
}

void game_actions_use(Game *game) {
        Command *last_cmd = NULL;
        Id object_id = NO_ID;
        char arg[MAX_BUFFER + 1];
        char character_name[MAX_BUFFER + 1];
        char object_name[MAX_BUFFER + 1];
        char *token = NULL;
        int object_health, player_health, character_health;
        Bool alive;
        Character *character = NULL;
        const char *cmd_arg = NULL;

        if (!game || !(last_cmd = game_get_last_command((const Game *)game))) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        cmd_arg = command_get_arg((const Command *)last_cmd);
        if (!cmd_arg) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        strcpy(arg, cmd_arg);

        object_id = game_get_object_id_from_name((const Game *)game, arg);
        if (object_id == NO_ID) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        if (game_player_has_object((const Game *)game, object_id) == FALSE) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        object_health = game_get_object_health_from_name(game, arg);

        token = strtok(arg, " ");

        if (token) {
                strcpy(object_name, token);
                token = strtok(NULL, " ");

                if (token && strcmp(token, "over") == 0) {
                        token = strtok(NULL, " ");

                        if (token) {
                                strcpy(character_name, token);
                                character = game_get_character_from_name(game, character_name);

                                if (character &&
                                    character_get_following(character) == player_get_id(game_get_current_player(game)) &&
                                    character_get_friendly(character) == TRUE) {
                                        alive = character_get_health(character) > 0 ? TRUE : FALSE;

                                        if (object_health != 0) {
                                                if (alive == FALSE) {
                                                        command_set_success(last_cmd, OK);
                                                        return;
                                                }

                                                character_health = game_get_character_health_from_name(game, character_name);
                                                game_character_gets_attacked_by_use(game, character_health + object_health,
                                                                                    character_name);
                                                game_object_destroy_from_name(game, object_name);
                                                command_set_success(last_cmd, OK);
                                                return;
                                        }
                                }
                        }
                }
        }

        character_name[0] = '\0';
        player_health = game_get_player_health(game);
        game_player_gets_attacked_by_use(game, (player_health + object_health));
        player_del_object(game_get_current_player((const Game *)game), object_id);
        game_object_destroy_from_name(game, object_name);
        command_set_success(last_cmd, OK);
        return;
}

void game_actions_recruit(Game *game) {
        Command *last_cmd = NULL;
        char arg[MAX_BUFFER + 1];
        Character *current_character = NULL;
        Player *current_player = NULL;
        Id player_id = NO_ID;

        if (!game || !(last_cmd = game_get_last_command((const Game *)game))) {
                return;
        }

        strcpy(arg, command_get_arg((const Command *)last_cmd));

        current_character = game_get_character_from_name(game, arg);
        if (!current_character) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        current_player = game_get_current_player(game);
        if (!current_player) {
                command_set_success(last_cmd, ERROR);
                return;
        }

        player_id = player_get_id(current_player);

        if (game_get_player_location(game) == game_get_character_location(game, character_get_id(current_character)) &&
            character_get_friendly(current_character) == TRUE && character_get_following(current_character) == NO_ID) {
                character_set_following(current_character, player_id);
                command_set_success(last_cmd, OK);
                return;
        }

        command_set_success(last_cmd, ERROR);
}

void game_actions_abandon(Game *game) {
        Command *last_cmd = NULL;
        char arg[MAX_BUFFER + 1];
        Character *current_character = NULL;
        Player *current_player = NULL;
        Id player_id = NO_ID;

        if (!game || !(last_cmd = game_get_last_command((const Game *)game))) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        strcpy(arg, command_get_arg((const Command *)last_cmd));

        current_character = game_get_character_from_name(game, arg);
        if (!current_character) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        current_player = game_get_current_player(game);
        if (!current_player) {
                command_set_success(game_get_last_command((const Game *)game), ERROR);
                return;
        }

        player_id = player_get_id(current_player);

        if (game_get_player_location(game) == game_get_character_location(game, character_get_id(current_character)) &&
            character_get_following(current_character) == player_id) {
                character_set_following(current_character, NO_ID);
                command_set_success(game_get_last_command((const Game *)game), OK);
                return;
        }

        command_set_success(game_get_last_command((const Game *)game), ERROR);
}

void game_actions_open(Game *game) {
        Command *last_cmd = NULL;
        char arg[MAX_BUFFER + 1];
        char link_name[MAX_BUFFER + 1];
        char object_name[MAX_BUFFER + 1];
        char *token = NULL;
        Id object_open = NO_ID;
        Id object_location = NO_ID;
        Id object_id = NO_ID;
        Link *current_link;

        if (!game || !(last_cmd = game_get_last_command(game))) {
                command_set_success(game_get_last_command(game), ERROR);
                return;
        }

        strcpy(arg, command_get_arg((const Command *)last_cmd));

        token = strtok(arg, " ");
        if (token) {
                strcpy(link_name, token);

                current_link = game_get_link_from_name(game, link_name);
                if (!current_link) {
                        command_set_success(game_get_last_command(game), ERROR);
                        return;
                }

                token = strtok(NULL, " ");
                if (strcmp(token, "with") == 0) {
                        token = strtok(NULL, " ");
                        if (token) {
                                strcpy(object_name, token);

                                object_location = game_get_object_location_from_name(game, object_name);
                                if (object_location != NO_ID) {
                                        command_set_success(game_get_last_command(game), ERROR);
                                        return;
                                }

                                object_open = game_get_object_open_from_name(game, object_name);
                                if (object_open == NO_ID) {
                                        command_set_success(game_get_last_command(game), ERROR);
                                        return;
                                }

                                object_id = game_get_object_id_from_name(game, object_name);
                                if (object_id == NO_ID) {
                                        command_set_success(game_get_last_command(game), ERROR);
                                        return;
                                }

                                if (game_player_has_object(game, object_id) == FALSE) {
                                        command_set_success(game_get_last_command(game), ERROR);
                                        return;
                                }

                                if (object_open == link_get_id(current_link) && link_get_open(current_link) == FALSE) {
                                        link_set_open(current_link, TRUE);
                                        command_set_success(game_get_last_command(game), OK);
                                        return;
                                }
                                command_set_success(game_get_last_command(game), ERROR);
                                return;
                        }
                }
        }

        command_set_success(game_get_last_command(game), ERROR);
        return;
}

Status game_actions_save(Game *game) {
        char *command_string = NULL;
        char *token = NULL;
        char *filename = NULL;
        char command_copy[MAX_BUFFER];

        if (!game) {
                return ERROR;
        }

        strcpy(command_string, command_get_string_code(game_get_last_command(game)));
        if (strcpy(command_string, command_get_string_code(game_get_last_command(game))) != 0) {
                return ERROR;
        }

        strncpy(command_copy, command_string, sizeof(command_copy) - 1);
        command_copy[sizeof(command_copy) - 1] = '\0';

        token = strtok(command_copy, " ");
        if (!token || strcmp(token, "save") != 0) {
                return ERROR;
        }
        token = strtok(NULL, " ");
        if (!token) {
                return ERROR;
        }
        filename = token;

        if (game_game_management_save(game, filename) == ERROR) {
                return ERROR;
        }

        game_set_finished(game, TRUE);
        return OK;
}

Status game_actions_load(Game *game) {
        char *command_string = NULL;
        char *token = NULL;
        char *filename = NULL;
        char command_copy[MAX_BUFFER];

        if (!game) {
                return ERROR;
        }

        strcpy(command_string, command_get_string_code(game_get_last_command(game)));
        if (strcpy(command_string, command_get_string_code(game_get_last_command(game))) != 0) {
                return ERROR;
        }

        strncpy(command_copy, command_string, sizeof(command_copy) - 1);
        command_copy[sizeof(command_copy) - 1] = '\0';

        token = strtok(command_copy, " ");
        if (!token || strcmp(token, "load") != 0) {
                return ERROR;
        }
        token = strtok(NULL, " ");
        if (!token) {
                return ERROR;
        }
        filename = token;

        if (game_game_management_load(game, filename) == ERROR) {
                return ERROR;
        }

        return OK;
}
