#ifndef GAMECLIENT_HPP_INCLUDE
#define GAMECLIENT_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_native_dialog.h"

#include "network/client.hpp"
#include "network/packet/packetall.hpp"

#include "gamecore/datamodel.hpp"
#include "gamecore/player.hpp"

#include "util/log/logger.hpp"

#include "playercontroller.hpp"

class GameClient : public Network::Client
{
public:
    GameClient();
    ~GameClient();

    void Run();

protected:
    bool HandlePacket(Network::Packet::Connect *packet, const Network::Address &sender);
    bool HandlePacket(Network::Packet::Disconnect *packet, const Network::Address &sender);
    bool HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender);
    bool HandlePacket(Network::Packet::Player *packet, const Network::Address &sender);

    void HandleKeyDown(int keycode);
    void HandleKeyUp(int keycode);

protected:
    void RequestTerrainFromServer();
    void CreatePlayerForClient();
    void SendPhysicsUpdateToServer();

    // ALLEGRO Variables
protected:
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;

    // Game variables
protected:
    Game::DataModel dataModel;
    bool isRunning;

    PlayerController* player_controller;
    Game::Player *player;

    // Log stuff
protected:
    Util::Log* log;
};

#endif // GAMECLIENT_HPP_INCLUDE
