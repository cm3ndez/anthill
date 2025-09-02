/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Abraham Martín
 * @version 6.0
 * @date 03-04-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

/**
 * @def WIDTH_MAP
 * @brief Defines map width
 */
#define WIDTH_MAP 75

/**
 * @def WIDTH_DES
 * @brief Defines description width
 */
#define WIDTH_DES 90

/**
 * @def WIDTH_BAN
 * @brief Defines banner width
 */
#define WIDTH_BAN 23

/**
 * @def HEIGHT_MAP
 * @brief Defines map height
 */
#define HEIGHT_MAP 36

/**
 * @def HEIGHT_BAN
 * @brief Defines banner height
 */
#define HEIGHT_BAN 1

/**
 * @def HEIGHT_HLP
 * @brief Defines help height
 */
#define HEIGHT_HLP 2

/**
 * @def HEIGHT_FDB
 * @brief Defines feedback height
 */
#define HEIGHT_FDB 3

/**
 * @def EMPTY_INNER_ROW
 * @brief Defines an empty row for gdesc
 */
#define EMPTY_INNER_ROW "                 "

/**
 * @def EMPTY_LONG_ROW
 * @brief Defines an empty long row for gdesc
 */
#define EMPTY_LONG_ROW "                   "

/**
 * @def FLOOR_ROOF
 * @brief Defines a dashed row for gdesc
 */
#define FLOOR_ROOF "+-----------------+"

/**
 * @def WALL
 * @brief Defines a wall symbol
 */
#define WALL "|"

/**
 * @def EMPTY
 * @brief Defines a spacebar
 */
#define EMPTY " "

/**
 * @def ONE
 * @brief Defines the number 1 for general use
 */
#define ONE 1

/**
 * @def AUX_LENGTH
 * @brief Defines the length for a general purpose buffer
 */
#define AUX_LENGTH 17

/**
 * @def LEFT_ARROW
 * @brief Defines a left direction symbol.
 */
#define LEFT_ARROW "<"

/**
 * @def RIGHT_ARROW
 * @brief Defines a right direction symbol.
 */
#define RIGHT_ARROW ">"

/**
 * @def UP_ARROW
 * @brief Defines an up direction symbol.
 */
#define UP_ARROW "^"

/**
 * @def DOWN_ARROW
 * @brief Defines a down direction symbol.
 */
#define DOWN_ARROW "v"

/**
 * @brief _Graphic_engine private struct
 * */

struct _Graphic_engine {
        Area *map /**< Map region pointer*/, *descript /**< Descript region pointer*/, *banner /**< Banner region pointer*/,
            *help /**< Help region pointer*/, *feedback /**< Feedback region pointer*/;
};

