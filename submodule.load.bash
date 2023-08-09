#!/bin/bash
#    Author: Alexander Ksenofontov
#    License: MIT
#    All right reserved

echo -----------------------------------------------------------------------------
echo Update modules
echo ----------------------------------------------------------------------------


#git submodule add https://github.com/zeux/pugixml.git 3th-submodule/pugixml
#git submodule add https://github.com/yuhaoth/minilzo.git 3th-submodule/minilzo
#git submodule add https://github.com/p-ranav/argparse.git 3th-submodule/argparse

git submodule init
git submodule update

