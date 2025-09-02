/**
 * @brief It defines the command interpreter
 *
 * @file command.h
 * @author Abraham Martín
 * @version 4.0
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
/**
 * @def N_CMDT
 * @brief Defines the number of command types
 */
#define N_CMDT 2

/**
 * @def N_CMD
 * @brief Defines the number of available commands
 */
#define N_CMD 15

/**
 * @brief CommandType
 *
 * This struct stores all the information related to a CommandType.
 */
typedef enum { CMDS, CMDL } CommandType;

/**
 * @brief CommandCode
 *
 * This struct stores all the information related to a commandCode.
 */
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, TAKE, DROP, CHAT, ATTACK, MOVE, INSPECT, USE, RECRUIT, ABANDON, OPEN, SAVE, LOAD } CommandCode;

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
typedef struct _Command Command;

/**
 * @brief Allocates memory for a new command
 * @author Abraham Martín
 *
 * @return Pointer to the Command created
 */
Command* command_create(void);

/**
 * @brief Frees up the memory for a command
 * @author Abraham Martín
 *
 * @param command Pointer to a Command to be destroyed
 * @return OK if the command was destroyed, ERROR otherwise
 */
Status command_destroy(Command* command);

/**
 * @brief Sets de code of a command
 * @author Abraham Martín
 *
 * @param command Command that has to be set and the code to set it
 * @param code to set in command
 * @return OK if the code was set and ERROR otherwise
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Gets the code of a given command
 * @author Abraham Martín
 *
 * @param command Command from which to get the code
 * @return The code if everything goes well and NO_CMD if there was a mistake
 */
CommandCode command_get_code(const Command* command);

/**
 * @brief Gets the string version of the code of a given command
 * @author Abraham Martín
 *
 * @param command Command from which to get the code
 * @return The string_code if everything goes well and NO_CMD if there was a mistake
 */
const char* command_get_string_code(const Command* command);

/**
 * @brief Sets the status field of a given command
 * @author Abraham Martín
 *
 * @param command Pointer to a command from which to get the code
 * @param status The status to which to set the command's field
 * @return OK if the field could be set, or ERROR otherwise
 */
Status command_set_success(Command* command, Status status);

/**
 * @brief Gets the status field of a given command
 * @author Abraham Martín
 *
 * @param command Command from which to get the Status field
 * @return The status field of a given command or ERROR if something went wrong
 */
Status command_get_success(const Command* command);

/**
 * @brief Gets the input the user entered
 * @author Abraham Martín
 *
 * @param command Command to store the input
 * @return OK if it could get the input, and ERROR otherwise
 */
Status command_get_user_input(Command* command);

/**
 * @brief Sets the arg field of a given command
 * @author Abraham Martín
 *
 * @param command Command to store the input
 * @param arg string that stores the argumnent of a command
 * @return OK if it could set the argument of the command, or ERROR otherwise
 */
Status command_set_arg(Command* command, char* arg);

/**
 * @brief Gets the argument's field of a given command
 * @author Abraham Martín
 *
 * @param command Command to store the input
 * @return String containing the argument of the given command
 */
const char* command_get_arg(const Command* command);

/**
 * @brief Shows all the information of a given command
 * @author Abraham Martín
 *
 * @param command Command to store the input
 */
void command_print(const Command* command);

#endif
