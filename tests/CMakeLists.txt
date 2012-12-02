########################
# Fungus2D Tests CMake #
########################
cmake_minimum_required( VERSION 2.6 )

project( Fungus2D )

#########
# Tests #
#########

add_executable( CoreStartTest corestart.cpp )
target_link_libraries( CoreStartTest Fungus2D ${LIBRARIES} )

######################
# MSVC configuration #
######################
if(WIN32)
	if(MSVC)
	    set_target_properties( CoreStartTest
	        PROPERTIES WIN32_EXECUTABLE true )
	endif(MSVC)
endif(WIN32)
