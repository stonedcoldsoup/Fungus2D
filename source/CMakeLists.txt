cmake_minimum_required (VERSION 2.8)
project ( Fungus2D)

# Build Phoenix Core
add_library( Fungus2D STATIC
	Fungus2D.h
	core.h
	core.cpp
	prng.h
	prng.c
	fismath.h
	fismath.cpp
	)

set_target_properties(Fungus2D PROPERTIES LINK_FLAGS_RELEASE -s )
set_target_properties(Fungus2D PROPERTIES DEBUG_POSTFIX "_d" )	
