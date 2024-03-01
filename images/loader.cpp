#include "../src/raylib/raylib_colors.cpp"
#include <lauxlib.h>
#include <lua.h>
#include <lua.hpp>
#include <raylib.h>

typedef struct Img
{
	Texture2D texture;
	Image image;
	Img(const char* file){
		this->image = LoadImage(file);
		this->texture = LoadTextureFromImage(image);
	}

	~Img(){
		UnloadTexture(this->texture);
		UnloadImage(this->image);
	}
} Img;
// Forward declaration
int LuaLoadImage(lua_State *L);
int LuaDrawImage(lua_State *L);
int LuaUnloadImage(lua_State *L);

// Register functions with Lua
void RegisterImgFunctions(lua_State* L) {
    luaL_Reg imgMethods[] = {
        {"LoadImage", LuaLoadImage},
        {"DrawImage", LuaDrawImage},
        {"UnloadImage", LuaUnloadImage},
        {NULL, NULL}
    };

    lua_setglobal(L, "luaimg");
    // Create a metatable for Img
    luaL_newmetatable(L, "ImgMeta");
    luaL_setfuncs(L, imgMethods, 0);
}

// Lua function to create and load an Img object
int LuaLoadImage(lua_State *L) {
    const char* file = luaL_checkstring(L, 1);
    Img* img = new Img(file);
    Img** imgPtr = (Img**)lua_newuserdata(L, sizeof(Img*));
    *imgPtr = img;

    lua_pushlightuserdata(L, imgPtr);

    return 1; // Return the userdata
}

int LuaDrawImage(lua_State *L) {
    Img* img = *(Img**)luaL_checkudata(L, 1, "ImgMeta");
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);
    Color tint = lua_getColor(L, 4);
    DrawTexture(img->texture, x, y, tint);
    return 0;
}


// Lua function to unload an Img object
int LuaUnloadImage(lua_State *L) {
    Img* img = *(Img**)luaL_checkudata(L, 1, "ImgMeta");
    delete img;
    return 0;
}

extern "C" int luaopen_images(lua_State *L){
	RegisterImgFunctions(L);
	return 1;
}
