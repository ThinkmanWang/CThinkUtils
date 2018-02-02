project(thinkutils)
AUX_SOURCE_DIRECTORY(. log_SOURCE_DIR)

ADD_SUBDIRECTORY(data_struct)
INCLUDE_DIRECTORIES(data_struct)

ADD_LIBRARY (thinkutils test.c datetime.c ini.c md5.c netutils.c string_utils.c parson.c)

TARGET_LINK_LIBRARIES(thinkutils ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(thinkutils pthread log data_struct)

INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIR}
        ${JsonGlib_INCLUDE_DIRS} data_struct)