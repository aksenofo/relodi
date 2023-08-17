#
#  Created on: Aug 17, 2023
#      Author: Alexander Ksenofontov
#

include_modules(src/base/common)
USE_ARGPARCE()

#--------------------------------------------------------------------------------------------------
SET(relodi_file_sniffer_PACKET
    main.cpp
)

add_executable(relodi-file-sniffer
    ${relodi_file_sniffer_PACKET} 
)

target_link_libraries(relodi-file-sniffer
    common
    ${DEF_MT_LIB}
    ${DEF_SYS_LIB}
)
