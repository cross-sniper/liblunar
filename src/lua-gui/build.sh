#!/usr/bin/env bash
set -e
libs="$(pkg-config --cflags --libs sfml-all) -fPIC"
g++ main.cpp -o ../../lua_gui.so -shared $libs -L imgui -I imgui -limgui