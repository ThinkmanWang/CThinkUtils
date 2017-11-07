cmake_minimum_required(VERSION 3.8)
project(CHelloWorld)

set(CMAKE_C_STANDARD 99)

INCLUDE(FindGLIB2.cmake)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)
IF (GLIB2_FOUND)
    MESSAGE ("Glib found")
    INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS})
    MESSAGE (${GLIB2_INCLUDE_DIRS})
    #LINK_DIRECTORIES(${GLIB2_LIBRARIES})
    #LINK_DIRECTORIES(${GTHREAD2_LIBRARIES})
ELSE (GLIB2_FOUND)
    MESSAGE ("Glib not found")
ENDIF (GLIB2_FOUND)

set(SOURCE_FILES main.c)
add_executable(CHelloWorld ${SOURCE_FILES})

ADD_SUBDIRECTORY(log)
INCLUDE_DIRECTORIES(log)

ADD_SUBDIRECTORY(thinkutils)
INCLUDE_DIRECTORIES(thinkutils)

ADD_SUBDIRECTORY(test)

TARGET_LINK_LIBRARIES(CHelloWorld ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(CHelloWorld pthread log thinkutils)

add_custom_command(TARGET CHelloWorld
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini)

add_custom_command(TARGET CHelloWorld
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.ini config.ini)
