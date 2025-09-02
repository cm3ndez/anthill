/**
 * @brief It implements the load of the spaces, players, objects, characters and links
 * and asigns them their vaules according to the file. It also saves the game progress if its indicated
 *
 * @file game_management.c
 * @author Jorge Ochoa
 * @version 4.0
 * @date 01-05-2025
 * @copyright GNU Public License
 */

#include "game_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def EMPTY_LINE
 * @brief Defines an empty row for gdesc
 */
#define EMPTY_LINE "         \0"

/**
 * @def EMPTY_LINE
 * @brief Defines an empty row for gdesc
 */
#define EMPTY_LINE "         \0"

Status game_management_load_spaces(Game **game, char *file) {
        int i;
        char line[WORD_SIZE] = "";
        char *toks = NULL;
        Space *space = NULL;
        Id id = NO_ID;
        char name[WORD_SIZE] = "";
        Bool discovered;
        char gdesc[GDESC_LINES][LINE_LENGTH + 1];
        FILE *f = NULL;

        /* Error control */
        if ((!file) || (!game)) {
                return ERROR;
        }

        f = fopen(file, "r");
        if (!f) {
                return ERROR;
        }

        while (fgets(line, WORD_SIZE, f)) {
                if (strncmp("#s:", line, 3) == 0) {
                        /*id*/
                        toks = strtok(line + 3, "|\n");
                        if (!toks) return ERROR;
                        id = atol(toks);

                        /*names*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        strcpy(name, toks);

                        /*Discovered*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        discovered = atoi(toks);

                        /*gdesc*/
                        for (i = 0; i < GDESC_LINES; i++) {
                                toks = strtok(NULL, "|\n");
                                if (!toks) {
                                        strcpy(gdesc[i], EMPTY_LINE);
                                } else {
                                        strcpy(gdesc[i], toks);
                                } /* || strlen(toks) != LINE_LENGTH*/
                        }

#ifdef DEBUG
                        printf("Leido: %ld|%s|%u|%s|%s|%s|%s|%s|%s|%s|%s|\n", id, name, discovered, gdesc[0], gdesc[1], gdesc[2],
                               gdesc[3], gdesc[4], gdesc[5], gdesc[6], gdesc[7]);
#endif

                        space = space_create(id);
                        if (space) {
                                if (space_set_name(space, name) != OK || space_set_discovered(space, discovered) != OK ||
                                    space_set_gdesc(space, gdesc) != OK || game_add_space(*game, space) != OK) {
                                        space_destroy(space);
                                        return ERROR;
                                }
                        }
                }
        }

        if (ferror(f)) {
                fclose(f);
                return ERROR;
        }

        fclose(f);

        return OK;
}

