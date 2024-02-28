libs = @lua -llua++ -lraylib
flags = -Os -O3
source = src/main.cpp
output = raylua

raylib_compile_flags = -DCMAKE_POSITION_INDEPENDENT_CODE=<<fpic, ON>> -DUSE_WAYLAND=<<compile_wayland, ON>>
raylib_path = raylib/build/raylib
compiler = <<compiler, g++>>
debug_opts = <<with_debug, no_debug>>

run cd raylib; rm -rf build
run cd raylib; cmake -S . -B build $raylib_compile_flags; cd build; make

# Add -L flag to specify the library search path
run $compiler $source -o $output $libs $flags -fPIC -L$raylib_path -D$debug_opts

flags = -Os -O3 -fPIC -shared
source = src/raylib/raylua.cpp
output = raylua.so

run $compiler $source -o $output $libs $flags -L$raylib_path