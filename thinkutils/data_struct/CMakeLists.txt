project(data_struct)
AUX_SOURCE_DIRECTORY(. log_SOURCE_DIR)
ADD_LIBRARY (data_struct ThinkPtrArray.c ThinkList.c ThinkHashmap.c ThinkBTree.c ThinkBSTree.c ThinkTree.c)
TARGET_LINK_LIBRARIES(data_struct ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(data_struct pthread log)

INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS})