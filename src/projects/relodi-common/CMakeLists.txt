#
#  Created on: Aug 17, 2023
#      Author: Alexander Ksenofontov
#

include_modules(src/base/common)
include_directories(.)

#---------------------------------------------------------------------------------------------------

add_library(relodi-common
    relodi-common.cpp
    header_block0.cpp
    header_block1.cpp
)
