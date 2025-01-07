#include "playerlist.hpp"

#include "datamodel.hpp"

namespace Game
{

PlayerList::PlayerList() : players()
{

}

PlayerList::~PlayerList()
{

}

void PlayerList::AddPlayer(Player *player)
{
    this->players.push_back(player);

    DataModel *dataModel = static_cast<DataModel*>(this->provider);
    World *world = dataModel->GetWorld();
    world->AddActor(player);
}

void PlayerList::RemovePlayer(Player *player)
{
    this->players.remove(player);

    DataModel *dataModel = static_cast<DataModel*>(this->provider);
    World *world = dataModel->GetWorld();
    world->RemoveActor(player);
}

std::list<Player*> PlayerList::GetPlayers()
{
    return this->players;
}

Player* PlayerList::GetPlayerWithNetworkId(uint32_t id)
{
    for (Player* player : this->players)
    {
        if (player->GetNetworkOwner() == id)
        {
            return player;
        }
    }
    return nullptr;
}


}
