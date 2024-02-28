#include <lua.hpp>
#include "raylib_colors.cpp"

#include <raylib.h>
#include <vector>
#include <cstring>

static int lua_is_key_down(lua_State *L) {
  int key = luaL_checkinteger(L, 1);
  lua_pushboolean(L, IsKeyDown(key));
  return 1;
}
static int lua_draw_fps(lua_State *L) {
  int x, y;
  x = luaL_checkinteger(L, 1);
  y = luaL_checkinteger(L, 2);
  DrawFPS(x, y);
  return 0;
}

static int lua_get_time(lua_State *L) {
  lua_pushinteger(L, GetTime());
  return 1;
}

static int lua_get_frame_time(lua_State *L) {
  lua_pushinteger(L, GetFrameTime());
  return 1;
}
static int lua_get_fps(lua_State *L) {
  lua_pushinteger(L, GetFPS());
  return 1;
}

static int lua_set_target_fps(lua_State *L) {
  int TargetFpsToMatch =
      luaL_optinteger(L, 1, 60); // defaults to 60 fps, if no value given
  SetTargetFPS(TargetFpsToMatch);
  return 0;
}


static int lua_draw_rectangle(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);

  Color color;
  color = lua_getColor(L, 5);

  DrawRectangle(posX, posY, width, height, color);
  return 0;
}

// Wrapper function to create a window
static int lua_create_window(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  const char *title = luaL_checkstring(L, 3);
  #ifdef no_debug
  SetTraceLogLevel(LOG_NONE);
  #endif
  InitWindow(width, height, title);
  return 0; // No return values
}

// Wrapper function to close the window
static int lua_close_window(lua_State *L) {
  CloseWindow();
  return 0; // No return values
}

// Wrapper function to clear the background
static int lua_fill_bg(lua_State *L) {
  Color color;
  color = lua_getColor(L, 1);

  ClearBackground(color);
  return 0;
}

// Wrapper function to begin drawing
static int lua_start_drawing(lua_State *L) {
  BeginDrawing();
  return 0;
}

// Wrapper function to end drawing
static int lua_stop_drawing(lua_State *L) {
  EndDrawing();
  return 0;
}

static int change_title(lua_State *L){
  SetWindowTitle(lua_tostring(L,1));
  return 0;
}


static int lua_should_close_window(lua_State *L) {
  lua_pushboolean(L, WindowShouldClose());
  return 1;
}

// Wrapper function to draw text
static int lua_draw_text(lua_State *L) {
  const char *text = luaL_checkstring(L, 1);
  int posX = luaL_checkinteger(L, 2);
  int posY = luaL_checkinteger(L, 3);
  int fontSize = luaL_checkinteger(L, 4);

  Color color;
  color = lua_getColor(L, 5);

  DrawText(text, posX, posY, fontSize, color);

  return 0;
}

static int addRaylibFunction(lua_State *L, int (*function)(lua_State *),
                             const char *name) {
  lua_pushcfunction(L, function);
  lua_setfield(L, -2, name);
  return 1;
}
// RLAPI Vector2 GetMousePosition(void);
static int lua_get_mouse_position(lua_State *L) {
  lua_newtable(L);
  Vector2 mouse_pos = GetMousePosition();
  lua_pushinteger(L, mouse_pos.x);
  lua_setfield(L, -2, "x");
  lua_pushinteger(L, mouse_pos.y);
  lua_setfield(L, -2, "y");
  return 1;
}


#include "raylib_init_helper.cpp"
