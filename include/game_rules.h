/**
 * @brief It defines the specific game rules for our game
 *
 * @file game_management.c
 * @author Carlos Méndez, Jorge Ochoa y Jorge Pastor
 * @version 4.0
 * @date 01-05-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "types.h"

/**
 * @brief Implements function that checks if the game rules are activated
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @param last_cmd the last command introduced
 * @param turn int indicating how many turns have passed since the begining of the game
 * @param times_feeded reference to the amount of times the queen ant has been feeded
 * @param spider_is_dead Pointer to bool that is TRUE when the spider enemy is defeated
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_update(Game* game, Command* last_cmd, int turn, int* times_feeded, Bool* spider_is_dead);

/**
 * @brief Implements the game rule for the roof falling in top of the player and dealing damage every 5 turns
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_crumbling_roof(Game* game);

/**
 * @brief Implements the game rule for the attack of the spider that extra damage, 1 each turn since the attack, until 3 turns
 * have passed
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_spiders_venom_damage(Game* game);

/**
 * @brief Implements the game rule for when the spider is killed and drops the object of its fangs
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_spider_dies(Game* game);

/**
 * @brief Implements the game rule for the mission of feeding your queen ant so she can create more ants
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_feed_queen(Game* game);

/**
 * @brief Implements the game rule for when the players go up again to the start where the enemy ants are invading
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_ant_invasion(Game* game);

/**
 * @brief Implements the game rule for when the player attack with fangs
 * @author Carlos Méndez
 *
 * @param game Pointer to pointer to the game that is being played
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rule_attack_with_fangs(Game* game);
