set(target "graphics")

add_library(${target} STATIC
	drawer/actordrawer.cpp
	drawer/actordrawer.hpp

	drawer/terraindrawer.cpp
	drawer/terraindrawer.hpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		gamecore
		util

		allegro
		allegro_color
		allegro_primitives
)
project_dll_export(${target})
