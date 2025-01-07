set(target "Util")

add_library(${target} STATIC
	log/log.cpp
	log/log.hpp
	log/logger.cpp
	log/logger.hpp
	service.cpp
	service.hpp
	serviceprovider.cpp
	serviceprovider.hpp
	timer.cpp
	timer.hpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
project_dll_export(${target})
