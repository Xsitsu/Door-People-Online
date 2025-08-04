set(target "client")

add_executable(${target}
	graphics/actordrawer.cpp
	graphics/actordrawer.hpp

	graphics/terraindrawer.cpp
	graphics/terraindrawer.hpp

	gameclient.cpp
	gameclient.hpp
	main.cpp
	playercontroller.hpp
	playercontroller.cpp
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

		allegro
		allegro_color
		allegro_primitives
)
