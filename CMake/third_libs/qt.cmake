#
#  Created on: Jan 12, 2023
#      Author: Alexander Ksenofontov
#

IF (WIN32)
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/qt-windows.cmake)
ELSE()
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/qt-posix.cmake)
ENDIF()
