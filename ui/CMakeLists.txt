project(ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH /usr/local/opt/qt)
find_package(Qt5Widgets REQUIRED)

#add_executable(publisher publisher.cpp)
#target_link_libraries(publisher Qt5::Widgets Qt5::DBus)

add_executable(ui ui_main.cpp)
target_link_libraries(ui Qt5::Widgets ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_struct)

add_subdirectory(bstree_printer)