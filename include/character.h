#ifndef CHARACTER_H
#define CHARACTER_H

/**
 * @brief Defines the functions to operate on a character
 *
 * @file character.h
 * @author Carlos Méndez
 * @version 2.0
 * @date 21-02-2025
 * @copyright GNU Public License
 */

#include "types.h"

/**
 * @def GDESC_SIZE
 * @brief Defines the length of the gdesc
 */
#define GDESC_SIZE 6

/**
 * @brief Character
 *
 * This struct stores all the information related to a Character.
 */
typedef struct _Character Character;

/**
 * @brief Allocates memory for a new character and sets every field to 0 or NULL except the id
 * @author Carlos Méndez
 *
 * @param id Id of the character being created
 * @return Pointer to the character created, or NULL if there was an ERROR
 */
Character* character_create(Id id);

/**
 * @brief Frees up the memory of the character
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @return OK if it could destroy the character, and ERROR otherwise
 */
Status character_destroy(Character* character);

/**
 * @brief Establishes the character´s friendly state
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @param friendly Its friendly state, TRUE is its friendly and FALSE otherwise
 * @return OK if it could set it and ERROR if it couldnt
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief Retrieves the friendly field of a given character
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @return The character´s friendly state or FALSE if there was an error
 */
Bool character_get_friendly(const Character* character);

/**
 * @brief Asigns the character´s health
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @param health An int value of its health
 * @return OK if it could set it and ERROR otherwise
 */
Status character_set_health(Character* character, int health);

/**
 * @brief Retrieves the health of a given character
 * @author Carlos Méndez
 *
 * @param character Const pointer to character
 * @return The character´s health or -1 if there was an error
 */
int character_get_health(const Character* character);

/**
 * @brief Asigns if its following or not
 * @author Jorge Ochoa
 *
 * @param character Pointer to character
 * @param following Id of the player we are following
 * @return OK if it could set it and ERROR otherwise
 */
Status character_set_following(Character *character, Id following);

/**
 * @brief Gets if the character is following or not
 * @author Jorge Ochoa
 *
 * @param character Const pointer to character
 * @return The id of the player that we are following, NO_ID if an error ocurrs.
 */
Id character_get_following(const Character* character);

/**
 * @brief Asigns the gdesc field of the character
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @param gdesc String of the gdesc
 * @return OK if it could set it or ERROR otherwise
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief Retrieves the graphic description of a given character
 * @author Carlos Méndez
 *
 * @param character Const pointer to character
 * @return The description if everything went well or NULL otherwise
 */
const char* character_get_gdesc(const Character* character);

/**
 * @brief Gives back the id of a given character
 * @author Carlos Méndez
 *
 * @param character Const pointer to character
 * @return The character´s id or NO_ID if there was an error
 */
Id character_get_id(const Character* character);

/**
 * @brief Asigns the name field of the character
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @param name String of the name
 * @return OK if it could set it or ERROR otherwise
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief Retrieves the name of a given character
 * @author Carlos Méndez
 *
 * @param character Const pointer to character
 * @return The character´s name or NULL if there was an error
 */
const char* character_get_name(const Character* character);

/**
 * @brief Asigns the message field of the character
 * @author Carlos Méndez
 *
 * @param character Pointer to character
 * @param message String of the message
 * @return OK if it could set it or ERROR otherwise
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief Retrieves the message of a given character
 * @author Carlos Méndez
 *
 * @param character Const pointer to character
 * @return The character´s message or NULL if there was an error
 */
const char* character_get_message(const Character* character);

/**
 * @brief Outputs the character´s attributes
 * @author Carlos Méndez
 *
 * @param character Const pointer to character
 * @return OK if it could print it or ERROR otherwise
 */
Status character_print(const Character* character);

#endif
