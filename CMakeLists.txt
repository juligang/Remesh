# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

project( Retile )
cmake_minimum_required(VERSION 2.8.11)

set(SRC ./src)
file(GLOB SOURCEFILES ${SRC}/*.cpp ${SRC}/*.h ${SRC}/*.hpp)


# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

	message(STATUS "This project requires the CGAL library, and will not be compiled.")
	return()

endif()

# include helper file
include( ${CGAL_USE_FILE} )


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

	message(STATUS "This project requires the Boost library, and will not be compiled.")

	return()

endif()

# include for local directory

# include for local package
include_directories( BEFORE ../src )


# Creating entries for all C++ files with "main" routine
# ##########################################################

include( CGAL_CreateSingleSourceCGALProgram )

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SOURCEFILES})



#project(Retile)
#cmake_minimum_required(VERSION 2.8)

#set(SRC ./src)
#file(GLOB SOURCEFILES ${SRC}/*.cpp ${SRC}/*.h ${SRC}/*.hpp)

############# FIND PACKAGE ###############
#find_package(CGAL COMPONENTS Core )

########### INCLUDES #################
#include_directories(${CGAL_INCLUDE_DIRS})

#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SOURCEFILES})

