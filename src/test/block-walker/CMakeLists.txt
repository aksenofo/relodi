#
#  Created on: Фгп 2, 2023
#      Author: Alexander Ksenofontov
#

#--------------------------------------------------------------------------------------------------
SET(block_walker_PACKET
    main.cpp
)

add_executable(block-walker
    ${block_walker_PACKET} 
)

target_link_libraries(block-walker
    ${UNCRUSTIFY}
    ${PUGIXML}
    ${DEF_MT_LIB}
    ${DEF_SYS_LIB}
)
