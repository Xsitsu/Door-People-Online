#include "datamodel.hpp"

#include "GameCore/world.hpp"
#include "GameCore/playerlist.hpp"

namespace Game
{

DataModel::DataModel() : Util::ServiceProvider()
{

}

DataModel::~DataModel()
{

}

void DataModel::Init()
{
    Util::ServiceProvider::Init();
    this->AddService("World", new World());
    this->AddService("PlayerList", new PlayerList());
}

World* DataModel::GetWorld()
{
    return reinterpret_cast<World*>(this->GetService("World"));
}

PlayerList* DataModel::GetPlayerList()
{
    return reinterpret_cast<PlayerList*>(this->GetService("PlayerList"));
}

}
