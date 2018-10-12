project(ui)

AUX_SOURCE_DIRECTORY(. ui_SOURCE_DIR)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)

# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

set(CMAKE_PREFIX_PATH /usr/local/opt/qt)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

# Generate rules for building source files from the resources
#qt5_add_resources(QRCS resources.qrc)

# Tell CMake to create the helloworld executable
#add_executable(ui ui_main.c ${UI_HEADERS} ${QRCS})
add_executable(ui ui_main.cpp)

# Add the Qt5 Widgets for linking
target_link_libraries(ui Qt5::Widgets ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_struct)

