#include "lost_in_space.h"
#include "splashkit.h"

#define MIN_POWER_UP_RANGE -1500
#define MAX_POWER_UP_RANGE 1500
#define MAX_GAME_RANGE 3000

// Creating a new game
game_data new_game()
{
    game_data game;

    game.player = new_player();

    return game;
}

// Applying the effect of the powerup
void apply_power_up(game_data &game, int index)
{

    if (game.power_ups[index].kind == FUEL)
    {

        // Increasing the value only if the percentage is less than 100
        if (game.player.fuel_pct <= 1)
            game.player.fuel_pct += 0.25;

        play_sound_effect("fuel_sound");
    }

    else if (game.power_ups[index].kind == LEVEL)
    {
        // Increasing the value only if the level is less than 5
        if (game.player.level <= 5)
            game.player.level += 1;

        play_sound_effect("coins_sound");
    }

    else if (game.power_ups[index].kind == HEART)
    {
        // Increasing the value only if the percentage is less than 100
        if (game.player.health_pct <= 1)
            game.player.health_pct += 0.25;

        play_sound_effect("health_sound");
    }

    else
    {
        play_sound_effect("fuel_sound");
    }
}

// Removing the powerup at the index from the vector
void remove_power_up(game_data &game, int index)
{
    int last_idx = game.power_ups.size() - 1;
    game.power_ups[index] = game.power_ups[last_idx];
    game.power_ups.pop_back();
}

void check_collisions(game_data &game)
{

    for (int i = game.power_ups.size() - 1; i >= 0; i--)
    {
        if (sprite_collision(game.player.player_sprite, game.power_ups[i].power_up_sprite))
        {
            // Increasing the score everytime a powerup is collected
            game.player.score++;

            // First applying the effect of the powerup and then removing it from the vector
            apply_power_up(game, i);
            remove_power_up(game, i);
        }
    }
}

void add_power_up(game_data &game)
{
    int value = rnd(MIN_POWER_UP_RANGE, MAX_POWER_UP_RANGE);

    // Adding the powerup to the vector at any random position between the paying area
    game.power_ups.push_back(new_power_up(value, value));
}

void check_power_up_position(game_data &game)
{
    for (int i = 0; i < game.power_ups.size(); i++)
    {
        double power_up_x = sprite_x(game.power_ups[i].power_up_sprite);
        double power_up_y = sprite_y(game.power_ups[i].power_up_sprite);

        // The powerup is removd if it goes out of the playing area of 3000
        if (power_up_x > MAX_POWER_UP_RANGE or power_up_y > MAX_POWER_UP_RANGE or power_up_x < MIN_POWER_UP_RANGE or power_up_y < MIN_POWER_UP_RANGE)
        {
            remove_power_up(game, i);
        }
    }

    
}


void update_game(game_data &game)
{

    // Adding a powerup in 2% of the time
    if (rnd() < 0.02)
    {
        add_power_up(game);
    }

    // Checking the collison between player and powerups
    check_collisions(game);

    // Perform movement and update the camera
    update_player(game.player);

    // Updating the powerups and checking their position
    for (int i = 0; i < game.power_ups.size(); i++)
    {
        check_power_up_position(game);

        update_power_up(game.power_ups[i]);

    }
    
}

point_2d power_mini_map_coordinate(const power_up_data &power_up)
{
    double power_x, power_y, mini_map_x, mini_map_y;

    power_x = sprite_x(power_up.power_up_sprite);
    power_y = sprite_y(power_up.power_up_sprite);

    // Calculating the coordinate of the powerup according to the minimap
    mini_map_x = (power_x - MIN_POWER_UP_RANGE) / MAX_GAME_RANGE * 100 + 15;
    mini_map_y = (power_y - MIN_POWER_UP_RANGE) / MAX_GAME_RANGE * 100 + 15;

    return point_at(mini_map_x, mini_map_y);
}

point_2d player_mini_map_coordinate(const player_data &player)
{
    double player_x, player_y, mini_map_x, mini_map_y;

    player_x = sprite_x(player.player_sprite);
    player_y = sprite_y(player.player_sprite);

    // Calculating the coordinate of the player according to the minimap
    mini_map_x = (player_x - MIN_POWER_UP_RANGE) / MAX_GAME_RANGE * 100 + 15;
    mini_map_y = (player_y - MIN_POWER_UP_RANGE) / MAX_GAME_RANGE * 100 + 15;

    return point_at(mini_map_x, mini_map_y);
}

void draw_minimap(const game_data &game)
{
    for (int i = 0; i < game.power_ups.size(); i++)
    {
        // Drawing the position of the powerups with the red colour
        draw_pixel(rgba_color(255, 0, 0, 255), power_mini_map_coordinate(game.power_ups[i]), option_to_screen());
    }

    // Drawing the position of the player with the blue colour
    draw_pixel(rgba_color(0, 0, 255, 255), player_mini_map_coordinate(game.player), option_to_screen());
}

// Function to return the drawing options of option_part_bmp
drawing_options option_part(double x, double y, double width, double height)
{
    drawing_options options;

    options = option_part_bmp(x, y, width, height, option_to_screen());

    return options;
}

// Procedure to include the elements in the Heads up display
void draw_hud(const game_data &game)
{
    // Drawing the area of the HUD
    draw_rectangle(COLOR_LIGHT_BLUE, 5, 5, 410, 125, option_part(0, 0, 300, 200));

    // Drawing the minimap area
    draw_rectangle(COLOR_YELLOW_GREEN, 15, 15, 100, 100, option_to_screen());

    // Drawing score and location
    draw_text("SCORE: " + to_string(game.player.score), COLOR_WHITE, 120, 20, option_to_screen());
    draw_text("LOCATION: " + point_to_string(center_point(game.player.player_sprite)), COLOR_WHITE, 120, 35, option_to_screen());

    // Drawing the fuel bar
    draw_text("FUEL: ", COLOR_WHITE, 120, 55, option_to_screen());
    draw_bitmap("empty", 160, 50, option_part(0, 0, bitmap_width("empty"), bitmap_height("empty")));
    draw_bitmap("full", 160, 50, option_part(0, 0, game.player.fuel_pct * bitmap_width("full"), bitmap_height("full")));

    // Drawing the health bar
    draw_text("HEALTH: ", COLOR_WHITE, 120, 80, option_to_screen());
    draw_bitmap("empty", 175, 73, option_part(0, 0, bitmap_width("empty"), bitmap_height("empty")));
    draw_bitmap("red_bar", 175, 73, option_part(0, 0, game.player.health_pct * bitmap_width("red_bar"), bitmap_height("red_bar")));

    //Showing the level
    draw_text("LEVEL: ", COLOR_WHITE, 120, 105, option_to_screen());
    int x = 165;
    int counter = game.player.level / 2;
    for (int i = 0; i <= counter; i++)
    {
        draw_bitmap("level_hud", x, 90, option_part(0, 0, bitmap_width("level_hud"), bitmap_height("level_hud")));
        x = x + 40;
    }

    // Drawing the minimap to show the position of the powerups and player
    draw_minimap(game);

}

void draw_game(const game_data &game)
{
    // Redrawing everything
    clear_screen(COLOR_BLACK);

    // Displaying the HUD
    draw_hud(game);
    
    // as well as the player who can move
    draw_player(game.player);

    // Drawing the power ups
    for (int i = 0; i < game.power_ups.size(); i++)
        draw_power_up(game.power_ups[i]);

    refresh_screen(60);
}