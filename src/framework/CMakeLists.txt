add_subdirectory(utils)
add_executable(Style_transfer main.cpp)
target_link_libraries(Style_transfer fslazywindow simplebitmap ysbitmapfont utils GL GLU X11)
set_target_properties( Style_transfer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../style-transfer)