Graphic_engine *graphic_engine_create(void) {
        static Graphic_engine *ge = NULL;
        if (ge) {
                return ge;
        }

        screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
        ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
        if (ge == NULL) {
                return NULL;
        }

        ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
        ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
        ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
        ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
        ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

        return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
        if (!ge) return;

        screen_area_destroy(ge->map);
        screen_area_destroy(ge->descript);
        screen_area_destroy(ge->banner);
        screen_area_destroy(ge->help);
        screen_area_destroy(ge->feedback);

        screen_destroy();
        free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
        int i;
        Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID;
        Space *space_act = NULL, *space_left = NULL, *space_right = NULL, *space_back = NULL, *space_next = NULL;
        char str[WORD_SIZE], *toks;
        CommandCode last_cmd = UNKNOWN;
        extern char *cmd_to_str[N_CMD][N_CMDT];
        Status status = ERROR;
        char l_walls[ONE + 1], r_walls[ONE + 1], aux1[AUX_LENGTH + 1], aux2[AUX_LENGTH + 1], aux3[AUX_LENGTH + 1];
        char aux4[AUX_LENGTH + 1], aux5[AUX_LENGTH + 1], aux6[AUX_LENGTH + 1];
        char *gdesc = NULL;
        char *gdesc_act = NULL;
        char *gdesc_left = NULL;
        char *gdesc_right = NULL;

        /* Paint the in the map area */
        screen_area_clear(ge->map);
        if ((id_act = game_get_player_location((const Game *)game)) != NO_ID) {
                space_act = game_get_space((const Game *)game, id_act);
                id_back = game_get_connection((const Game *)game, id_act, N);
                id_next = game_get_connection((const Game *)game, id_act, S);
                id_right = game_get_connection((const Game *)game, id_act, E);
                id_left = game_get_connection((const Game *)game, id_act, W);

                if (id_back != NO_ID) {
                        space_back = game_get_space((const Game *)game, id_back);
                        gdesc = (char *)character_get_gdesc(game_get_enemy_character_at_space((const Game *)game, (int)id_back));

                        if (space_get_discovered(game_get_space((const Game *)game, id_back)) == TRUE) {
                                sprintf(str, "         %s%s %s", EMPTY_LONG_ROW, FLOOR_ROOF, EMPTY_LONG_ROW);
                                screen_area_puts(ge->map, str);
                                sprintf(str, "        %s |  %11s %3d|%s", EMPTY_LONG_ROW, gdesc == NULL ? "" : gdesc,
                                        (int)id_back, EMPTY_LONG_ROW);

                                screen_area_puts(ge->map, str);
                        }

                        aux1[0] = '\0';
                        aux2[0] = '\0';

                        game_get_players_row_at_space((const Game *)game, id_back, aux1, aux2);
                        sprintf(str, "         %s|%s|%s", EMPTY_LONG_ROW,
                                (strcasecmp(aux1, "                  ") == 0) ? "                  " : aux1, EMPTY_LONG_ROW);

                        screen_area_puts(ge->map, str);
                        sprintf(str, "         %s|%s|%s", EMPTY_LONG_ROW,
                                (strcasecmp(aux1, "                  ") == 0) ? "                  " : aux2, EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);

                        for (i = 0; i < GDESC_LINES; i++) {
                                sprintf(str, "         %s|    %s    |%s", EMPTY_LONG_ROW,
                                        space_get_gdesc((const Space *)space_back, i), EMPTY_LONG_ROW);
                                screen_area_puts(ge->map, str);
                        }
                        strcpy(aux1, EMPTY);
                        game_get_object_list_at_space((const Game *)game, id_back, aux1);
                        sprintf(str, "         %s|%-17s| %s", EMPTY_LONG_ROW, aux1, EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);
                        sprintf(str, "         %s%s %s", EMPTY_LONG_ROW, FLOOR_ROOF, EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);
                        sprintf(str, "         %s         %s", EMPTY_LONG_ROW,
                                game_connection_is_open((const Game *)game, id_act, N) == TRUE ? UP_ARROW : EMPTY);
                        screen_area_puts(ge->map, str);
                } else {
                        for (i = 0; i < GDESC_LINES + 7; i++) {
                                sprintf(str, "         %s %s %s", EMPTY_LONG_ROW, EMPTY_LONG_ROW, EMPTY_LONG_ROW);
                                screen_area_puts(ge->map, str);
                        }
                }

                if (id_act != NO_ID) {
                        space_left = game_get_space((const Game *)game, id_left);
                        space_right = game_get_space((const Game *)game, id_right);
                        if (space_left) {
                                strcpy(l_walls, WALL);
                                sprintf(aux1, "%d", (int)id_left);
                        } else {
                                strcpy(l_walls, EMPTY);
                                strcpy(aux1, EMPTY);
                        }
                        if (space_right) {
                                strcpy(r_walls, WALL);
                                sprintf(aux2, "%d", (int)id_right);
                        } else {
                                strcpy(r_walls, EMPTY);
                                strcpy(aux2, EMPTY);
                        }
                        sprintf(str, "        %s %s %s ", space_left ? FLOOR_ROOF : EMPTY_LONG_ROW, FLOOR_ROOF,
                                space_right ? FLOOR_ROOF : EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);
                        gdesc_left = (char *)character_get_gdesc(game_get_enemy_character_at_space((const Game *)game, id_left));
                        gdesc_act = (char *)character_get_gdesc(game_get_enemy_character_at_space((const Game *)game, id_act));
                        gdesc_right =
                            (char *)character_get_gdesc(game_get_enemy_character_at_space((const Game *)game, id_right));

                        if (space_get_discovered(game_get_space((const Game *)game, id_act)) == TRUE) {
                                sprintf(str, "        %s       %6s %3s%s |%6s %6s %3d| %s       %6s %3s%s", l_walls,
                                        gdesc_left == NULL ? "" : gdesc, aux1, l_walls,
                                        game_get_current_player_gdesc((const Game *)game), gdesc_act == NULL ? "" : gdesc_act,
                                        (int)id_act, r_walls, gdesc_right == NULL ? "" : gdesc_right, aux2, r_walls);
                        }
                        screen_area_puts(ge->map, str);

                        /*Print de los players*/
                        /*Players de la izquierda*/
                        aux1[0] = '\0';
                        aux2[0] = '\0';
                        game_get_players_row_at_space((const Game *)game, id_left, aux1, aux2);
                        /*Players de la actual*/
                        aux3[0] = '\0';
                        aux4[0] = '\0';
                        game_get_players_row_at_space((const Game *)game, id_act, aux3, aux4);
                        /*Players de la derecha*/
                        aux5[0] = '\0';
                        aux6[0] = '\0';
                        game_get_players_row_at_space((const Game *)game, id_right, aux5, aux6);

                        sprintf(str, "        %s%s%s |%s| %s%s%s", l_walls,
                                ((strcasecmp(aux1, "                 ") == 0) || (strcasecmp(aux1, "   |   |   |   | ") == 0))
                                    ? "                 "
                                    : aux1,
                                l_walls,
                                ((strcasecmp(aux3, "                 ") == 0) || (strcasecmp(aux3, "   |   |   |   | ") == 0))
                                    ? "                 "
                                    : aux3,
                                r_walls,
                                ((strcasecmp(aux5, "                 ") == 0) || (strcasecmp(aux5, "   |   |   |   | ") == 0))
                                    ? "                 "
                                    : aux5,
                                r_walls);

                        screen_area_puts(ge->map, str);
                        sprintf(str, "        %s%s%s |%s| %s%s%s", l_walls,
                                ((strcasecmp(aux2, "                 ") == 0) || (strcasecmp(aux2, "   |   |   |     ") == 0))
                                    ? "                 "
                                    : aux2,
                                l_walls,
                                ((strcasecmp(aux4, "                 ") == 0) || (strcasecmp(aux4, "   |   |   |     ") == 0))
                                    ? "                 "
                                    : aux4,
                                r_walls,
                                ((strcasecmp(aux6, "                 ") == 0) || (strcasecmp(aux6, "   |   |   |     ") == 0))
                                    ? "                 "
                                    : aux6,
                                r_walls);

                        screen_area_puts(ge->map, str);

                        for (i = 0; i < GDESC_LINES; i++) {
                                sprintf(
                                    str, "        %s  %-15s%s%s|    %s    |%s%s    %s    %s", l_walls,
                                    space_get_gdesc((const Space *)space_left, i), l_walls,
                                    i == 1 && game_connection_is_open((const Game *)game, id_act, W) == TRUE ? LEFT_ARROW : EMPTY,
                                    space_get_gdesc((const Space *)space_act, i),
                                    i == 1 && game_connection_is_open((const Game *)game, id_act, E) == TRUE ? RIGHT_ARROW
                                                                                                             : EMPTY,
                                    r_walls, space_get_gdesc((const Space *)space_right, i), r_walls);
                                screen_area_puts(ge->map, str);
                        }
                        strcpy(aux1, EMPTY);
                        strcpy(aux2, EMPTY);
                        strcpy(aux3, EMPTY);
                        game_get_object_list_at_space((const Game *)game, id_left, aux1);
                        game_get_object_list_at_space((const Game *)game, id_act, aux2);
                        game_get_object_list_at_space((const Game *)game, id_right, aux3);
                        sprintf(str, "        %s%-17s%s |%-17s| %s%-17s%s", l_walls, aux1, l_walls, aux2, r_walls, aux3, r_walls);
                        screen_area_puts(ge->map, str);
                        sprintf(str, "        %s %s %s", space_left ? FLOOR_ROOF : EMPTY_LONG_ROW, FLOOR_ROOF,
                                space_right ? FLOOR_ROOF : EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);
                }

                if (id_next != NO_ID) {
                        sprintf(str, "           %s       %s", EMPTY_LONG_ROW,
                                game_connection_is_open((const Game *)game, id_act, S) == TRUE ? DOWN_ARROW : EMPTY);
                        screen_area_puts(ge->map, str);
                        space_next = game_get_space((const Game *)game, id_next);
                        sprintf(str, "         %s%s %s", EMPTY_LONG_ROW, FLOOR_ROOF, EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);

                        /*if (space_get_discovered(space_next) == TRUE) {
                                sprintf(str, "        %s |       %6s %3d| %s", EMPTY_LONG_ROW,
                                        character_get_gdesc(game_get_enemy_character_at_space((const Game *)game, id_next)),
                                        (int)id_next, EMPTY_LONG_ROW);
                                screen_area_puts(ge->map, str);
                        }*/

                        gdesc = (char *)character_get_gdesc(game_get_enemy_character_at_space((const Game *)game, (int)id_back));

                        if (space_get_discovered(game_get_space((const Game *)game, id_next)) == TRUE) {
                                sprintf(str, "        %s |  %11s %3d|%s", EMPTY_LONG_ROW, gdesc == NULL ? "" : gdesc,
                                        (int)id_next, EMPTY_LONG_ROW);

                                screen_area_puts(ge->map, str);
                        }

                        aux1[0] = '\0';
                        aux2[0] = '\0';
                        game_get_players_row_at_space((const Game *)game, id_next, aux1, aux2);

                        sprintf(str, "         %s|%s|%s", EMPTY_LONG_ROW,
                                ((strcasecmp(aux1, "   |   |   |   | ") == 0) || (strcasecmp(aux1, "                 ")) == 0)
                                    ? "                 "
                                    : aux1,
                                EMPTY_LONG_ROW);

                        screen_area_puts(ge->map, str);
                        sprintf(str, "         %s|%s|%s", EMPTY_LONG_ROW,
                                ((strcasecmp(aux2, "   |   |   |     ") == 0) || (strcasecmp(aux2, "                 ")) == 0)
                                    ? "                 "
                                    : aux2,
                                EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);

                        for (i = 0; i < GDESC_LINES; i++) {
                                sprintf(str, "         %s|    %s    |%s", EMPTY_LONG_ROW,
                                        space_get_gdesc((const Space *)space_next, i), EMPTY_LONG_ROW);
                                screen_area_puts(ge->map, str);
                        }
                        strcpy(aux1, EMPTY);
                        game_get_object_list_at_space((const Game *)game, id_next, aux1);
                        sprintf(str, "         %s|%-17s| %s", EMPTY_LONG_ROW, aux1, EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);
                        sprintf(str, "         %s%s %s", EMPTY_LONG_ROW, FLOOR_ROOF, EMPTY_LONG_ROW);
                        screen_area_puts(ge->map, str);
                } else {
                        for (i = 0; i < GDESC_LINES + 7; i++) {
                                sprintf(str, "        %s %s %s", EMPTY_LONG_ROW, EMPTY_LONG_ROW, EMPTY_LONG_ROW);
                                screen_area_puts(ge->map, str);
                        }
                }
        }

        /* Paint in the description area */
        screen_area_clear(ge->descript);

        game_get_info((const Game *)game, str);
        toks = strtok(str, "|\n");
        while (toks) {
                screen_area_puts(ge->descript, toks);
                toks = strtok(NULL, "|\n");
        }

        /* Paint in the banner area */
        screen_area_puts(ge->banner, "    The anthill game ");

        /* Paint in the help area */
        screen_area_clear(ge->help);
        sprintf(str, " The commands you can use are:");
        screen_area_puts(ge->help, str);
        sprintf(str,
                "move or m, take or t, drop or d, inspect or i, attack or a, use or u, recruit or r, abandon or ab, open or o, "
                "chat or c, load or l, save or s exit or e.");
        screen_area_puts(ge->help, str);

        /* Paint in the feedback area */
        last_cmd = command_get_code(game_get_last_command((const Game *)game));
        status = command_get_success(game_get_last_command((const Game *)game));
        sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS],
                status == 1 ? "OK" : "ERROR");
        screen_area_puts(ge->feedback, str);

        /* Dump to the terminal */
        screen_paint(game_get_current_turn((const Game *)game));
        if (!(game_get_finished((const Game *)game)) && last_cmd != EXIT) printf("prompt:> ");
}
