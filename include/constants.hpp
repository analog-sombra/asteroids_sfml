#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

namespace Constants
{
    // Window settings
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;
    constexpr unsigned int FRAMERATE_LIMIT = 60;
    constexpr char WINDOW_TITLE[] = "Asteroids SFML";

    constexpr float TURN_SPEED = 100.0f;
    constexpr float PLAYER_SPEED = 200.0f;
    constexpr float PLAYER_WIDTH = 50.0f;
    constexpr float PLAYER_HEIGHT = 40.0f;
    
    constexpr float BULLET_SPEED = 300.0f;
    constexpr float SHOOT_COOLDOWN = 0.5f; // Cooldown time in seconds
    constexpr float BULLET_LIFETIME = 4.0f; // Lifetime of a bullet in seconds

    constexpr float ASTEROID_SPIN = 25.0f;
    constexpr float ASTEROID_SPEED = 100.0f;

    constexpr float ASTEROID_SPAWN_TIME = 3.0f; // Time interval between asteroid spawns in seconds

}

#endif // __CONSTANTS_HPP__