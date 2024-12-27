set(target "Util")

add_library(${target} STATIC
	logchannel.cpp
	logchannel.hpp
	logger.cpp
	logger.hpp
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
