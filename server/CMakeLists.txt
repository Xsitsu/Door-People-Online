set(target "server")

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
		gamecore
		network
		util
)
