#
#  Created on: Sep 8, 2021
#      Author: Alexander Ksenofontov
#

if(NOT DEFINED PROJECT_LIBS)
    message(FATAL_ERROR "PROJECT_LIBS has not been defined. Aborted.")
endif()

#--------------------------- For diferent types of build (COMMON OPTIONS) 
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
else()
	message(FATAL_ERROR "Model:" ${CMAKE_BUILD_TYPE} " Unknown build_type (it should be Debug|Release|RelWithDebInfo|MinSizeRel)")
endif()

#--------------------------- Detect arch --------------------------------
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
   # 64 bits
   set(ARCH x64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
   # 32 bits
   set(ARCH x86)
else()
    message(FATAL_ERROR "Unknown arch, must be either 32 or 64. Aborted.")
endif()


IF (WIN32)
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/common_windows.cmake)
ELSE()
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/common_posix.cmake)
ENDIF()

INCLUDE (${CMAKE_CURRENT_LIST_DIR}/functions.cmake)
INCLUDE (${CMAKE_CURRENT_LIST_DIR}/macros.cmake)
INCLUDE (${CMAKE_CURRENT_LIST_DIR}/third_libs.cmake)
