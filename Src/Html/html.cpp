#include "html.h"

#include <iostream>
/*

TEMPLATE_LITERAL_BEGIN
TEMPLATE_LITERAL_END
TEMPLATE_SCRIPT_BEGIN
TEMPLATE_SCRIPT_END

*/

//std::string templateLiteralBegin = TEMPLATE_LITERAL_BEGIN; 
//std::string templateScriptBegin = TEMPLATE_SCRIPT_BEGIN; 
//std::string templateScriptEnd = TEMPLATE_END;

std::vector<Html::HtmlChunk*>* Html::Parse(std::string input) {
    std::vector<Html::HtmlChunk*> *chunks = new std::vector<Html::HtmlChunk*>();
    
    std::string tempBuffer = "";
    int currentChunkId = 0;

    int currentSymbolPos = 0;

    size_t i = 0;
    for (i = 0; i < input.length(); i++) {
        char c = input[i];

        std::cout << currentChunkId << " | " << c << " | " << input.substr(i, strlen(TEMPLATE_LITERAL_BEGIN)) << std::endl;

        // We can assume that all even chunkIds are HTML chunks.
        // This imposes the limit that the HTML file cannot begin with a literal
        //      (Or could it since it will match below and add an empty string to chunk?? Needs testing)
        if (currentChunkId % 2 == 0) {
            if (input.substr(i, strlen(TEMPLATE_LITERAL_BEGIN)) == TEMPLATE_LITERAL_BEGIN) {
                // Create HtmlChunk from tempBuffer
                auto chunk = new Html::HtmlChunk;
                chunk->content = tempBuffer;
                chunk->type = Html::HtmlChunkType::HTML;

                i += strlen(TEMPLATE_LITERAL_BEGIN);

                tempBuffer = "";
                chunks->push_back(chunk);
                currentChunkId++;
                continue;
            }
        } else {
            // Were in a template, look for end
            if (input.substr(i, strlen(TEMPLATE_END)) == TEMPLATE_END) {
                // Create HtmlChunk from tempBuffer
                auto chunk = new Html::HtmlChunk;
                chunk->content = tempBuffer;

                // TODO Check what type of template we are in, script or literal.
                chunk->type = Html::HtmlChunkType::TEMPLATE_LITERAL;

                i += strlen(TEMPLATE_END);

                tempBuffer = "";
                chunks->push_back(chunk);
                currentChunkId++;
                continue;
            }
        }
        
        tempBuffer += c;
    }

    if (currentChunkId % 2 == 0) {
        // Create HtmlChunk from tempBuffer
        auto chunk = new Html::HtmlChunk;
        chunk->content = tempBuffer;
        chunk->type = Html::HtmlChunkType::HTML;

        i += strlen(TEMPLATE_LITERAL_BEGIN);

        //std::cout << "CHUNK" << currentChunkId << " " << tempBuffer << std::endl;
        tempBuffer = "";
        chunks->push_back(chunk);
        currentChunkId++;
    } else {
        // Were in a template, look for end
        // Create HtmlChunk from tempBuffer
        auto chunk = new Html::HtmlChunk;
        chunk->content = tempBuffer;

        // TODO Check what type of template we are in, script or literal.
        chunk->type = Html::HtmlChunkType::TEMPLATE_LITERAL;

        i += strlen(TEMPLATE_END);

        //std::cout << "CHUNK" << currentChunkId << " " << tempBuffer << std::endl;
        tempBuffer = "";
        chunks->push_back(chunk);
        currentChunkId++;
    }

    // TODO

    return chunks;
}
