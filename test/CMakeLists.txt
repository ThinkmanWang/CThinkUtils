project(test)
#AUX_SOURCE_DIRECTORY(. log_SOURCE_DIR)
#ADD_LIBRARY (thinkutils test.c ieee.c)
#TARGET_LINK_LIBRARIES(thinkutils ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
#TARGET_LINK_LIBRARIES(thinkutils pthread log)

add_executable(test_ieee test_ieee.c)
TARGET_LINK_LIBRARIES(test_ieee ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(test_ieee pthread log thinkutils)

add_executable(json_test json_test.c)
TARGET_LINK_LIBRARIES(json_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(json_test pthread log thinkutils)

add_executable(data_struct_test data_struct_test.c)
TARGET_LINK_LIBRARIES(data_struct_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(data_struct_test pthread log thinkutils data_type)

add_executable(hash_test hash_test.c)
TARGET_LINK_LIBRARIES(hash_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

add_executable(btree_test btree_test.c)
TARGET_LINK_LIBRARIES(btree_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

add_executable(bstree_test bstree_test.c)
TARGET_LINK_LIBRARIES(bstree_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

add_executable(tree_test tree_test.c)
TARGET_LINK_LIBRARIES(tree_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

add_executable(graph_test graph_test.c)
TARGET_LINK_LIBRARIES(graph_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

add_executable(spiral_array spiral_array.c)

add_executable(size_test size_test.c)

add_executable(qsort qsort.cpp)

add_executable(refrence_test refrence_test.cpp)

add_executable(ptr_ary_test ptr_ary_test.c)
TARGET_LINK_LIBRARIES(ptr_ary_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

add_executable(list_test list_test.c)
TARGET_LINK_LIBRARIES(list_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)

INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS} thinkutils/data_type thinkutils/log)

add_executable(mid mid.cpp)

