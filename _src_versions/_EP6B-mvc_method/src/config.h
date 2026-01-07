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

#include <fstream>
#include <sstream>
#include <string>
