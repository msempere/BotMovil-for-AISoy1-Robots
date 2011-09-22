cmake_minimum_required (VERSION 2.8)
cmake_policy(VERSION 2.8)
project(newBotMovil)

IF (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	add_definitions(-D__DEBUG__)
	SET(CMAKE_CXX_FLAGS "-Wall -O0")
ELSE (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	SET(CMAKE_CXX_FLAGS "-Wall -O2")
ENDIF (${CMAKE_BUILD_TYPE} MATCHES "Debug")

IF (${CROSS_COMPILING})
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_CFLAGS} -mfpu=neon")
ENDIF (${CROSS_COMPILING})


add_subdirectory(src)
