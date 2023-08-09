#
#  Created on: Jul 24, 2023
#      Author: Alexander Ksenofontov
#

MACRO(COMPILE_XXD_COMPRESSED name)

        set (XXD ${PROJECT_UTIL}/xxd-compressed/xxd-compressed)

	get_filename_component(name_wnext ${name} NAME_WE)

        message(STATUS "Run XXD COMPRESSED:" ${XXD} " for:" ${CMAKE_CURRENT_SOURCE_DIR}/${name})
	
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
        ADD_CUSTOM_COMMAND(
                OUTPUT ${name}.cc

		COMMAND echo
		ARGS "'#'include '<'${name}.inc'>'" > ${name}.cc

                COMMAND echo
                ARGS "const char ${name_wnext}[] \= {" >> ${name}.cc

                COMMAND ${XXD}
                ARGS -i ${CMAKE_CURRENT_SOURCE_DIR}/${name} >> ${name}.cc

                COMMAND echo
                ARGS "}\;" >> ${name}.cc

                COMMAND echo
                ARGS "const unsigned int ${name_wnext}_len '=' sizeof'(' ${name_wnext} ');'" >> ${name}.cc

                COMMAND echo
                ARGS "'#'pragma once" > ${name}.inc

                COMMAND echo
                ARGS "extern const char ${name_wnext}'[]' \;" >> ${name}.inc

                COMMAND echo	
                ARGS "extern const unsigned int ${name_wnext}_len\;" >> ${name}.inc


                DEPENDS ${name}
        )
ENDMACRO(COMPILE_XXD_COMPRESSED)
