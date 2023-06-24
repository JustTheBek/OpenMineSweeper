cmake_minimum_required(VERSION 3.15)  								  

set(CMAKE_C_COMPILER /usr/bin/gcc)                                    # configure C compiler 

project(OpenMineSweeper LANGUAGES C)   								  # create CMake project 

#enable_testing()												 	  # enable Unit Testing

# add compiler flags which are needed to build the app, shall at least contain cmd: 'pkg-config --cflags glib-2.0'
add_compile_options(
			-I/usr/include/glib-2.0
			-I/usr/lib/x86_64-linux-gnu/glib-2.0/include
			-Wall			
			-O0
			-ggdb
			#-H # prints out information about direct and indirect includes
)

# add linker flags which are needed to link the app, shall contain at least cmd: 'pkg-config --libs glib-2.0'
link_libraries(
			-lglib-2.0
)

add_executable(OpenMineSweeper)   												  

#add_subdirectory(src/)  										  	  # define lover levels where source files can be found
target_sources(OpenMineSweeper PRIVATE main.c) 				 		  # define files as target (on this level) which shall be built 


#target_link_libraries(OpenMineSweeper PRIVATE src::GameManager) 		  # link libraries to executable

# adding make target: ${CMAKE_SOURCE_DIR}/build/make GenerateUml
# generates .png files from .uml diagramms with PlantUML and store them into ${CMAKE_SOURCE_DIR}/docs
#add_custom_command (OUTPUT architecture.png COMMAND java -DPLANTUML_LIMIT_SIZE=8192 -jar /usr/share/plantuml/plantuml.jar -o "${CMAKE_SOURCE_DIR}/docs/"  "${CMAKE_SOURCE_DIR}/**/*.uml")
#add_custom_target(GenerateUml COMMAND DEPENDS architecture.png)		


															  