#include "imgui/rlImGui.cpp"
#include "imgui/rlImGui.h"
#include <cstddef>
#include <imgui.h>
#include <lua.h>
#include <lua.hpp>

// Function to set up ImGui with optional dark mode
static int Setup(lua_State *L) {
    bool darkMode = lua_toboolean(L, 1);
    rlImGuiSetup(darkMode);
    return 0;
}

// Wrapper for ImGui Begin function to differentiate from raylib Begin
static int BeginGui(lua_State *_) {
    _ = _; // to stop clangd complaining about unused variable, DO NOT REMOVE THIS(lua_State*_), otherwise compilation fails
    rlImGuiBegin();
    return 0;
}

// Wrapper for ImGui End function to differentiate from raylib End
static int EndGui(lua_State *_) {
    _ = _;
    rlImGuiEnd();
    return 0;
}

// Function to begin an ImGui sub-window
static int BeginSubWindow(lua_State *L){
    const char* name = lua_tostring(L, 1);
    ImGui::Begin(name);
    return 0;
}

// Function to end an ImGui sub-window
static int EndSubWindow(lua_State *L){
    ImGui::End();
    return 0;
}

static int DrawTextSubWindow(lua_State *L){
    const char* text = lua_tostring(L, 1);
    ImGui::Text("%s", text);
    return 0;
}

static int InputFloatSubWindow(lua_State *L){
    const char* label = lua_tostring(L, 1);
    float v = lua_tointeger(L, 2);
    float v_min = lua_tointeger(L, 3);
    float v_max = lua_tointeger(L, 4);
    // Apparently, this returns a boolean
    bool valueChanged = ImGui::SliderFloat(label, &v, v_min, v_max);

    // Return two values: the boolean result and the modified float value
    lua_pushboolean(L, valueChanged);
    lua_pushinteger(L, v);
    // so, i have no idea what i'm supposed to do here
    return 2;
}

// Function to create an ImGui-style window with Begin and End methods
static int Window(lua_State *L){
    const luaL_Reg funcs[] = {
        {"Begin", BeginSubWindow},
        {"End", EndSubWindow},
        {"Text",DrawTextSubWindow},
        {"SliderFloat",InputFloatSubWindow},
        {NULL, NULL}
    };
    luaL_newlib(L, funcs);
    return 1;
}

// Array of Lua functions exposed to Lua scripts
const luaL_Reg funcs[] = {
    {"Setup", Setup},
    {"Begin", BeginGui},
    {"End", EndGui},
    {"Window", Window},
    {NULL, NULL} // Mark the end of the array
};

// Entry point for the Lua C API binding
extern "C" int luaopen_lua_gui(lua_State *L) {
    // Expose functions under the "raygui" namespace
    lua_setglobal(L, "raygui");
    luaL_newlib(L, funcs);
    return 1;
}
