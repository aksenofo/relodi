#  Created on: March 18, 2023
#      Author: Alexander Ksenofontov
#

IF (WIN32)
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/pugixml-windows.cmake)
ELSE()
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/pugixml-posix.cmake)
ENDIF()

