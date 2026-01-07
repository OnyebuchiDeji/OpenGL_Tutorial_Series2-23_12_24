#pragma once

#include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
//  This is needed to send pointers to the Matrices in GLM
// #include "glm/gtc/type_ptr.hpp"

#include <unordered_map>

#include <string>
#include "vector"


namespace objloader
{
    std::vector<std::string> split(std::string line, std::string delimeter);
};

namespace randutils
{
    int random_int_in_range(int range);
    float random_float();
};

enum class ObjectType
{
    eAlice,
    eBall,
    eBoard,
    eCorner,
    eCube,
    eDemon,
    eDemon2,
    eGirl2,
    eGirl3,
    eHands,
    ePlant,
    eSkull,
    eTree,
    eWall,
};

static std::vector<const char*> modelNames = {
    "../_resources/models/alice.obj",     //Alice
    "../_resources/models/ball.obj",      //Ball
    "../_resources/models/board.obj",     //Board
    "../_resources/models/corner.obj",    //Corner
    "../_resources/models/cube.obj",      //Cube
    "../_resources/models/demon.obj",     //Demon
    "../_resources/models/ghost.obj",    //Demon2  //  no demon2
    "../_resources/models/girl.obj",     //Girl2    //  no girl2
    "../_resources/models/monkey.obj",     //Girl3  //  no girl3
    "../_resources/models/hand_monster.obj",     //Hands
    "../_resources/models/monseter_plant.obj", //Plant
    "../_resources/models/skull.obj",     //Skull
    "../_resources/models/tree.obj",      //Tree
    "../_resources/models/wall.obj",      //Wall
};

static std::vector<const char*> imageNames = {
    "../core/img/Alice_baseColor.png",  //Alice
    "../core/img/glass.png",            //Ball
    "../core/img/board.png",            //Board
    "../core/img/red_brick.png",        //Corner
    "../core/img/wood.png",             //Cube
    "../core/img/demon.png",            //Demon
    "../core/img/demon2.png",           //Demon2
    "../core/img/stargirl.png",         //Girl2
    "../core/img/none.png",             //Girl3
    "../core/img/T_Hands_D02.png",      //Hands
    "../core/img/PLANT_CLR_002.png",    //Plant
    "../core/img/skull.png",            //Skull
    "../core/img/Tree_Texture.png",     //Tree
    "../core/img/wall.png",             //Wall
};

static std::vector<float> scales = {
    0.01f,  //Alice
    0.1f,   //Ball
    0.01f,  //Board
    1.0f,   //Corner
    1.0f,   //Cube
    1.0f,   //Demon
    1.0f,   //Demon2
    1.5f,   //Girl2
    2.0f,   //Girl3
    2.0f,   //Hands
    0.01f,  //Plant
    1.0f,   //Skull
    2.0f,   //Tree
    0.1f,   //Wall
};

struct Mesh{
    uint32_t elementCount, VAO, VBO, EBO, material;
};

constexpr float windowWidth = 1200.0f;
constexpr float windowHeight = 600.0f;

constexpr uint32_t maxObjectCount = 1000;
constexpr uint32_t objectTypeCount = 14;