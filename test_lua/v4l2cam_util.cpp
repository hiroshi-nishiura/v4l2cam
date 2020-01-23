#include "lua.hpp"

static int get(lua_State *L)
{
    int w = luaL_checkint(L,-2);
    int h = luaL_checkint(L,-1);
//    const void* data = luaL_checkudata(L,-1,NULL);

    lua_newtable(L);

    lua_pushinteger(L,0);
    lua_pushinteger(L,w);
    lua_settable(L,-3);

    lua_pushinteger(L,1);
    lua_pushinteger(L,h);
    lua_settable(L,-3);

    lua_pushinteger(L,2);
    lua_pushinteger(L,0);
    lua_settable(L,-3);
    return 1;
}

LUA_API int luaopen_v4l2cam_util(lua_State *L)
{
  const luaL_Reg driver[] = 
    {
      {"rgb2tbl", rgb2tbl},
      {NULL, NULL},
    };
    
  luaL_openlib (L, "v4l2cam", driver, 0);
  lua_settable(L, -1);

  return 1;
}
