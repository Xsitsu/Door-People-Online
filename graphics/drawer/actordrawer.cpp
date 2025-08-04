#include "actordrawer.hpp"

namespace Graphics
{

ActorDrawer::ActorDrawer()
{}

ActorDrawer::~ActorDrawer()
{}

void ActorDrawer::DrawActor(Game::World *world, Game::Actor *actor, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col)
{
    Game::Physics::PhysicsObject *object = world->GetPhysicsHandler().GetPhysicsObject(actor->GetPhysicsObjectHandle());

    Game::Vector2 size = object->GetGameObject().size;
    Game::Vector2 position = object->GetGameObject().position;

    Game::Vector2 posAdder(position.x, -position.y);

    Game::Vector2 drawStart = drawBegin + posAdder;
    Game::Vector2 drawEnd = drawStart + size;
    al_draw_filled_rectangle(drawStart.x, drawStart.y, drawEnd.x, drawEnd.y, col);

    ALLEGRO_COLOR colBlack = al_map_rgb(0, 0, 0);
    if (actor->GetDirection() == Game::Actor::Direction::Left)
    {
        al_draw_filled_rectangle(drawStart.x + 4, drawStart.y + 4, drawStart.x + 20, drawStart.y + 20, colBlack);
        al_draw_filled_rectangle(drawStart.x, drawStart.y + 28, drawStart.x + 14, drawStart.y + 32,  colBlack);
    }
    else if (actor->GetDirection() == Game::Actor::Direction::Right)
    {
        Game::Vector2 topRight(drawEnd.x, drawStart.y);
        al_draw_filled_rectangle(topRight.x - 20, topRight.y + 4, topRight.x - 4, topRight.y + 20, colBlack);
        al_draw_filled_rectangle(topRight.x - 14, topRight.y + 28, topRight.x, topRight.y + 32, colBlack);
    }
}

}