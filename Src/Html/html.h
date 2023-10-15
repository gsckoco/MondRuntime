/*
	Handles parsing of html files, finding and replacing
*/

#pragma once

#include <string>
#include <vector>


#define TEMPLATE_LITERAL_BEGIN 	"<%="
#define TEMPLATE_SCRIPT_BEGIN 	"<%lua"
#define TEMPLATE_END 	"%>"

namespace Html {

	enum HtmlChunkType {
		HTML,
		TEMPLATE_LITERAL,
		TEMPLATE_SCRIPT
	};

	struct HtmlChunk
	{
		std::string content;
		enum HtmlChunkType type;
	};

	std::vector<Html::HtmlChunk*>* Parse(std::string input);
}
