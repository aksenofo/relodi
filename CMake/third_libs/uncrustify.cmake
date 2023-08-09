#
#  Created on: Jan 12, 2023
#      Author: Alexander Ksenofontov
#

function(USE_UNCRUSTIFY)

    if (WIN32)
    	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        	set(lib_root ${PROJECT_3TH_MODULE}/uncrustify_build/build-debug-${ARCH}/Debug/)
    	else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        	set(lib_root ${PROJECT_3TH_MODULE}/uncrustify_build/build-release-${ARCH}/Release/)
    	endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    else(WIN32)
        if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
                set(lib_root ${PROJECT_3TH_MODULE}/uncrustify_build/build-debug-${ARCH})
        else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
                set(lib_root ${PROJECT_3TH_MODULE}/uncrustify_build/build-release-${ARCH})
        endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    endif(WIN32)

    set(src_include ${PROJECT_3TH_MODULE}/uncrustify/src)
    include_directories(${src_include})

    if (WIN32)
    	include_directories(${lib_root}/..)
    	include_directories(${lib_root}/../src)
    else()
        include_directories(${lib_root})
    	include_directories(${lib_root}/src)
    endif()

    link_directories(${lib_root})

    set(result
	uncrustify_lib
        PARENT_SCOPE 
    )

endfunction()
