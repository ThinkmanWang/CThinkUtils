project(bstree_printer)

#AUX_SOURCE_DIRECTORY(. bstree_printer_SOURCE_DIR)

add_executable(bstree_printer bstree_printer.cpp CBSTreePrinterDlg.cpp)
target_link_libraries(bstree_printer Qt5::Widgets ${GLIB2_LIBRARIES} ${GTHREAD2_LIBRARIES} log thinkutils data_type)
#qt5_use_modules(bstree_printer Widgets)
