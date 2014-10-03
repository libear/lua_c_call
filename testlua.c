
/**
 * @author libearxiong@tencent.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "md5.h"

int chello(lua_State* L)
{
    size_t l;
    const char *message = luaL_checklstring(L, 1, &l);
    lua_pushstring(L, message);
    return 1;
}

int cmd5(lua_State* L)
{
    size_t msg_len;
    const char *msg = lua_tolstring(L,1,&msg_len);
    if (msg_len) {
	char buff[16];
	md5(msg, msg_len, buff);		
	char md5buff[33];
	int i;
	static char map[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	unsigned char byte,half_byte;
	for(i = 0; i < 16; i++) {
            byte = buff[i];
	    half_byte = byte >> 4;
	    md5buff[2*i] = map[half_byte];
	    half_byte = byte & 0x0f;
	    md5buff[2*i + 1] = map[half_byte];
	}
	md5buff[32] = '\0';
	lua_pushstring(L, md5buff);		
    } else {
	lua_pushstring(L, "");
    }
    return 1;
}

static int cToLuaFunc (lua_State* L)
{
    lua_register(L, "chello", chello);
    lua_register(L, "cmd5", cmd5);	
    return 1;
}

/*
 *
 */
int main(int argc, char** argv) 
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    cToLuaFunc(L);
    luaL_loadfile(L, "./test.lua");
    lua_pcall(L, 0, 0, 0);
    
    const char *pstr = "libearxiong";	
    lua_getglobal(L, "showstr");
    lua_pushstring(L, pstr);
    lua_pcall(L, 1, 0, 0);

    lua_getglobal(L, "add");
    lua_pushinteger(L, 20);
    lua_pushinteger(L, 30);
    lua_pcall(L, 2, 1, 0);
    int result = lua_tointeger(L, -1);
    printf("lua add function return val is %d \n", result);
    
    lua_getglobal(L, "swap");
    lua_pushinteger(L, 20);
    lua_pushinteger(L, 30);
    int x = lua_tointeger(L, -1);
    int y = lua_tointeger(L, -2);
    printf("lua swap function return val is %d and %d \n", x, y);

    lua_close(L);
    return (EXIT_SUCCESS);
}
