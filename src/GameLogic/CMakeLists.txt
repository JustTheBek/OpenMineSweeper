add_library(GameLogic STATIC)
add_library(src::GameLogic ALIAS GameLogic) 

target_sources(GameLogic		
		PRIVATE
		GameLogic_Types.h
		GameLogic.h
		GameLogic.c		
)

target_include_directories(GameLogic
		PUBLIC							  
		./	
)

#target_link_libraries(GameLogic 			# add libraries which shall be linked to the target lib
#   PUBLIC
#   ...)  