########################
# Fungus2D Tests CMake #
########################
cmake_minimum_required( VERSION 2.6 )

project( Fungus2D )

#########
# Tests #
#########

add_executable( PlatformerTest platformer.cpp )
target_link_libraries( PlatformerTest Fungus2D ${LIBRARIES} )

######################
# MSVC configuration #
######################
if(WIN32)
	if(MSVC)
	    set_target_properties( PlatformerTest PROPERTIES
								WIN32_EXECUTABLE true
								LINK_FLAGS_RELEASE -s
								DEBUG_POSTFIX "_d")
	endif(MSVC)
endif(WIN32)
