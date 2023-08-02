# Flags have to be defined as normal variable and not as string since it 
# will be used by add_compile_options() which does not accept strings. 


# add compiler flags which are needed to build the app linking against GTK-4.0 and glib-2.0,
# shall be equal to output of commands: 'pkg-config --cflags glib-2.0' and 'pkg-config --cflags gtk4'
set(Linux_Compiler_Flags                       
            -Wall			
            -O0
            -ggdb			
            -mfpmath=sse
            -msse -msse2
            -pthread
            -I/usr/include/gtk-4.0
            -I/usr/include/gio-unix-2.0
            -I/usr/include/cairo
            -I/usr/include/pango-1.0
            -I/usr/include/harfbuzz
            -I/usr/include/pango-1.0
            -I/usr/include/fribidi
            -I/usr/include/harfbuzz
            -I/usr/include/gdk-pixbuf-2.0
            -I/usr/include/x86_64-linux-gnu
            -I/usr/include/cairo
            -I/usr/include/pixman-1
            -I/usr/include/uuid
            -I/usr/include/freetype2
            -I/usr/include/libpng16
            -I/usr/include/graphene-1.0
            -I/usr/lib/x86_64-linux-gnu/graphene-1.0/include
            -I/usr/include/libmount
            -I/usr/include/blkid
            -I/usr/include/glib-2.0
            -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
            #-H # prints out information about direct and indirect includes)
)

# add linker flags which are needed to link the app linking against GTK-4.0 and glib-2.0,
# shall be equal to output of commands: 'pkg-config --libs glib-2.0' and 'pkg-config --libs gtk4' 
set(Linux_Linker_Flags  
            -lgtk-4
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
)