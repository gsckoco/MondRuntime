/*
    Page logic, reads FS executes lua code for corresponding lua files
*/

#include <string>

#include "../../Lib/luau/Compiler/include/luacode.h"
#include "../../Lib/luau/VM/include/lua.h"
#include "../../Lib/luau/VM/include/lualib.h"
#include "../Html/html.h"

namespace Page
{
    class Page
    {
    private:
        /* data */
        Html::HtmlChunk **chunks;
        int chunkCount;

        lua_State *L;
    public:
        Page(std::string pageName, std::string htmlSource, std::string luaSource);
        ~Page();

        bool Execute();
        void EvaluteExpr(std::string expr);
        std::string Render();
    };
    
    
} // namespace Page
