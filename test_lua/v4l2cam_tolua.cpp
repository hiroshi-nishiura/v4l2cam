/*
** Lua binding: v4l2cam_lua
** Generated automatically by tolua++-1.0.93 on Fri Apr 27 16:57:21 2018.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_v4l2cam_lua_open (lua_State* tolua_S);

#include "../src/v4l2cam.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_v4l2cam (lua_State* tolua_S)
{
 v4l2cam* self = (v4l2cam*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"v4l2cam");
}

/* method: new of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_new00
static int tolua_v4l2cam_lua_v4l2cam_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   v4l2cam* tolua_ret = (v4l2cam*)  Mtolua_new((v4l2cam)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"v4l2cam");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_new00_local
static int tolua_v4l2cam_lua_v4l2cam_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   v4l2cam* tolua_ret = (v4l2cam*)  Mtolua_new((v4l2cam)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"v4l2cam");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_delete00
static int tolua_v4l2cam_lua_v4l2cam_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_open00
static int tolua_v4l2cam_lua_v4l2cam_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
  int w = ((int)  tolua_tonumber(tolua_S,2,0));
  int h = ((int)  tolua_tonumber(tolua_S,3,0));
  int req_buffers = ((int)  tolua_tonumber(tolua_S,4,3));
  const char* device = ((const char*)  tolua_tostring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   int tolua_ret = (int)  self->open(w,h,req_buffers,device);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_close00
static int tolua_v4l2cam_lua_v4l2cam_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   int tolua_ret = (int)  self->close();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: capture of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_capture00
static int tolua_v4l2cam_lua_v4l2cam_capture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
  bool async = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'capture'", NULL);
#endif
  {
   const void* tolua_ret = (const void*)  self->capture(async);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'capture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: yuv2rgb of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_yuv2rgb00
static int tolua_v4l2cam_lua_v4l2cam_yuv2rgb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
  const void* buffer = ((const void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'yuv2rgb'", NULL);
#endif
  {
   const void* tolua_ret = (const void*)  self->yuv2rgb(buffer);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'yuv2rgb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: width of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_width00
static int tolua_v4l2cam_lua_v4l2cam_width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'width'", NULL);
#endif
  {
   int tolua_ret = (int)  self->width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'width'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: height of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_height00
static int tolua_v4l2cam_lua_v4l2cam_height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'height'", NULL);
#endif
  {
   int tolua_ret = (int)  self->height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'height'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: format of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_format00
static int tolua_v4l2cam_lua_v4l2cam_format00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'format'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->format();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'format'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: is_opened of class  v4l2cam */
#ifndef TOLUA_DISABLE_tolua_v4l2cam_lua_v4l2cam_is_opened00
static int tolua_v4l2cam_lua_v4l2cam_is_opened00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"v4l2cam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  v4l2cam* self = (v4l2cam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'is_opened'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->is_opened();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'is_opened'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_v4l2cam_lua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"v4l2cam","v4l2cam","",tolua_collect_v4l2cam);
  #else
  tolua_cclass(tolua_S,"v4l2cam","v4l2cam","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"v4l2cam");
   tolua_function(tolua_S,"new",tolua_v4l2cam_lua_v4l2cam_new00);
   tolua_function(tolua_S,"new_local",tolua_v4l2cam_lua_v4l2cam_new00_local);
   tolua_function(tolua_S,".call",tolua_v4l2cam_lua_v4l2cam_new00_local);
   tolua_function(tolua_S,"delete",tolua_v4l2cam_lua_v4l2cam_delete00);
   tolua_function(tolua_S,"open",tolua_v4l2cam_lua_v4l2cam_open00);
   tolua_function(tolua_S,"close",tolua_v4l2cam_lua_v4l2cam_close00);
   tolua_function(tolua_S,"capture",tolua_v4l2cam_lua_v4l2cam_capture00);
   tolua_function(tolua_S,"yuv2rgb",tolua_v4l2cam_lua_v4l2cam_yuv2rgb00);
   tolua_function(tolua_S,"width",tolua_v4l2cam_lua_v4l2cam_width00);
   tolua_function(tolua_S,"height",tolua_v4l2cam_lua_v4l2cam_height00);
   tolua_function(tolua_S,"format",tolua_v4l2cam_lua_v4l2cam_format00);
   tolua_function(tolua_S,"is_opened",tolua_v4l2cam_lua_v4l2cam_is_opened00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 LUA_API int luaopen_v4l2cam_lua (lua_State* tolua_S) {
 return tolua_v4l2cam_lua_open(tolua_S);
};
#endif

