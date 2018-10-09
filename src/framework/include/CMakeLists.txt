add_library(utils
        essentials.cpp essentials.h
        DeepCutout.cpp DeepCutout.h
        resizebmp.cpp resizebmp.h
        cpp2python.cpp cpp2python.h
        button.h button.cpp
        CImg.h
        libraries.h ImageUI.cpp ImageUI.h bmplocations.cpp bmplocations.h bmphash.cpp bmphash.h images.cpp images.h)
target_include_directories(utils PUBLIC .)
target_link_libraries(utils fslazywindow simplebitmap ysbitmapfont GL GLU X11)
