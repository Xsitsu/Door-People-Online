#ifndef PLAYER_CONTROLLER_HPP_INCLUDE
#define PLAYER_CONTROLLER_HPP_INCLUDE

#include "input_dll_export.h"

#include "gamecore/actor.hpp"
#include "gamecore/player.hpp"
#include "gamecore/world.hpp"

namespace Input
{

class DLL_EXPORT PlayerController
{
public:
    PlayerController(Game::Player *player, Game::World *world);

    bool CanJump() const;
    void Jump();
    void Move(Game::Actor::Direction move_dir);
    void StopMoving(Game::Actor::Direction move_dir);
    bool IsMoving(Game::Actor::Direction move_dir) const;
    bool IsOnGround() const;

    bool NeedsPhysicsUpdate() const;
    void ClearPhysicsUpdate();

private:
    Game::Physics::PhysicsObject* GetPhysicsObject();
    const Game::Physics::PhysicsObject* GetPhysicsObject() const;

private:
    Game::Player *player;
    Game::World *world;
    bool needs_physics_update;

    void UpdateDirection(Game::Actor::Direction move_dir);
};

}

#endif // PLAYER_CONTROLLER_HPP_INCLUDE
