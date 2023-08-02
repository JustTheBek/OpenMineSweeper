# Flags have to be defined as normal variable and not as string since it 
# will be used by add_compile_options() which does not accept strings.


set(Windows_Compiler_Flags                       
            -Wall
            -O0
            -g
            -DLIBDEFLATE_DLL
            -mfpmath=sse
            -msse
            -msse2
            -IC:/msys64/mingw64/include/gtk-4.0
            -IC:/msys64/mingw64/include/pango-1.0
            -IC:/msys64/mingw64/include/harfbuzz
            -IC:/msys64/mingw64/include/pango-1.0
            -IC:/msys64/mingw64/include/fribidi
            -IC:/msys64/mingw64/include/gdk-pixbuf-2.0
            -IC:/msys64/mingw64/include/webp
            -IC:/msys64/mingw64/include/cairo
            -IC:/msys64/mingw64/include/freetype2
            -IC:/msys64/mingw64/include/libpng16
            -IC:/msys64/mingw64/include/harfbuzz
            -IC:/msys64/mingw64/include/pixman-1
            -IC:/msys64/mingw64/include/graphene-1.0
            -IC:/msys64/mingw64/lib/graphene-1.0/include
            -IC:/msys64/mingw64/include/glib-2.0
            -IC:/msys64/mingw64/lib/glib-2.0/include			
            #-H # prints out information about direct and indirect includes)
)

set(Windows_Linker_Flags  
            -lgtk-4
			-lpangowin32-1.0
			-lpangocairo-1.0
			-lpango-1.0
			-lharfbuzz
			-lgdk_pixbuf-2.0
			-lcairo-gobject
			-lcairo
			-lgraphene-1.0
			-lgio-2.0
			-lgobject-2.0
			-lglib-2.0
			-lintl
)