cmake_minimum_required (VERSION 3.5)

find_package(Lua 5.1 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

message(INFO: ${LUA_LIBRARY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_v4l2.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/v4l2cam_tolua.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND tolua++5.1 -n v4l2cam_lua -o v4l2cam_tolua.cpp v4l2cam_tolua.pkg
  COMMENT "Generating lua bind"
  VERBATIM)

add_library(v4l2cam_lua SHARED ${CMAKE_CURRENT_SOURCE_DIR}/v4l2cam_tolua.cpp)
set_target_properties(v4l2cam_lua PROPERTIES PREFIX "")
target_link_libraries(v4l2cam_lua tolua++5.1 v4l2cam)

add_library(v4l2cam_util SHARED ${CMAKE_CURRENT_SOURCE_DIR}/v4l2cam_util.cpp)
set_target_properties(v4l2cam_util PROPERTIES PREFIX "")

# TOLUA_APIをLUA_APIに変更する必要がある/.soでexportされないようだ
# TOLUA_API int luaopen_v4l2cam_lua (lua_State* tolua_S)
# to
# LUA_API int luaopen_v4l2cam_lua (lua_State* tolua_S)
