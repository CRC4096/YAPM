#!/bin/bash

set -ex

apt update && apt -y upgrade
apt install -y qt5-default qtquickcontrols2-5-dev qtdeclarative5-dev

#if [[ "${CXX}" == clang* ]]
#then
#    export CXXFLAGS="-stdlib=libc++"
#fi

cmake -H. -BBuild -DCMAKE_BUILD_TYPE=RELEASE -Wdev
cd Build
make -j 2
ctest -V -j 2
