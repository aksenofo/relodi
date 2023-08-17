#
#  Created on: Aug 17, 2023
#      Author: Alexander Ksenofontov
#

#--------------------------------------------------------------------------------------------------
SET(relodi_file_sniffer_PACKET
    main.cpp
)

add_executable(relodi-file-sniffer
    ${relodi_file_sniffer_PACKET} 
)

target_link_libraries(relodi-file-sniffer
    ${DEF_MT_LIB}
    ${DEF_SYS_LIB}
)
