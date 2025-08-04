set(target "input")

add_library(${target} STATIC
    playercontroller.cpp
    playercontroller.hpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		gamecore
		util
)
project_dll_export(${target})
