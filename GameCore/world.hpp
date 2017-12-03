#ifndef WORLD_HPP_INCLUDE
#define WORLD_HPP_INCLUDE

#include "main.h"

#include "util/service.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT World : public Util::Service
#else
class World : public Util::Service
#endif // _WIN32
{
public:
    World();
    ~World();

protected:

};

}

#endif // WORLD_HPP_INCLUDE
