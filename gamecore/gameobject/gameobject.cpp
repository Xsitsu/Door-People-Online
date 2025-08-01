#include "gameobject.hpp"

namespace Game
{

GameObject::GameObject() : position(0, 0), size(1, 1)
{}

GameObject::GameObject(const Vector2 &position, const Vector2 &size) : position(position), size(size)
{}

}