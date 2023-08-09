###################################################################################################
#
#  Created on: Aug 2, 2023
#      Author: Alexander Ksenofontov
#
###################################################################################################

cmake_minimum_required(VERSION 3.12.4)

project(relodi)

cmake_policy(SET CMP0004 OLD)
cmake_policy(SET CMP0008 OLD)

SET(ROOT_PROJECT ${PROJECT_SOURCE_DIR})
SET(PROJECT_LIBS "$ENV{LIB_MNT}/")

set(CMAKE_CXX_STANDARD 17)

#---------------------------------------------------------------------------------------------------
INCLUDE (${ROOT_PROJECT}/CMake/start.cmake)
#---------------------------------------------------------------------------------------------------

add_subdirectory(src)
