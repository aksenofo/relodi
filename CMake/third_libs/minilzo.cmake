#  Created on: Jul 24, 2023
#      Author: Alexander Ksenofontov
#
function(USE_MINILZO)

       include_directories(${PROJECT_3TH_MODULE})
       set(result_minilzo_c
           ${PROJECT_3TH_MODULE}/minilzo/minilzo.c
           PARENT_SCOPE
       )

endfunction()
