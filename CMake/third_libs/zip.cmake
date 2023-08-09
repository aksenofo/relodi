#
#  Created on: Sep 8, 2021
#      Author: Alexander Ksenofontov
#

if(NOT DEFINED PROJECT_LIBS)
	message(FATAL_ERROR "PROJECT_LIBS has not been defined. Build aborted")
endif()

#--------------------------------------------------------------------------------------------------
#
#--------------------------------------------------------------------------------------------------
function(USE_LIBZIP)

	set(root ${PROJECT_LIBS}/libzip)

    	set(lib_root ${root}/lib)
        link_directories(${lib_root})

	set(result
	    libzip.a
	    PARENT_SCOPE 
	)

endfunction()
