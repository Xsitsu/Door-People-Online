set(target "client")

add_executable(${target}
	actordrawer.cpp
	actordrawer.hpp
	gameclient.cpp
	gameclient.hpp
	main.cpp
	terraindrawer.cpp
	terraindrawer.hpp
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
