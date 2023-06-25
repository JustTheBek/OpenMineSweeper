add_library(Gui STATIC)
add_library(src::Gui ALIAS Gui) 

target_sources(Gui		
		PRIVATE
		Gui.h
		Gui.c		
)

target_include_directories(Gui
		PUBLIC							  
		./	
)

target_link_libraries(Gui 			# add libraries which shall be linked to the target lib
   PUBLIC
   src::GameLogic)     	

															  
