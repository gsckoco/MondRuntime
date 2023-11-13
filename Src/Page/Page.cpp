#include "Page.h"

#include <iostream>

Page::Page::Page(std::string pageName, std::string htmlSource, std::string luaSource)
{
	std::cout << "Constructor" << std::endl;
	size_t bytecodeSize = 0;
    this->L = luaL_newstate();
	luaL_openlibs(L);

// Might be worthwhile in future to precompile the Lua files and execute as required.
	char* bytecode = luau_compile(luaSource.c_str(), luaSource.length(), NULL, &bytecodeSize);
	int result = luau_load(L, (std::string("Page::Page::Page ") + pageName).c_str(), bytecode, bytecodeSize, 0);
	free(bytecode);

    this->chunks = Html::Parse(htmlSource)->data();
	this->chunkCount = sizeof(chunks);
}

Page::Page::~Page()
{
}

bool Page::Page::Execute() {
	std::cout << "Execute" << std::endl;
	int err = lua_pcall(this->L, 0, 0, 0);

    if (err != 0) {
        // Error happened.
        const char *errResult = lua_tostring(L, -1);
        std::cout << "Got error: " << errResult << std::endl;
    }

    return false;
}

void Page::Page::EvaluteExpr(std::string expr) {
	std::cout << "Eval" << std::endl;
    //std::cout << expr << std::endl;
	size_t bytecodeSize = 0;

    std::string wrapped = "return (" + expr + ")";

	char* bytecode = luau_compile(wrapped.c_str(), wrapped.length(), NULL, &bytecodeSize);
	int result = luau_load(L, (std::string("Page::Page::EvaluateExpr ")).c_str(), bytecode, bytecodeSize, 0);
	free(bytecode);

	int err = lua_pcall(L, 0, 1, 0);
    const char *evalResult = lua_tostring(L, -1);

    lua_pop(L, 1); // Clear return.

    std::cout << "Result: " << evalResult << std::endl;
}

std::string Page::Page::Render() {
    return "";
}
