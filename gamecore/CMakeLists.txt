set(target "gamecore")

add_library(${target} STATIC
	actor.cpp
	actor.hpp
	datamodel.cpp
	datamodel.hpp

	gameobject/gameobject.cpp
	gameobject/gameobject.hpp

	physics/physicshandler.cpp
	physics/physicshandler.hpp

	physics/physicsobject.cpp
	physics/physicsobject.hpp

	physics/physicssettings.cpp
	physics/physicssettings.hpp

	player.cpp
	player.hpp
	playerlist.cpp
	playerlist.hpp

	terrain/terrainobject.cpp
	terrain/terrainobject.hpp

	terrain/terrainhandler.cpp
	terrain/terrainhandler.hpp

	vector2.cpp
	vector2.hpp
	world.cpp
	world.hpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		util
)
project_dll_export(${target})
