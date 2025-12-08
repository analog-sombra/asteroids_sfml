#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>
#include <memory>
#include <list>

class Entity;

class Game
{
public:
    Game();
    void run();

    static std::list<std::unique_ptr<Entity>> toAddList;
    static std::vector<std::unique_ptr<Entity>> entities;
};

#endif // __GAME_HPP__