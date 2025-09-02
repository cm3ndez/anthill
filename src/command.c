/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Abraham Martín
 * @version 4.0
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/**
 * @def CMD_LENGTH
 * @brief Defines the length of the command
 */
#define CMD_LENGTH 50

/**
 * @def MAX_ARG
 * @brief Defines the length of the argument
 */
#define MAX_ARG 40

/**
 * @var cmd_to_str[N_CMD][N_CMDT]
 * @brief Array of sort/long versions of each command
 */
char* cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"},   {"e", "Exit"}, {"t", "Take"},    {"d", "Drop"},
                                   {"c", "Chat"},      {"a", "Attack"},   {"m", "Move"}, {"i", "Inspect"}, {"u", "Use"},
                                   {"r", "Recruit"},   {"ab", "Abandon"}, {"o", "Open"}, {"s", "Save"},    {"l", "Load"}};

/**
 * @brief _Command private struct
 * */
struct _Command {
        CommandCode code;                 /**< Name of the command */
        char string_code[CMD_LENGTH + 1]; /**< String version of the code */
        char arg[MAX_ARG + 1];            /**< Argument of the command */
        Status success;                   /**< Success field of the command*/
};

/*
Private functions
*/

/**
 * @brief It resesets all fields in the command
 * @author Carlos Méndez
 *
 * @param command pointer to command to be reset
 * @return void this functions does no return anything
 */
void command_reset(Command* command);

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Command* command_create(void) {
        Command* newCommand = NULL;

        newCommand = (Command*)malloc(sizeof(Command));
        if (newCommand == NULL) {
                return NULL;
        }

        /* Initialization of an empty command*/
        newCommand->code = NO_CMD;
        newCommand->arg[0] = '\0';
        newCommand->success = OK;
        newCommand->string_code[0] = '\0';
        return newCommand;
}

Status command_destroy(Command* command) {
        if (command) free(command);
        return OK;
}

Status command_set_code(Command* command, CommandCode code) {
        if (!command) {
                return ERROR;
        }

        command->code = code;

        return OK;
}

CommandCode command_get_code(const Command* command) {
        if (!command) {
                return NO_CMD;
        }
        return command->code;
}

const char* command_get_string_code(const Command* command) {
        if (!command) return NULL;
        return command->string_code;
}

Status command_set_success(Command* command, Status status) {
        if (!command) return ERROR;
        command->success = status;
        return OK;
}

Status command_get_success(const Command* command) {
        if (!command) return ERROR;
        return command->success;
}

void command_reset(Command* command) {
        if (!command) {
                printf("No hay comando");
                return;
        }

        command->code = NO_CMD;
        strcpy((command->arg), "\0");
        command->string_code[0] = '\0';
        command->success = OK;
}

Status command_get_user_input(Command* command) {
        char input[CMD_LENGTH] = "", *token = NULL;
        int i = UNKNOWN - NO_CMD + 1;
        CommandCode cmd;

        if (!command) {
                return ERROR;
        }

        command_reset(command);

        if (fgets(input, CMD_LENGTH, stdin)) {
                token = strtok(input, " \n");

                if (!token) {
                        return command_set_code(command, UNKNOWN);
                }
                cmd = UNKNOWN;
                while (cmd == UNKNOWN && i < N_CMD) {
                        if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
                                cmd = i + NO_CMD;
                        } else {
                                i++;
                        }
                }

                token = strtok(NULL, " \n");
                if (token) command_set_arg(command, token);

                switch (cmd) {
                        case NO_CMD:
                                strcpy(command->string_code, "no_cmd");
                                break;
                        case UNKNOWN:
                                strcpy(command->string_code, "unknown");
                                break;
                        case EXIT:
                                strcpy(command->string_code, "exit");
                                break;
                        case TAKE:
                                strcpy(command->string_code, "take");
                                break;
                        case DROP:
                                strcpy(command->string_code, "drop");
                                break;
                        case CHAT:
                                strcpy(command->string_code, "chat");
                                break;
                        case ATTACK:
                                strcpy(command->string_code, "attack");
                                break;
                        case MOVE:
                                strcpy(command->string_code, "move");
                                break;
                        case INSPECT:
                                strcpy(command->string_code, "inspect");
                                break;
                        case USE:
                                strcpy(command->string_code, "use");
                                break;
                        case RECRUIT:
                                strcpy(command->string_code, "recruit");
                                break;
                        case ABANDON:
                                strcpy(command->string_code, "abandon");
                                break;
                        case OPEN:
                                strcpy(command->string_code, "open");
                                break;
                        case SAVE:
                                strcpy(command->string_code, "save");
                                break;
                        case LOAD:
                                strcpy(command->string_code, "load");
                                break;
                        default:
                                strcpy(command->string_code, "");
                }
                return command_set_code(command, cmd);
        } else {
                return command_set_code(command, EXIT);
        }
}

Status command_set_arg(Command* command, char* arg) {
        if (!command || !arg) return ERROR;
        strcpy(command->arg, arg);
        return OK;
}

const char* command_get_arg(const Command* command) {
        if (!command) {
                return NULL;
        }
        return command->arg;
}

void command_print(const Command* command) {
        if (!command) return;
        printf("Command code: %d | Command arg: %s | Command status %d\n", command->code, command->arg, command->success);
        return;
}
