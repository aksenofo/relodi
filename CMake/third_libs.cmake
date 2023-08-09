#
#  Created on: Sep 8, 2021
#      Author: Alexander Ksenofontov
#

#  inlude QT
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/qt.cmake)

#  inlude Uncrustify
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/uncrustify.cmake)

#  LIBZIP
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/zip.cmake)

#  XXD
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/xxd.cmake)

#  xxd-compressed
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/xxd-compressed.cmake)

#  ARGPARCE
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/argparse.cmake)

# PUGIXML
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/pugixml.cmake)

# magic_enum
include_directories(${PROJECT_SOURCE_DIR}/app/../3th-src/magic_enum/include)

# minilzo
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/third_libs/minilzo.cmake)
