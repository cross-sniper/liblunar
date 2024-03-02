#include <lua.h>
#include <raylib.h>
#include <lua.hpp>
#include "raylib_wrapper.cpp"
#include <iostream>


static luaL_Reg funcs[] = {
	// Add functions to the table using addRaylibFunction
	{ "InitWindow", lua_create_window },
	{ "DrawText", lua_draw_text },
	{ "NewColor", lua_create_color },
	{ "SetWindowTitle", change_title},
	{ "CloseWindow", lua_close_window },
	{ "DrawCircle",lua_draw_circle},
	{ "DrawRectangle", lua_draw_rectangle },
	{ "ClearBackground", lua_fill_bg },
	{ "BeginDrawing", lua_start_drawing },
	{ "EndDrawing", lua_stop_drawing },
	{ "IsKeyDown", lua_is_key_down },
	{ "SetTargetFPS", lua_set_target_fps },
	{ "WindowShouldClose", lua_should_close_window },
	{ "DrawFPS", lua_draw_fps },
	{ "GetFPS", lua_get_fps },
	{ "GetFrameTime", lua_get_frame_time },
	{ "GetMousePosition", lua_get_mouse_position },
	{ "GetScreenWidth", lua_get_screen_width },
	{ "GetScreenHeight", lua_get_screen_height },
	{ NULL,NULL}
};

extern "C" int luaopen_raylua(lua_State *L) {
    // Iterate over the functions and add them to the table
    lua_setglobal(L, "raylua");
    luaL_newlib(L, funcs);
    lua_init_colors(L);

    init_raylib_keys(L);

   // Set the table in the global space with the name "raylua"


    std::cout << "raylua initialized" << std::endl;
    return 1;
}
