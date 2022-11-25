#!/usr/bin/env bash

if [ ! -d "build" ]; then
    mkdir build
else
    while getopts ":h" option; do
        case $option in
            r) # rebuild
                rm -fR build/*;;
            \?) # error
                echo "invalid option"
                exit;;
        esac
    done
fi

cd build

cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DTOOLCHAIN_PREFIX="/usr/local/gcc-arm-none-eabi/" \
    -DCMAKE_TOOLCHAIN_FILE="../cmake/toolchain-arm-none-eabi.cmake" \
    -DAPPLICATION="ttn-otaa" \
    -DREGION_EU433="OFF" \
    -DREGION_EU868="ON" \
    -DREGION_US915="OFF" \
    -DREGION_AU915="OFF" \
    -DBOARD="heltec151" \
    -DMBED_RADIO_SHIELD="sx1276" \
    -DUSE_RADIO_DEBUG="ON" ..

#make

cd ..
