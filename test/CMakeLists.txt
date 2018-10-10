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
TARGET_LINK_LIBRARIES(data_struct_test pthread log thinkutils data_struct)

add_executable(hash_test hash_test.c)
TARGET_LINK_LIBRARIES(hash_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_struct)

add_executable(btree_test btree_test.c)
TARGET_LINK_LIBRARIES(btree_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_struct)

add_executable(bstree_test bstree_test.c)
TARGET_LINK_LIBRARIES(bstree_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_struct)

add_executable(tree_test tree_test.c)
TARGET_LINK_LIBRARIES(tree_test ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_struct)

add_executable(spiral_array spiral_array.c)


INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS} thinkutils/data_struct thinkutils/log)

