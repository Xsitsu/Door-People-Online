find_package(Freetype REQUIRED)

set(target "Client")

add_executable(${target}
	actordrawer.cpp
	actordrawer.hpp
	gameclient.cpp
	gameclient.hpp
	main.cpp
	terraindrawer.cpp
	terraindrawer.hpp
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

		# freetype must happen before allegro
		freetype
		allegro_monolith
)
