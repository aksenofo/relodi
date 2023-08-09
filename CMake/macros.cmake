#
#  Created on: Sep 8, 2021
#      Author: Alexander Ksenofontov
#

MACRO(include_modules mod_name)
    include_directories(${ROOT_PROJECT}/${mod_name})
ENDMACRO(include_modules)

MACRO(include_rel_modules mod_name)
    include_directories(${mod_name})
ENDMACRO(include_rel_modules)

MACRO(include_3th_modules mod_name)
    include_directories(${ROOT_PROJECT}/3th/${mod_name})
ENDMACRO(include_3th_modules)

MACRO(WINSYBSYSTEM_IF_WIN project)
    set_target_properties(${project} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_target_properties(${project} PROPERTIES LINK_FLAGS_DEBUG   "/SUBSYSTEM:WINDOWS")
ENDMACRO(WINSYBSYSTEM_IF_WIN)