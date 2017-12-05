#ifndef GAMECLIENT_HPP_INCLUDE
#define GAMECLIENT_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"

#include "network/client.hpp"
#include "network/packetall.hpp"

#include "gamecore/datamodel.hpp"
#include "gamecore/player.hpp"

class GameClient : public Network::Client
{
public:
    GameClient();
    ~GameClient();

    void Run();

protected:
    bool HandlePacket(Network::Packet::Connect *packet, const Network::Address &sender);
    bool HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender);
    bool HandlePacket(Network::Packet::Player *packet, const Network::Address &sender);

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;

    Game::DataModel dataModel;
    bool isRunning;

    Game::Player *player;

};

#endif // GAMECLIENT_HPP_INCLUDE
