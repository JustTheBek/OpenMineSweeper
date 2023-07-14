add_library(GameManager STATIC)
add_library(src::GameManager ALIAS GameManager) 

target_sources(GameManager		
		PRIVATE
		GameManager_Types.h
		GameManager.h
		GameManager.c		
)

target_include_directories(GameManager
		PUBLIC							  
		./	
)

target_link_libraries(GameManager 			# add libraries which shall be linked to the target lib
   PUBLIC
   src::GameLogic)  

															  
