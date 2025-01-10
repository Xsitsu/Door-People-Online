#include "playercontroller.hpp"

#include "gamecore/vector2.hpp"

PlayerController::PlayerController(Game::Player *player): needs_physics_update(false)
{
    this->player = player;
}

bool PlayerController::CanJump() const
{
    return this->player->IsOnGround();
}

void PlayerController::Jump()
{
    if (this->CanJump())
    {
        this->player->Jump();
        this->needs_physics_update = true;
    }
}

void PlayerController::UpdateDirection(Game::Actor::Direction move_dir)
{
    Game::Actor::Direction cur_dir = this->player->GetDirection();
    if (cur_dir != move_dir)
    {
        if (this->IsMoving(cur_dir))
        {
            this->StopMoving(cur_dir);
        }

        this->player->SetDirection(move_dir);

        this->needs_physics_update = true;
    }
}

void PlayerController::Move(Game::Actor::Direction move_dir)
{
    this->UpdateDirection(move_dir);

    if (!this->IsMoving(move_dir))
    {
        int x_speed = this->player->GetWalkspeed() * (int)move_dir;
        this->player->AddVelocity(Game::Vector2(x_speed, 0));

        this->needs_physics_update = true;
    }
}

void PlayerController::StopMoving(Game::Actor::Direction move_dir)
{
    if (this->IsMoving(move_dir))
    {
        int x_speed = this->player->GetWalkspeed() * (int)move_dir;
        this->player->AddVelocity(Game::Vector2(-x_speed, 0));

        this->needs_physics_update = true;
    }
}

bool PlayerController::IsMoving(Game::Actor::Direction move_dir) const
{
    bool is_same_dir = (this->player->GetDirection() == move_dir);
    bool has_x_speed = (this->player->GetVelocity().x != 0);

    return (is_same_dir && has_x_speed);
}

bool PlayerController::NeedsPhysicsUpdate() const
{
    return this->needs_physics_update;
}

void PlayerController::ClearPhysicsUpdate()
{
    this->needs_physics_update = false;
}
