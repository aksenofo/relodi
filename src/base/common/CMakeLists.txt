#
#  Created on: Oct 4, 2018
#      Author: Alexander Ksenofontov

include_directories(.)

#---------------------------------------------------------------------------------------------------
SET(common_PACKET
    common.cpp
    crc.cpp
    format.cpp
    base62_encoder.cpp
    base64_encoder.cpp
    light_search.cpp
    shared_mutex.cpp
    random.cpp
    log.cpp
)

add_library(common
    ${common_PACKET}
)
