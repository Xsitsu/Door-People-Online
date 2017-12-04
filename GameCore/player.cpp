#include "player.hpp"

namespace Game
{

Player::Player() : networkOwner(0)
{

}

Player::~Player()
{

}

bool Player::IsPlayer() const
{
    return true;
}

uint32_t Player::GetNetworkOwner() const
{
    return this->networkOwner;
}

void Player::SetNetworkOwner(uint32_t owner)
{
    this->networkOwner = owner;
}

}
