#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "player.h"
#include "power_up.h"

#include <vector>

using std::vector;
using namespace std;

/**
 * The game_data keeps track of all of the information related to the overall game.
 * 
 * @field   player          The object of the player_data struct to accesss the player's information
 * @field   power_ups       Dynamic array of power_up_data to keep track of mutilple powerups
 * @field   game_timer      To keep track of the time
 *  */
struct game_data
{
    player_data player;
    vector<power_up_data> power_ups;
    timer game_timer;
};

/*
 * Creates a new game by creating a new player.
 * 
 * @returns     The new game data
 */
game_data new_game();

/*
 * Updates the game by updating the player, powerups, adding powerups and checking
 * collision between player and powerups.
 * 
 * @param game      The game being updated
 */
void update_game(game_data &game);

/*
 * Draws the game to the screen by drawing the hud, player and powerups.
 * 
 * @param game   The game to draw to the screen
 */
void draw_game(const game_data &game);

/*
 * Adds a powerup to the dynamic array of the game's powerup by calling the new_power_up function
 * to add at any random position between -1500 to +1500.
 * 
 * @param game   The game to be updated
 */
void add_power_up(game_data &game);

/*
 * Checks the collision between the player and powerup to call the respective procedures to
 * apply and remove the powerup.
 * 
 * @param game   The game to be updated
 */
void check_collisions(game_data &game);

/*
 * Updates the value of the powerup at index and plays an appropriate sound according to the powerup.
 * 
 * @param game   The game to be updated
 * @param index  The index of the powerup to be updated 
 */
void apply_power_up(game_data &game, int index);

/*
 * Removes the powerup at the index from the vector of powerups.
 * 
 * @param game   The game to be updated
 * @param index  The index of the powerup to be deleted 
 */
void remove_power_up(game_data &game, int index);

/*
 * Checks the postion of the powerups to ensure they are within the playing area of 3000
 * and removes the powerups which goes beyond that area.
 * 
 * @param game   The game to be updated
 */
void check_power_up_position(game_data &game);

/*
 * Calculates the coordinate of the powerup to be drawn at the minimap.
 * 
 * @returns     The 2d coordinate of the powerup
 */
point_2d power_mini_map_coordinate(const power_up_data &power_up);

/*
 * Calculates the coordinate of the player to be drawn at the minimap.
 * 
 * @returns     The 2d coordinate of the player
 */
point_2d player_mini_map_coordinate(const player_data &player);

/*
 * Draws the positions of the powerups and player in the minimap
 * 
 * @param game   The game to be drawn to the screen
 */
void draw_minimap(const game_data &game);


/*
 * Draws the heads up display to the screen by drawing the score, location of the player, fuel bar, health bar,
 * level and the minimap.
 * 
 * @param game   The game to be drawn to the screen.
 */
void draw_hud(const game_data &game);

#endif