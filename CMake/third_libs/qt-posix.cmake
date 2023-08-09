#
#  Created on: Jan 12, 2023
#      Author: Alexander Ksenofontov
#


function(USE_QT)

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(root ${PROJECT_LIBS}/Qt-debug)
    else ()
        set(root ${PROJECT_LIBS}/Qt)
    endif()

    
    include_directories(${root}/include)
    include_directories(${root}/include/QtCore)
    include_directories(${root}/include/QtGui)
    include_directories(${root}/include/QtWidgets)

    set(lib_root ${root}/lib)
    set(bin_root ${root}/bin)

    link_directories(${lib_root})

    set(result
        Qt5Core
        Qt5Gui
        Qt5Widgets
        PARENT_SCOPE
    )

    set(moc_compiller
	${bin_root}/moc
	PARENT_SCOPE
    )

    set(rcc_compiller
	${bin_root}/rcc
	PARENT_SCOPE
    )

    set(uic_compiller
        ${bin_root}/uic
        PARENT_SCOPE
    )

endfunction()

# USE_QT - must me used before
MACRO(COMPILE_MOC moc_name)
	message(STATUS "Run MOC:" ${moc_compiller} " for:" ${CMAKE_CURRENT_SOURCE_DIR}/${moc_name})

	ADD_CUSTOM_COMMAND(
		OUTPUT ${moc_name}.cc
		COMMAND ${moc_compiller}
		ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${moc_name} > ${moc_name}.cc
		DEPENDS ${moc_name}
 	)
ENDMACRO(COMPILE_MOC)

# USE_QT - must me used before
MACRO(COMPILE_MOC_1 moc_name out_name)

	message(STATUS "Run MOC1:" ${moc_compiller} " for:" ${CMAKE_CURRENT_SOURCE_DIR}/${out_name})
	ADD_CUSTOM_COMMAND(
		OUTPUT ${out_name}
		COMMAND ${moc_compiller}
		ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${moc_name} > ${out_name}
		DEPENDS ${moc_name}
 	)
ENDMACRO(COMPILE_MOC_1)

# USE_QT - must me used before
MACRO(COMPILE_RCC rcc_name)

	message(STATUS "Run RCC:" ${rcc_compiller} " for:" ${CMAKE_CURRENT_SOURCE_DIR}/${rcc_name})

	ADD_CUSTOM_COMMAND(
		OUTPUT ${rcc_name}.vfs.cc
		COMMAND ${rcc_compiller}
		ARGS --compress=4 ${CMAKE_CURRENT_SOURCE_DIR}/${rcc_name} > ${rcc_name}.vfs.cc
		DEPENDS ${rcc_name}
 	)
ENDMACRO(COMPILE_RCC)

# USE_QT - must me used before
MACRO(COMPILE_RCC_EA rcc_name extra_args)

	message(STATUS "Run RCC_EA:" ${rcc_compiller} " for:" ${CMAKE_CURRENT_SOURCE_DIR}/${rcc_name})

        ADD_CUSTOM_COMMAND(
                OUTPUT ${rcc_name}.vfs.cc
                COMMAND ${rcc_compiller}
                ARGS --compress=4 ${extra_args} ${CMAKE_CURRENT_SOURCE_DIR}/${rcc_name} > ${rcc_name}.vfs.cc
                DEPENDS ${rcc_name}
        )
ENDMACRO(COMPILE_RCC_EA)

MACRO(COMPILE_UIC uic_name)
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
        ADD_CUSTOM_COMMAND(
                OUTPUT ${uic_name}.cc
                COMMAND ${uic_compiller}
            	    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${uic_name} > ${uic_name}.h
                COMMAND echo
                    ARGS //just to make a dependency. > ${uic_name}.cc
                DEPENDS ${uic_name}
        )
ENDMACRO(COMPILE_UIC)
