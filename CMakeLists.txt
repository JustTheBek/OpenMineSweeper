cmake_minimum_required(VERSION 3.15)  								  

set(CMAKE_C_COMPILER /usr/bin/gcc)                                    # configure C compiler 

project(OpenMineSweeper LANGUAGES C)   								  # create CMake project 

#enable_testing()												 	  # enable Unit Testing

# add compiler flags which are needed to build the app linking against GTK-4.0 and glib-2.0,
# shall be equal to output of commands: 'pkg-config --cflags glib-2.0' and 'pkg-config --cflags gtk4' 
add_compile_options(
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
			-Wall			
			-O0
			-ggdb
			#-H # prints out information about direct and indirect includes
)

# add linker flags which are needed to link the app linking against GTK-4.0 and glib-2.0,
# shall be equal to output of commands: 'pkg-config --libs glib-2.0' and 'pkg-config --libs gtk4' 
link_libraries(
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

add_executable(OpenMineSweeper)   												  

add_subdirectory(src/)  										  	  # define lover levels where source files can be found
target_sources(OpenMineSweeper PRIVATE main.c) 				 		  # define files as target (on this level) which shall be built 


target_link_libraries(OpenMineSweeper PRIVATE src::Gui) 		  	  # link libraries to executable

# adding make target: ${CMAKE_SOURCE_DIR}/build/make GenerateUml
# generates .png files from .uml diagramms with PlantUML and store them into ${CMAKE_SOURCE_DIR}/docs
#add_custom_command (OUTPUT architecture.png COMMAND java -DPLANTUML_LIMIT_SIZE=8192 -jar /usr/share/plantuml/plantuml.jar -o "${CMAKE_SOURCE_DIR}/docs/"  "${CMAKE_SOURCE_DIR}/**/*.uml")
#add_custom_target(GenerateUml COMMAND DEPENDS architecture.png)		

#TODO: add relative paths to build and project root (via launch.sh parameter)
#file(COPY ./cliparts DESTINATION ./build/cliparts) # copyclipart into the build folder (the executable needs them)
															  