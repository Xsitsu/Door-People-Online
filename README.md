# Online Platformer Game
Also known as Door People Online. (because of how the characters turned out)

Final lab for my networks class written in C++. (December 2017)

## About
This project is a 2D online platformer written for my networks lab over around 4 days.

The [Code::Blocks](http://www.codeblocks.org/) IDE with the MinGW compiler was used for development of this project.

The [Allegro 5](http://liballeg.org/) game programming library was used in the development of this game to handle window/display creation, game timers, drawing shapes, and keyboard events.

Everything not handled by Allegro 5 was written in C++ from scratch. This includes networking, game logic, and build scripts.



## Building

### Linux

1. Clone the repository.
2. Run build.sh.

**Note:** No client build for linux.

### Windows

1. Clone the repository.
2. Get a pre-built copy of [Allegro 5.0.10](https://www.allegro.cc/files/) and put it into the newly copied repository directory. **(version / filenames DO matter)**
3. Open Client, Server, GameCore, Network, and Util projects in Code::Blocks.
4. Build Client/Server.
5. Build GameCore.
6. Build Network.
7. Build Util.
8. Build Client/Server.

**Note:** This build order is required because of post build scripts in GameCore, Network, and Util projects that copy produced DLL files to appropriate bin folders. The bin folders for projects wont exist without first building them. This is a problem that could be fixed in script, but it wont be at leasts for now.

## Game Features

**Movement:** Players are able to connect to a server, move around, and jump.

**"Smart Networking":** Player "physics" (and I use that term very lightly) are networked from client to server to other clients based on input and large position changes. When players are not moving clients will locally simulate their own physics for those players.

**Multiple Connections From IP Addresses:** Server accepts up to 3 connections from a single IP address. Any connections past the limit of 3 will be refused.

**Client Reconnecting:** Any clients that crash and do not send a disconnection packet are able to reconnect and reclaim their old connection.

**Terrain Downloading:** Clients download terrain data from the server upon startup.

**Different Types of Terrain:** There are green walls, and blue platforms. Green walls can be collided with from all 4 sides. Blue platforms only stop the player from falling through the top, so players can jump up through blue platforms from below.


## Features I Wanted To Add But Didn't Have Time To Or Couldn't Get Working

**Threading:** For some reason std::mutex just wouldn't compile with whatever version of MinGW I was using, so I just stopped trying after a few hours because I didn't want to waste time. The entire Logger class was written in a way so it could have a dedicated log output thread, but that never saw the light of day.

**Signals:** Windows signals are just bad and ruined everything. I could catch SIG_INT on Linux for the server and send disconnect packets to all clients, but Windows just ruins every single attempt at that on the client.

**Automatic Client Timeout:** If a client crashes and doesn't send a disconnect, they will remain on the server forever until reclaimed.

**Automatic Server Timeout:** If the server goes down, clients will never know and will continue existing. They will just think it's odd how other players stopped moving.

**Random Player Colors:** I wanted to give players a random color, but I just never got around to it.

**Hack Checks:** Clients are 100% authoritative on their players. There's no code to stop players from lying about position or velocity.

**Packet Data/Size Validation:** Straight up the game will crash if you send a packet with an invalid size. This will never happen while using a valid client/server, but any attacker could create an invalid packet to send to the server to crash it.

**Server Address Config File:** Debug client is set to connect to server running on local machine, while release client is set to connect to a hardcoded address. I wanted to have a config file for loading server address and port, but never got around to it.

## Programming Decisions

### Packet Family and Packet Action System
I wanted to create a system that would reduce the number of different packet encoding/decoding styles that would be required. I didn't want to have to create a different system for encoding/decoding an add player packet and a remove player packet for example.

With this system, you can define one encoding/decoding system for an entire packet family type, and then with the packet action field specify how the packet is to be interpreted. For example, a Player packet has Add, Remove, and Tell actions for creating, deleting, and updating physics for a player (respectively).

### Service Provider System
I wanted to try implementing a pattern I had seen in other projects before, but I didn't end up doing much with it. I still ended up adding specific GetService() functions for things like World and PlayerList, so perhaps it wasn't that beneficial.

### Socket and Address Classes
Modified versions of some network programming example somewhere on the internet. They act as wrappers for native sockets on Windows and Linux systems and are able to be used cross platform which was the main reason for their use.


