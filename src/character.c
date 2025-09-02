/**
 * @brief Implements the functions to operate on a character
 *
 * @file character.c
 * @author Carlos Méndez
 * @version 2.0
 * @date 22-02-2025
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def NAME_SIZE
 * @brief Defines the length of the name
 */
#define NAME_SIZE 30

/**
 * @def MESSAGE_SIZE
 * @brief Defines the length of the message
 */
#define MESSAGE_SIZE 400

/**
 * @brief _Character private struct
 * */
struct _Character {
        Id id;                          /**< Unique Id*/
        char name[NAME_SIZE + 1];       /**< Name of the characterr*/
        Bool friendly;                  /**< Friendly status*/
        int health;                     /**< Health of the character*/
        Id following;                   /**< Id of the player that is following*/
        char gdesc[GDESC_SIZE + 1];     /**< Graphical description of the character*/
        char message[MESSAGE_SIZE + 1]; /**< Message of the character*/
};

Character* character_create(Id id) {
        Character* newCharacter = NULL;

        /* Error control */
        if (id == NO_ID) return NULL;

        newCharacter = (Character*)malloc(sizeof(Character));
        if (newCharacter == NULL) {
                return NULL;
        }

        /* Initialization of an empty character*/
        newCharacter->id = id;
        newCharacter->friendly = FALSE;
        newCharacter->following = NO_ID;
        strcpy(newCharacter->message, " \0");
        return newCharacter;
}

Status character_destroy(Character* character) {
        free(character);
        return OK;
}

Status character_set_friendly(Character* character, Bool friendly) {
        if (!character) return ERROR;
        character->friendly = friendly;
        return OK;
}

Bool character_get_friendly(const Character* character) {
        if (!character) return TRUE;
        return character->friendly;
}

Status character_set_health(Character* character, int health) {
        if (!character) return ERROR;
        character->health = health;
        return OK;
}

int character_get_health(const Character* character) {
        if (!character) return -1;
        return character->health;
}

Status character_set_following(Character* character, Id folllowing) {
        if (!character) return ERROR;
        character->following = folllowing;
        return OK;
}

Id character_get_following(const Character* character) {
        if (!character) return NO_ID;
        return character->following;
}

Status character_set_gdesc(Character* character, char* gdesc) {
        if (!character || !gdesc) return ERROR;
        strcpy(character->gdesc, gdesc);
        return OK;
}

const char* character_get_gdesc(const Character* character) {
        if (!character) return NULL;
        return character->gdesc;
}

Id character_get_id(const Character* character) {
        /*Error control*/
        if (!character) {
                return NO_ID;
        }
        return character->id;
}

Status character_set_name(Character* character, char* name) {
        /*Error control*/
        if (!character || !name) {
                return ERROR;
        }

        if (!strcpy(character->name, name)) {
                return ERROR;
        }
        return OK;
}

const char* character_get_name(const Character* character) {
        /*Error control*/
        if (!character) {
                return NULL;
        }
        return character->name;
}

Status character_set_message(Character* character, char* message) {
        /*Error control*/
        if (!character || !message) return ERROR;
        strcpy(character->message, message);
        return OK;
}

const char* character_get_message(const Character* character) {
        if (!character) return "";
        return character->message;
}

Status character_print(const Character* character) {
        /*Error control*/
        if (!character) {
                return ERROR;
        }
        fprintf(stdout, "name: %s, id: %d, friendly: %d, message: %s, health: %d, following: %d, gdesc: %s", character->name,
                (int)character->id, character->friendly, character->message, character->health, (int)character->following,
                character->gdesc);
        return OK;
}
