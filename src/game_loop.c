/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Abraham Martín
 * @version 4.0
 * @date 04-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_rules.h"
#include "graphic_engine.h"

/**
 * @brief It starts the game, creating, initializing it as well as its graphic engine
 * @author Profesores PPROG
 *
 * @param game Pointer to pointer to the game being created
 * @param gengine Pointer to pointer to graphic engine
 * @param file_name String (the file name)
 * @param deterministic if we activate the deterministic mode or not
 * @return 0 if everyting went well, 1 if there was any error
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name, int deterministic);

/**
 * @brief Implements the basic game loop for the game to run
 * @author Profesores PPROG
 *
 * @param game Pointer to game being played
 * @param gengine Pointer to the graphic engine
 * @param file Name of the file
 */
void game_loop_run(Game *game, Graphic_engine *gengine, char *file);

/**
 * @brief Frees up the memory occupied by the game and everything related to it
 * @author Profesores PPROG
 *
 * @param game Pointer to the game being played
 * @param gengine Pointer to the graphic engine
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 *@brief The main function of the project.
 *
 */
int main(int argc, char *argv[]) {
        Game *game = NULL;
        Graphic_engine *gengine;
        char *file = "invalid_file";
        int deterministic = 0;
        int i;

        if (argc < 2) {
                fprintf(stderr, "Use: %s <game_data_file> [-d] [-l <log_file>]\n", argv[0]);
                return 1;
        }

        for (i = 2; i < argc; i++) {
                if (strcmp(argv[i], "-d") == 0) {
                        deterministic = 1;
                } else if (strcmp(argv[i], "-l") == 0) {
                        if (i + 1 < argc) {
                                file = argv[i + 1];
                                i++;
                        } else {
                                fprintf(stderr, "ERROR, log file undefined after -l\n");
                                return 1;
                        }
                } else {
                        fprintf(stderr, "ERROR, unrecognized argument %s\n", argv[i]);
                        fprintf(stderr, "Valid use: %s <game_data_file> [-d] [-l <log_file>]\n", argv[0]);
                        return 1;
                }
        }

        if (!game_loop_init(&game, &gengine, argv[1], deterministic)) {
                srand(time(NULL));
                game_loop_run(game, gengine, file);
                game_loop_cleanup(game, gengine);
        }

        return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name, int deterministic) {
        /*Error control*/
        if ((!game) || (!gengine) || (!file_name)) {
                fprintf(stderr, "Error while initializing game.\n");
                return 1;
        }
        if (game_create_from_file(game, file_name) == ERROR) {
                fprintf(stderr, "Error while initializing game.\n");
                game_destroy(*game);
                return 1;
        } else {
                printf("Juego creado correctamente");
        }

        game_set_deterministic_mode(*game, deterministic);
        if (deterministic) {
                srand(1);
        } else {
                srand(time(NULL));
        }

        if ((*gengine = graphic_engine_create()) == NULL) {
                fprintf(stderr, "Error while initializing graphic engine.\n");
                game_destroy(*game);
                return 1;
        }

        return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, char *file) {
        Command *last_cmd;
        char arg[WORD_SIZE + 1];

        /*Variables for the game_rules*/
        int turns_passed = 1;
        int times_feeded = 0;
        Bool spider_is_dead = FALSE;

        /*Error control*/
        if (!gengine) {
                return;
        }

        last_cmd = game_get_last_command((const Game *)game);
        strcpy(arg, command_get_arg((const Command *)last_cmd));

        while ((command_get_code(last_cmd) != EXIT) && (game_get_finished((const Game *)game) == FALSE)) {
                graphic_engine_paint_game(gengine, game);
                command_get_user_input(last_cmd);
                game_actions_update(game, last_cmd);
                printf("Comprobando game_rules...\n");
                game_rule_update(game, last_cmd, turns_passed, &times_feeded, &spider_is_dead);
                turns_passed++;
#ifdef DEBUG
                game_print((const Game *)game);
#endif
                game_write_recent_log((const Game *)game, file);
        }

        if (command_get_code(last_cmd) == EXIT) {
                graphic_engine_paint_game(gengine, game);
        }
        if (command_get_code(last_cmd) == ATTACK) {
                graphic_engine_paint_game(gengine, game);
                printf("All the players are dead. Game Over.\n");
        }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
        if (gengine) graphic_engine_destroy(gengine);
        if (game) game_destroy(game);
}
