cmake_minimum_required(VERSION 3.9.5)
project(CThinkUtils)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLIB2 REQUIRED)
find_package(JsonGlib REQUIRED)

IF(APPLE)
    SET(CMAKE_BUILD_TYPE "Release")
    SET(CMAKE_OSX_ARCHITECTURES x86_64)
ENDIF(APPLE)

set(SOURCE_FILES main.c)
add_executable(CThinkUtils ${SOURCE_FILES})

ADD_SUBDIRECTORY(thinkutils)
INCLUDE_DIRECTORIES(thinkutils)

INCLUDE_DIRECTORIES(thinkutils/data_struct)
INCLUDE_DIRECTORIES(thinkutils/log)

ADD_SUBDIRECTORY(test)
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(CThinkUtils ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} ${JsonGlib_LIBRARIES})
TARGET_LINK_LIBRARIES(CThinkUtils pthread log thinkutils)

#install(DIRECTORY include DESTINATION .)

add_custom_command(TARGET CThinkUtils
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini)

add_custom_command(TARGET CThinkUtils
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.ini config.ini)

ADD_SUBDIRECTORY(ui)

