#ifndef LOST_IN_SPACE_POWER_UP
#define LOST_IN_SPACE_POWER_UP

#include "splashkit.h"
#include <vector>

using namespace std;

/*
 * Different options for the kind of power up.
 */
enum power_up_kind
{
    POWER,
    FUEL,
    LEVEL,
    BULLET,
    COIN,
    HEART
};

/**
 * The power_up_data keeps track of all of the information related to the power up.
 * 
 * @field   power_up_sprite     The power up's sprite - used to track position and movement
 * @field   kind                Current kind of power up 
 */
struct power_up_data
{
    power_up_kind   kind;
    sprite          power_up_sprite;

};

/**
 * Creates a new power up in the required position of the screen with a random power up.
 * 
 * @returns     The new power up data
 */
power_up_data new_power_up(double x, double y);

/**
 * Draws the power up to the screen. 
 * 
 * @param power_to_draw    The power up to draw to the screen
 */
void draw_power_up(const power_up_data &power_to_draw);

/**
 * Actions a step update of the power up - moving them and adjusting the camera.
 * 
 * @param power_to_update      The power up being updated
 */
void update_power_up(power_up_data &power_to_update);



#endif 