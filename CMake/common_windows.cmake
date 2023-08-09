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

add_definitions(/D_CRT_SECURE_NO_WARNINGS)
add_definitions(/D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

set(DEF_MT_LIB "")
set(DEF_SYS_LIB "")

