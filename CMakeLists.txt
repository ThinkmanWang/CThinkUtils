cmake_minimum_required(VERSION 2.6)
project(CHelloWorld)

enable_testing()
set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLIB2 REQUIRED)
find_package(JsonGlib REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")

set(SOURCE_FILES main.c)
add_executable(CHelloWorld ${SOURCE_FILES})

ADD_SUBDIRECTORY(log)
INCLUDE_DIRECTORIES(log)

ADD_SUBDIRECTORY(thinkutils)
INCLUDE_DIRECTORIES(thinkutils)

ADD_SUBDIRECTORY(test)
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(CHelloWorld ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} ${JsonGlib_LIBRARIES})
TARGET_LINK_LIBRARIES(CHelloWorld pthread log thinkutils)

#install(DIRECTORY include DESTINATION .)

add_custom_command(TARGET CHelloWorld
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini)

add_custom_command(TARGET CHelloWorld
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.ini config.ini)
