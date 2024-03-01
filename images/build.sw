libs = @lua -llua++ -lraylib
flags = -Os -O3 -shared
raylib_path = ../raylib/build/raylib
compiler = <<compiler, g++>>

run $compiler loader.cpp -o ../raylua-images.so $libs $flags -fPIC -L$raylib_path
