#pragma once

/**
    This file is included to include every thing that is needed generically.
    Also,glad should be included before glfw, since glad defines opengl already before glfw.
*/
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//  This is needed to send pointers to the Matrices in GLM
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include <vector>
#include <unordered_map>

#include <fstream>
#include <sstream>
#include <string>


/**
 *  Date: Mon-30-Dec-2024
 * 
 *  Declaring the functions for reading '.obj' files in this file 
 */

namespace ObjLoader
{
    std::vector<std::string> split(std::string line, std::string delimeter);
};

//  Mon-30-Dec-2024
enum class ObjectType
{
    eBox,
    eGirl,
    eRevy
};

//  Tue-31-Dec-2024
enum class AnimationType
{
    //  no animation and running
    eNone, eRun,
};