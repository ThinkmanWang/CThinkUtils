project(data_type)
#AUX_SOURCE_DIRECTORY(. log_SOURCE_DIR)
ADD_LIBRARY (data_type ThinkPtrArray.c ThinkList.c ThinkHashmap.c ThinkBTree.c ThinkBSTree.c ThinkTree.c ThinkGraph.c ThinkStringBuilder.c)
TARGET_LINK_LIBRARIES(data_type ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(data_type pthread log)

INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS})