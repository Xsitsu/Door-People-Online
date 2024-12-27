set(target "GameCore")

add_library(${target} STATIC
	actor.cpp
	actor.hpp
	datamodel.cpp
	datamodel.hpp
	platform.cpp
	platform.hpp
	player.cpp
	player.hpp
	playerlist.cpp
	playerlist.hpp
	terrain.cpp
	terrain.hpp
	vector2.cpp
	vector2.hpp
	wall.cpp
	wall.hpp
	world.cpp
	world.hpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		Util
)
project_dll_export(${target})
