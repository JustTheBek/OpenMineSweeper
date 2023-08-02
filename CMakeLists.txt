cmake_minimum_required(VERSION 3.15)  								  

# configure building on Linux
if (UNIX)
	message("Building on Linux.")
	set(CMAKE_C_COMPILER /usr/bin/gcc)             					 
	include(linux_flags.cmake)
	add_compile_options("${Linux_Compiler_Flags}")
	link_libraries("${Linux_Linker_Flags}")
endif (UNIX)

# configure building on Windows
if (WIN32)
	message("Building on Windows.")	
	set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe)              
	include(windows_flags.cmake)
	add_compile_options("${Windows_Compiler_Flags}")
	link_libraries("${Windows_Linker_Flags}")
endif (WIN32)


project(OpenMineSweeper LANGUAGES C)   								  # create CMake project 

#enable_testing()												 	  # needed for Unit Testing

add_executable(OpenMineSweeper)   												  
add_subdirectory(src/)  										  	  # define lover levels where further CMake files can be found
target_sources(OpenMineSweeper PRIVATE main.c) 				 		  # define files as target (on this level) which shall be built 
target_link_libraries(OpenMineSweeper PRIVATE src::Gui) 		  	  # link libraries to executable

# adding make target: ${CMAKE_SOURCE_DIR}/build/make GenerateUml
# generates .png files from .uml diagramms with PlantUML and store them into ${CMAKE_SOURCE_DIR}/docs
#add_custom_command (OUTPUT architecture.png COMMAND java -DPLANTUML_LIMIT_SIZE=8192 -jar /usr/share/plantuml/plantuml.jar -o "${CMAKE_SOURCE_DIR}/docs/"  "${CMAKE_SOURCE_DIR}/**/*.uml")
#add_custom_target(GenerateUml COMMAND DEPENDS architecture.png)		

#TODO: add relative paths to build and project root (via launch.sh parameter)
#file(COPY ./cliparts DESTINATION ./build/cliparts) # copyclipart into the build folder (the executable needs them)
															  