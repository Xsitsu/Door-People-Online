set(target "client-standalone")

add_executable(${target}
    game.cpp
    game.hpp
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
		util

		allegro
		allegro_color
		allegro_primitives
)
