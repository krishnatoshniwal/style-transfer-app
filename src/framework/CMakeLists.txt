add_subdirectory(include)
add_executable(StyleTransferApp MACOSX_BUNDLE main.cpp)
target_link_libraries(StyleTransferApp fslazywindow simplebitmap ysbitmapfont utils GL GLU X11)
set_target_properties(StyleTransferApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../dist)