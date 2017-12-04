#include "terrain.hpp"

namespace Game
{

Terrain::Terrain(TerrainType type) : type(type), position(), size()
{

}

Terrain::~Terrain()
{

}

TerrainType Terrain::GetTerrainType() const
{
    return this->type;
}

Vector2 Terrain::GetPosition() const
{
    return this->position;
}

Vector2 Terrain::GetSize() const
{
    return this->size;
}

void Terrain::SetPosition(const Vector2 &position)
{
    this->position = position;
}

void Terrain::SetSize(const Vector2 &size)
{
    this->size = size;
}

}
