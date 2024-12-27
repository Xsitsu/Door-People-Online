set(target "Server")

add_executable(${target}
	gameserver.cpp
	gameserver.hpp
	main.cpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		GameCore
		Network
		Util
)
