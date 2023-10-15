// MondRuntime.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <array> 
#include "MondRuntime.h"
#include "Page/Page.h"
#include "Html/html.h"

int main()
{
	size_t bytecodeSize = 0;
	std::string source = "\
		\
		\
	";

	/*
		TODO
		HTML Parser thing to get template literals
		Read files.
		Inject HTTP request info into environment. ENV.Request/ENV.Response objects like ASP.NET WebForms
	*/

	/*lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	char* bytecode = luau_compile(source.c_str(), source.length(), NULL, &bytecodeSize);
	int result = luau_load(L, "MondRuntime->Main", bytecode, bytecodeSize, 0);
	free(bytecode);
	lua_call(L, 0, 0);

	std::cout << result << std::endl;*/

	/*
	Html::HtmlChunk **chunks = Html::Parse("<html>yada yada <%= Something Cool Here %> </html>")->data();
	int chunkCount = sizeof(chunks);
	std::cout << chunkCount << std::endl;

	for (int i = 0; i < chunkCount; i++) {
		std::cout << "Chunk " << i << ": " << chunks[i]->content << std::endl;
	}
	*/

	Page::Page *page = new Page::Page("index", "<% testVar %>", "local testVar = 'Something cool'; testVar += 5; print(testVar)");

	return 1;
}
