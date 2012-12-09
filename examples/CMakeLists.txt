###########################
# Fungus2D Examples CMake #
###########################
cmake_minimum_required( VERSION 2.6 )

project( Fungus2D )

############
# Examples #
############

add_executable( Platformer platformer.cpp )
target_link_libraries( Platformer Fungus2D ${LIBRARIES} )

######################
# MSVC configuration #
######################
if(WIN32)
	if(MSVC)
	    set_target_properties( Platformer
	        PROPERTIES WIN32_EXECUTABLE true )
	endif(MSVC)
endif(WIN32)
