IF (WIN32)
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/xxd-windows.cmake)
ELSE()
    INCLUDE (${CMAKE_CURRENT_LIST_DIR}/xxd-posix.cmake)
ENDIF()
