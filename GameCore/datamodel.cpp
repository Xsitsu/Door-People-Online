#include "datamodel.hpp"

#include "gamecore/world.hpp"

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
}

}
