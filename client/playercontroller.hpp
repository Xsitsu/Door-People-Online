#ifndef PLAYER_CONTROLLER_HPP_INCLUDE
#define PLAYER_CONTROLLER_HPP_INCLUDE

#include "gamecore/actor.hpp"
#include "gamecore/player.hpp"

class PlayerController
{
public:
    PlayerController(Game::Player *player);

    bool CanJump() const;
    void Jump();
    void Move(Game::Actor::Direction move_dir);
    void StopMoving(Game::Actor::Direction move_dir);
    bool IsMoving(Game::Actor::Direction move_dir) const;

    bool NeedsPhysicsUpdate() const;
    void ClearPhysicsUpdate();

private:
    Game::Player *player;
    bool needs_physics_update;

    void UpdateDirection(Game::Actor::Direction move_dir);
};


#endif // PLAYER_CONTROLLER_HPP_INCLUDE
