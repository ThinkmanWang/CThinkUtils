project(test)
#AUX_SOURCE_DIRECTORY(. log_SOURCE_DIR)
#ADD_LIBRARY (thinkutils test.c ieee.c)
#TARGET_LINK_LIBRARIES(thinkutils ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
#TARGET_LINK_LIBRARIES(thinkutils pthread log)

add_executable(test_ieee test_ieee.c)
TARGET_LINK_LIBRARIES(test_ieee ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES})
TARGET_LINK_LIBRARIES(test_ieee pthread log thinkutils)

