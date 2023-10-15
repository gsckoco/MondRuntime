#include "Page.h"

Page::Page::Page(std::string pageName, std::string htmlSource, std::string luaSource)
{
	size_t bytecodeSize = 0;
    lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	char* bytecode = luau_compile(luaSource.c_str(), luaSource.length(), NULL, &bytecodeSize);
	int result = luau_load(L, (std::string("Page::Page::Page ") + pageName).c_str(), bytecode, bytecodeSize, 0);
	free(bytecode);
	lua_call(L, 0, 0);

    this->chunks = Html::Parse(htmlSource)->data();
	this->chunkCount = sizeof(chunks);
}

Page::Page::~Page()
{
}
