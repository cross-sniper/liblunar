#include "../src/raylib/raylib_colors.cpp"
#include <lauxlib.h>
#include <lua.h>
#include <lua.hpp>
#include <raylib.h>
#include <iostream>

typedef struct Img
{
	Texture2D texture;
	Image image;
	Img(const char* file){
	    this->image = LoadImage(file);
	    if (IsImageReady(this->image)){
	        std::cout << "loading image texture" << std::endl;
	        std::cout << "Image format: " << this->image.format << std::endl;
	        std::cout << "Image width: " << this->image.width << std::endl;
	        std::cout << "Image height: " << this->image.height << std::endl;

	        this->texture = LoadTextureFromImage(this->image); // crash
	        std::cout << "Texture ID: " << this->texture.id << std::endl;
	    }
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

int LuaLoadImage(lua_State *L) {
    const char* file = luaL_checkstring(L, 1);
    printf("Loading image: %s\n", file);
    Img* img = new Img(file);
    Img** imgPtr = (Img**)lua_newuserdata(L, sizeof(Img*));
    *imgPtr = img;

    // Set metatable for the userdata
    luaL_getmetatable(L, "ImgMeta");
    lua_setmetatable(L, -2);

    // Check for errors and push an error message if necessary
    if (!img->texture.id || !img->image.data) {
        delete img;
        return luaL_error(L, "Failed to load image from file: %s", file);
    }
	lua_pushlightuserdata(L, *imgPtr);

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