Status game_management_load_objects(Game **game, char *file) {
        char line[WORD_SIZE] = "";
        char name[WORD_SIZE] = "";
        char description[WORD_SIZE] = "";
        char *toks = NULL;
        Id id = NO_ID, dependency = NO_ID, open = NO_ID, obj_loc = NO_ID;
        Object *object = NULL;
        int health = 0;
        Bool movable;
        FILE *f = NULL;

        /* Error control */
        if ((!file) || (!game)) {
                return ERROR;
        }

        f = fopen(file, "r");
        if (f == NULL) {
                return ERROR;
        }

        while (fgets(line, WORD_SIZE, f)) {
                if (strncmp("#o:", line, 3) == 0) {
                        /*id*/
                        toks = strtok(line + 3, "|\n");
                        if (!toks) return ERROR;
                        id = atol(toks);

                        /*name*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        strcpy(name, toks);

                        /*location*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        obj_loc = atol(toks);

                        /*description*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        strcpy(description, toks);

                        /*health*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        health = atoi(toks);

                        /*movable*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        movable = atoi(toks);

                        /*dependecy*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        dependency = atol(toks);

                        /*open*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        open = atol(toks);

#ifdef DEBUG
                        printf("Leído: %ld|%s|%ld|%s|%d|%u|%ld|%ld|\n", id, name, obj_loc, description, health, movable,
                               dependency, open);
#endif

                        object = object_create(id);
                        if (object) {
                                if ((object_set_name(object, name) != OK) ||
                                    (space_add_object(game_get_space(*game, obj_loc), id) != OK) ||
                                    (object_set_description(object, description) != OK) ||
                                    (object_set_health(object, health) != OK) || (object_set_movable(object, movable) != OK) ||
                                    (object_set_dependency(object, dependency) != OK) || (object_set_open(object, open) != OK)) {
                                        object_destroy(object);
                                        return ERROR;
                                }

                                if (game_add_object(*game, object) != OK) {
                                        object_destroy(object);
                                        return ERROR;
                                }
                        }
                }
        }

        if (ferror(f)) {
                fclose(f);
                return ERROR;
        }

        fclose(f);

        return OK;
}

Status game_management_load_characters(Game **game, char *file) {
        char line[WORD_SIZE] = "";
        char name[WORD_SIZE] = "";
        char message[WORD_SIZE] = "";
        char *toks = NULL;
        Id id = NO_ID, following = NO_ID, loc = NO_ID;
        Character *character = NULL;
        Bool friendly = FALSE;
        int health = 0;
        char gdesc[WORD_SIZE] = "";
        FILE *f = NULL;

        /* Error control */
        if ((!file) || (!game)) {
                return ERROR;
        }

        f = fopen(file, "r");
        if (f == NULL) {
                return ERROR;
        }

        while (fgets(line, WORD_SIZE, f)) {
                if (strncmp("#c:", line, 3) == 0) {
                        /* id */
                        toks = strtok(line + 3, "|\n");
                        if (!toks) return ERROR;
                        id = atol(toks);

                        /* name */
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        strcpy(name, toks);

                        /* location */
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        loc = atol(toks);

                        /* friendly */
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        friendly = atoi(toks);

                        /* health */
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        health = atoi(toks);

                        /* gdesc */
                        toks = strtok(NULL, "|\n");
                        if (!toks || strlen(toks) > GDESC_SIZE) return ERROR;
                        strcpy(gdesc, toks);

                        /* message */
                        toks = strtok(NULL, "|\n");
                        if (toks) {
                                strcpy(message, toks);
                        } else {
                                strcpy(message, "");
                        }

                        /* following */
                        toks = strtok(NULL, "|\n");
                        if (toks) {
                                following = atol(toks);
                        } else {
                                following = NO_ID;
                        }

#ifdef DEBUG
                        printf("Leído: %ld|%s|%ld|%d|%d|%s|%s|%ld|\n", id, name, loc, friendly, health, gdesc, message,
                               following);
#endif

                        character = character_create(id);
                        if (character != NULL) {
                                if ((character_set_name(character, name) != OK) ||

                                    (character_set_friendly(character, friendly) != OK) ||
                                    (character_set_health(character, health) != OK) ||
                                    (character_set_gdesc(character, gdesc) != OK) ||
                                    (character_set_message(character, message) != OK) ||
                                    (character_set_following(character, following) != OK) ||
                                    (game_add_character(*game, character) != OK)) {
                                        character_destroy(character);
                                        return ERROR;
                                }

                                if ((space_add_character(game_get_space(*game, loc), id) != OK)) {
                                        character_destroy(character);
                                        return ERROR;
                                }
                        }
                }
        }

        if (ferror(f)) {
                fclose(f);
                return ERROR;
        }

        fclose(f);

        return OK;
}

Status game_management_load_links(Game **game, char *file) {
        char line[WORD_SIZE] = "";
        char name[WORD_SIZE] = "";
        char *toks = NULL;
        Id id = NO_ID, orig_id = NO_ID, dest_id = NO_ID;
        Bool open = FALSE;
        Direction direction = NO_DIRECTION;
        Link *link = NULL;
        FILE *f = NULL;

        /* Error control */
        if ((!file) || (!game)) {
                return ERROR;
        }

        f = fopen(file, "r");
        if (f == NULL) {
                return ERROR;
        }

        while (fgets(line, WORD_SIZE, f)) {
                /*#l:57|Passage|19|25|1|1|*/
                if (strncmp("#l:", line, 3) == 0) {
                        /*id*/
                        toks = strtok(line + 3, "|\n");
                        if (!toks) return ERROR;
                        id = atol(toks);

                        /*name*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        strcpy(name, toks);

                        /*origin*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        orig_id = atol(toks);

                        /*destination*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        dest_id = atol(toks);

                        /*direction*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        direction = atoi(toks);

                        /*open*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        open = atoi(toks);

#ifdef DEBUG
                        printf("Leído: %ld|%s|%ld|%ld|%d|%d|\n", id, name, orig_id, dest_id, direction, open);
#endif

                        link = link_create(id);
                        if (link != NULL) {
                                if ((link_set_name(link, name) != OK) || (link_set_origin(link, orig_id) != OK) ||
                                    (link_set_destination(link, dest_id) != OK) || (link_set_direction(link, direction) != OK) ||
                                    (link_set_open(link, open) != OK) || (game_add_link(*game, link) != OK)) {
                                        link_destroy(link);
                                        return ERROR;
                                }
                        }
                }
        }
        if (ferror(f)) {
                fclose(f);
                return ERROR;
        }

        fclose(f);

        return OK;
}

Status game_management_load_players(Game **game, char *file) {
        char line[WORD_SIZE] = "";
        char name[WORD_SIZE] = "";
        char *toks = NULL;
        char gdesc[P_GDESC_LENGTH + 1];
        int health, backpack_size;
        Id id = NO_ID, loc_id = NO_ID;
        Player *player = NULL;
        Space *space = NULL;
        FILE *f = NULL;

        /* Error control */
        if ((!file) || (!game)) {
                return ERROR;
        }

        f = fopen(file, "r");
        if (f == NULL) {
                return ERROR;
        }

        while (fgets(line, WORD_SIZE, f)) {
                /*#p:2|mouse|_Oo|01|5|3| */
                if (strncmp("#p:", line, 3) == 0) {
                        /*id*/
                        toks = strtok(line + 3, "|\n");
                        if (!toks) return ERROR;
                        id = atol(toks);

                        /*name*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        strcpy(name, toks);

                        /*gdesc*/
                        toks = strtok(NULL, "|\n");
                        if (!toks || strlen(toks) > P_GDESC_LENGTH) return ERROR;
                        strcpy(gdesc, toks);

                        /*loc_id*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        loc_id = atol(toks);

                        /*space*/
                        space = game_get_space((const Game *)(*game), loc_id);
                        if (!space) return ERROR;

                        /*health*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        health = atoi(toks);

                        /*backpack_size*/
                        toks = strtok(NULL, "|\n");
                        if (!toks) return ERROR;
                        backpack_size = atoi(toks);

#ifdef DEBUG
                        printf("Leído: %ld|%s|%s|%ld|%d|%d|\n", id, name, gdesc, loc_id, health, backpack_size);
#endif

                        player = player_create(id);
                        if (player != NULL) {
                                if ((player_set_name(player, name) != OK) || (player_set_gdesc(player, gdesc) != OK) ||
                                    (player_set_location(player, loc_id) != OK) || (player_set_health(player, health) != OK) ||
                                    (player_set_backpack_size(player, backpack_size) != OK) ||
                                    (game_add_player(*game, player) != OK)) {
                                        player_destroy(player);
                                        fclose(f);
                                        return ERROR;
                                } else {
                                        space_set_discovered(space, TRUE);
                                }
                        } else {
                                fclose(f);
                                return ERROR;
                        }
                }
        }
        if (ferror(f)) {
                fclose(f);
                return ERROR;
        }

        fclose(f);

        return OK;
}

Status game_management_save(Game **game, const char *filename) {
        FILE *file = NULL;
        Space *space = NULL;
        Link *link = NULL;
        Object *object = NULL;
        Character *character = NULL;
        Player *player = NULL;
        int i = 0;

        if (!game || !filename) {
                return ERROR;
        }

        file = fopen(filename, "w");
        if (file == NULL) {
                return ERROR;
        }
        /*Save turn*/
        fprintf(file, "#t: %d", game_get_current_turn(*game));

        /*Crear spaces*/
        for (i = 0; i < game_get_n_spaces(*game); i++) {
                space = game_get_space_from_index(*game, i);
                fprintf(file, "#s: %ld|%s|%c|%s|%s|%s|%s|%s|%s|%s|%s|\n", space_get_id(space), space_get_name(space),
                        space_get_discovered(space), space_get_gdesc(space, 0), space_get_gdesc(space, 1),
                        space_get_gdesc(space, 2), space_get_gdesc(space, 3), space_get_gdesc(space, 4),
                        space_get_gdesc(space, 5), space_get_gdesc(space, 6), space_get_gdesc(space, 7));
        }

        /*Crear links*/
        for (i = 0; i < game_get_n_links(*game); i++) {
                link = game_get_link_from_index(*game, i);
                fprintf(file, "#l:%ld|%s|%ld|%ld|%d|%d|\n", link_get_id(link), link_get_name(link), link_get_origin(link),
                        link_get_destination(link), link_get_direction(link), link_get_open(link));
        }

        /*Crear objects*/
        for (i = 0; i < game_get_n_objects(*game); i++) {
                object = game_get_object_from_index(*game, i);
                fprintf(file, "#o:%ld|%s|%ld|%s|%d|%d|%ld|%ld|\n", object_get_id(object), object_get_name(object),
                        game_get_object_location(*game, object_get_id(object)), object_get_description(object),
                        object_get_health(object), object_get_movable(object), object_get_dependency(object),
                        object_get_open(object));
        }

        /*Crear characters*/
        for (i = 0; i < game_get_n_characters(*game); i++) {
                character = game_get_character_from_index(*game, i);
                fprintf(file, "#e:%ld|%s|%d|%d|%s|%s|%ld|\n", character_get_id(character), character_get_name(character),
                        character_get_friendly(character), character_get_health(character), character_get_gdesc(character),
                        character_get_message(character), character_get_following(character));
        }

        /*Crear players*/
        for (i = 0; i < game_get_n_players(*game); i++) {
                player = game_get_player_from_index(*game, i);
                fprintf(file, "#p:%ld|%s|%ld|%d|%d|\n", player_get_id(player), player_get_name(player),
                        game_get_player_location(*game), player_get_health(player), player_get_num_objects(player));
        }

        fclose(file);
        return OK;
}

Status game_management_load_game_from_file(Game **game, char *filename) {
        if (!game) {
                return ERROR;
        }

        if (game_management_load_spaces(game, filename) == ERROR) {
                return ERROR;
        }
        if (game_management_load_players(game, filename) == ERROR) {
                return ERROR;
        }
        if (game_management_load_objects(game, filename) == ERROR) {
                return ERROR;
        }
        if (game_management_load_characters(game, filename) == ERROR) {
                return ERROR;
        }
        if (game_management_load_links(game, filename) == ERROR) {
                return ERROR;
        }

        return OK;
}

Status game_management_load(Game **game, const char *file) {
        FILE *f = NULL;
        char line[MAX_LINES];
        char *toks = NULL;
        Character *character = NULL;
        Player *player = NULL;
        Object *object = NULL;
        Link *link = NULL;
        Space *space = NULL;

        int turn = 0;
        Id following, id, friendly, loc_id, dependency, open, orig_id, dest_id;
        int health, backpack_size, i;
        char name[WORD_SIZE];
        char gdesc[WORD_SIZE];
        char gdesc_spaces[GDESC_LINES][LINE_LENGTH + 1];
        char message[MAX_LINES];
        Bool movable, discovered;
        Direction direction;

        if (!game || !file) {
                return ERROR;
        }

        f = fopen(file, "r");
        if (!f) {
                return ERROR;
        }

        while (fgets(line, sizeof(line), f)) {
                if (line[0] == '#') {
                        switch (line[1]) {
                                case 't': {
                                        sscanf(line, "#t:%d", &turn);
                                        game_set_turn(*game, turn);
                                        break;
                                }
                                case 's': {
                                        toks = strtok(line + 3, "|\n");
                                        if (!toks) return ERROR;
                                        id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        strcpy(name, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        discovered = atoi(toks);
                                        for (i = 0; i < GDESC_LINES; i++) {
                                                toks = strtok(NULL, "|\n");
                                                if (!toks || strlen(toks) != LINE_LENGTH) {
                                                        strcpy(gdesc_spaces[i], EMPTY_LINE);
                                                } else {
                                                        strcpy(gdesc_spaces[i], toks);
                                                }
                                        }
                                        space = game_get_space(*game, id);
                                        space_set_name(space, name);
                                        space_set_discovered(space, discovered);
                                        space_set_gdesc(space, gdesc_spaces);
                                        break;
                                }
                                case 'p': {
                                        toks = strtok(line + 3, "|\n");
                                        if (!toks) return ERROR;
                                        id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        strcpy(name, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks || strlen(toks) > P_GDESC_LENGTH) return ERROR;
                                        strcpy(gdesc, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        loc_id = atol(toks);
                                        space = game_get_space(*game, loc_id);
                                        if (!space) return ERROR;
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        health = atoi(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        backpack_size = atoi(toks);
                                        player = game_get_player_from_id(*game, id);
                                        player_set_name(player, name);
                                        player_set_location(player, loc_id);
                                        player_set_health(player, health);
                                        player_set_gdesc(player, gdesc);
                                        player_set_backpack_size(player, backpack_size);
                                        break;
                                }
                                case 'o': {
                                        toks = strtok(line + 3, "|\n");
                                        if (!toks) return ERROR;
                                        id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        strcpy(name, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        strcpy(gdesc, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        health = atoi(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        movable = atoi(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        dependency = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        open = atol(toks);
                                        object = game_get_object_from_id(*game, id);
                                        object_set_name(object, name);
                                        object_set_description(object, gdesc);
                                        object_set_health(object, health);
                                        object_set_dependency(object, dependency);
                                        object_set_movable(object, movable);
                                        object_set_open(object, open);
                                        break;
                                }
                                case 'c': {
                                        toks = strtok(line + 3, "|\n");
                                        if (!toks) return ERROR;
                                        id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        strcpy(name, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        friendly = atoi(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        health = atoi(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks || strlen(toks) > GDESC_SIZE) return ERROR;
                                        strcpy(gdesc, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (toks) {
                                                strcpy(message, toks);
                                        } else {
                                                strcpy(message, "");
                                        }
                                        toks = strtok(NULL, "|\n");
                                        if (toks) {
                                                following = atol(toks);
                                        } else {
                                                following = NO_ID;
                                        }
                                        character = game_get_character_from_name(*game, name);
                                        character_set_name(character, name);
                                        character_set_gdesc(character, gdesc);
                                        character_set_friendly(character, friendly);
                                        character_set_message(character, message);
                                        character_set_following(character, following);
                                        break;
                                }
                                case 'l': {
                                        toks = strtok(line + 3, "|\n");
                                        if (!toks) return ERROR;
                                        id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        strcpy(name, toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        orig_id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        dest_id = atol(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        direction = atoi(toks);
                                        toks = strtok(NULL, "|\n");
                                        if (!toks) return ERROR;
                                        open = atoi(toks);
                                        link = game_get_link_from_name(*game, name);
                                        link_set_name(link, name);
                                        link_set_origin(link, orig_id);
                                        link_set_destination(link, dest_id);
                                        link_set_direction(link, direction);
                                        break;
                                }
                        }
                }
        }

        fclose(f);
        return OK;
}
