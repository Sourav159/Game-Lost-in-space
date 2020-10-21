// Link to the screeencast of demonstration of the game in action: https://video.deakin.edu.au/media/t/0_x6ulpyzp

// Including all the header files related to the game
#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
    load_sound_effect("coins_sound", "coins.wav");
    load_sound_effect("health_sound", "health.wav");
    load_sound_effect("fuel_sound", "fuel.wav");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 1200, 650);
    load_resources();

    //Initialising the new game with new player
    game_data my_game;
    my_game = new_game();

    while (not quit_requested())
    {

        process_events();

        // Handle input to adjust player movement
        handle_input(my_game.player);

        // Updating the game with player and powerups
        update_game(my_game);

        //Drawing the game
        draw_game(my_game);

        // The game restarts when the fuel or health is finished
        if (my_game.player.fuel_pct <= 0 or my_game.player.health_pct <= 0)
        {
            my_game = new_game();
        }
    }

    return 0;
}