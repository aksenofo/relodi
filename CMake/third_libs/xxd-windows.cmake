#
#  Created on: Feb 13, 2023
#      Author: Alexander Ksenofontov
#

MACRO(COMPILE_XXD name)

        set (XXD ${PROJECT_UTIL}/xxd/xxd.exe -i)

	get_filename_component(name_wnext ${name} NAME_WE)

        message(STATUS "Run XXD:" ${XXD} " -i for:" ${CMAKE_CURRENT_SOURCE_DIR}/${name})
	
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
        ADD_CUSTOM_COMMAND(
                OUTPUT ${name}.cc

		COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd 
		ARGS "#include <${name}.inc>" > ${name}.cc

                COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd
                ARGS "const char ${name_wnext}[] \= {" >> ${name}.cc

                COMMAND ${XXD}
                ARGS < ${CMAKE_CURRENT_SOURCE_DIR}/${name} >> ${name}.cc

                COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd
                ARGS "}" >> ${name}.cc

                COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd
                ARGS ";const unsigned int ${name_wnext}_len = sizeof( ${name_wnext} );" >> ${name}.cc

                COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd
                ARGS "#pragma once" > ${name}.inc

                COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd
                ARGS "extern const char ${name_wnext}[];" >> ${name}.inc

                COMMAND ${PROJECT_UTIL}/xxd/echo-win-wrapper.cmd
                ARGS "extern const unsigned int ${name_wnext}_len;" >> ${name}.inc


                DEPENDS ${name}
        )
ENDMACRO(COMPILE_XXD)
