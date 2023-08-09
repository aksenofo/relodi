#  Created on: March 18, 2023
#      Author: Alexander Ksenofontov
#

function(USE_PUGIXML)

    set(lib_root_include ${PROJECT_3TH_MODULE}/pugixml/src)

    include_directories(${lib_root_include})

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(lib_root ${PROJECT_3TH_MODULE}/pugixml_build/build-debug-${ARCH}/${CMAKE_BUILD_TYPE})
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(lib_root ${PROJECT_3TH_MODULE}/pugixml_build/build-release-${ARCH}/${CMAKE_BUILD_TYPE})
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
        set(lib_root ${PROJECT_3TH_MODULE}/pugixml_build/build-release-${ARCH}/${CMAKE_BUILD_TYPE})
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
        set(lib_root ${PROJECT_3TH_MODULE}/pugixml_build/build-release-${ARCH}/${CMAKE_BUILD_TYPE})
    else()
	message(FATAL_ERROR "Model:" ${CMAKE_BUILD_TYPE} " Unknown build_type (it should be Debug|Release|RelWithDebInfo|MinSizeRel)")
    endif()

    link_directories(${lib_root})

    set(result
        pugixml
        PARENT_SCOPE
    )

endfunction()
