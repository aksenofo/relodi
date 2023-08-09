#  Created on: March 18, 2023
#      Author: Alexander Ksenofontov
#

function(USE_PUGIXML)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(lib_root ${PROJECT_3TH_MODULE}/pugixml_build/build-debug-${ARCH})
    else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(lib_root ${PROJECT_3TH_MODULE}/pugixml_build/build-release-${ARCH})
    endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

    set(lib_root_include ${PROJECT_3TH_MODULE}/pugixml/src)

    include_directories(${lib_root_include})

    link_directories(${lib_root})

    set(result
        pugixml
        PARENT_SCOPE
    )

endfunction()
