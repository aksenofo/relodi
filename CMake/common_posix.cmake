#
#  Created on: Jan 16, 2017
#      Author: Alexander Ksenofontov
#

#--------------------------- For diferent types of build (PLATFORN OPTIONS) 
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
else()
	message(FATAL_ERROR "Model:" ${CMAKE_BUILD_TYPE} " Unknown build_type (it should be Debug|Release|RelWithDebInfo|MinSizeRel)")
endif()

# Common build attributes
add_definitions(-fPIC -fmessage-length=0 -pthread -Wno-deprecated)

set(DEF_MT_LIB pthread)
set(DEF_SYS_LIB dl)
