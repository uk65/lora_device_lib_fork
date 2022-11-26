#!/usr/bin/env bash

#======================================================================

# possible boards
boards=(heltec151)

# possible apps
apps=(ttn-otaa)

board=boards[0]
app=apps[0]
debug="Debug"

#======================================================================

check_board() {
    if printf '%s\0' "${boards[@]}" | grep -Fxqz -- $1; then
        echo "Board '$1' used ..."
        board=$1
    else
        echo "Board '$1' isn't a valid selection. Possible boards:"
        for i in "${boards[*]}";
            do echo "$i";
        done
        exit
    fi
}

check_app() {
    if printf '%s\0' "${apps[@]}" | grep -Fxqz -- $1; then
        echo "App '$1' is built ..."
        app=$1
    else
        echo "App '$1' isn't a valid selection. Possible Apps:"
        for i in "${apps[*]}";
            do echo "$i";
        done
        exit
    fi
}

help() {
    echo "Options:"
    echo "-a app-name"
    echo "-b board"
    echo "-d (Debug-Build)"
    echo "-r (Rebuild ==> clean Build-Directory)"
    exit
}

if [ ! -d "build" ]; then
    mkdir build
fi

while getopts "a:b:dr" option; do
    case $option in
        a) # application
            check_app $OPTARG;;
        b) # board
            check_board $OPTARG;;
        d) # debug
            echo "Debug";;
        r) # rebuild
            echo "clean build directory" 
            rm -fR build/*;;
       \?) # invalid option
            help;;
    esac
done


cd build

cmake \
    -DCMAKE_BUILD_TYPE=$Debug \
    -DTOOLCHAIN_PREFIX="/usr/local/gcc-arm-none-eabi/" \
    -DCMAKE_TOOLCHAIN_FILE="../cmake/toolchain-arm-none-eabi.cmake" \
    -DAPPLICATION="$app" \
    -DREGION="REGION_EU868" \
    -DBOARD="$board" \
    -DMBED_RADIO_SHIELD="sx1276" \
    -DUSE_RADIO_DEBUG="ON" ..

make

cd ..

