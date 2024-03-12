#!/usr/bin/env sh
set -e
# Clean up existing shared libraries
find . -type f -wholename "bin/*.so" -exec rm {} \;
rm -rf bin
mkdir bin

# Define library dependencies and compilation flags
libs="-llua -lm -llua++ -lraylib"
flags="-Os -O3 -Wall -Wfatal-errors"
raylib_compile_flags="-DCMAKE_POSITION_INDEPENDENT_CODE=ON -DUSE_WAYLAND=ON"
debug_opts="no_debug"
raylib_path=raylib/build
# Source file and output names
source="src/raylua.cpp"
output="bin/raylua"

# Compile raylua application
compiler="g++"
$compiler $source -o $output $libs $flags -fPIC -L$raylib_path -D$debug_opts

# Compile raylua shared library
flags="-Os -O3 -fPIC -shared"
source="src/raylib/raylua.cpp"
output="bin/raylua.so"
$compiler $source -o $output $libs $flags -L$raylib_path

cd src/lua-gui
sh build.sh
cd ../..
mv *.so bin
cp -r src/game-scripts bin/game
