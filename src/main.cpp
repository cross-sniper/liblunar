#include <cstdlib>
#include <lua.hpp>
#include <raylib.h>

//todo: a function to return a value from global(like a background color) or a default value
//preferably made in lua, if possible

void dostring(lua_State *L, const char *string){
    if(luaL_dostring(L, string) != LUA_OK){
        luaL_dostring(L, "raylua.CloseWindow()");
        //interrogate it, and figure out what went wrong
        fprintf(stderr, "A error has ocoured: %s\n", lua_tostring(L, -1));
        lua_close(L);
        exit(1);
    }
}

int main() {
    // Create a new Lua state
    lua_State *L = luaL_newstate();
    if (!L) {
        // Handle error if Lua state creation fails
        fprintf(stderr, "Error: Unable to create Lua state\n");
        return 1;  // Return a non-zero value to indicate failure
    }

    // Open Lua standard libraries
    luaL_openlibs(L);
    // load raylua.so and initialize the window with a width of 800 and height of 600

    dostring(L, "raylua = require('raylua')");
    // Load and execute the Lua script
    if (luaL_dofile(L, "main.lua") != LUA_OK) {
        // Handle error if Lua script loading fails
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        return 1;      // Return a non-zero value to indicate failure
    }
    dostring(L, "raylua.InitWindow(800,600,'raylua - test')");
    dostring(L, "raylua.SetTargetFPS(60)");
    dostring(L, "setup()");
    dostring(L, "while not raylua.WindowShouldClose() do"
        "   raylua.BeginDrawing()"
        "   raylua.ClearBackground(raylua.BLACK)"
        "   loop()"
        "   raylua.EndDrawing()"
        "end");
    dostring(L, "raylua.CloseWindow()");

    // Close Lua state
    lua_close(L);

    return 0;  // Return 0 to indicate successful execution
}
