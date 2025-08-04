set(target "client")

add_executable(${target}
	gameclient.cpp
	gameclient.hpp
	main.cpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		gamecore
		graphics
		input
		network
		util

		allegro
		allegro_color
		allegro_primitives
)
