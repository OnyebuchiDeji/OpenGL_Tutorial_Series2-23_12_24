#include "config.h"
//  This defines the below once this cpp file is run.
#define STB_IMAGE_IMPLEMENTATION
#include "_vendor/stb_image.h"


// using namespace ObjLoading;


/**
 * 
 */
namespace ObjLoader
{

    std::vector<std::string> split(std::string line, std::string delimeter)
    {
        //  Stores all the strings that are in a line
        std::vector<std::string> splitLine;

        size_t pos = 0;
        std::string token;

        //  If the delimeter is not found in the line, it returns the end of string token
        //  so while there is a delimeter.
        while((pos = line.find(delimeter)) != std::string::npos)
        {
            //  takes the string from the start of the sentence to where the delimeter is.
            token = line.substr(0, pos);
            splitLine.push_back(token);
            //  This removes both the word that is taken and the delimeter
            line.erase(0, pos + delimeter.size());
        }
        //  For the last word in the sentence...
        //  Because the above gets the words before the delimeter...
        //  when the last one is reached, there might be a word after it.
        //  this line takes that word after the last deloimeter.
        splitLine.push_back(line);

        return splitLine;
    }
}