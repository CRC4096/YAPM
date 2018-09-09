#!/bin/bash

set -ex

apt-get update
apt-get install -y libstdc++-8-dev clang-6.0 qt5-default qtquickcontrols2-5-dev

if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
fi

mkdir build && cd build

make -j 2
ctest -V -j 2
