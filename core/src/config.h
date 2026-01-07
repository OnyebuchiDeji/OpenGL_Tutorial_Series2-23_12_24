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
    "../core/_resources/models/alice.obj",     //Alice
    "../core/_resources/models/ball.obj",      //Ball
    "../core/_resources/models/board.obj",     //Board
    "../core/_resources/models/corner.obj",    //Corner
    "../core/_resources/models/cube.obj",      //Cube
    "../core/_resources/models/demon.obj",     //Demon
    "../core/_resources/models/ghost.obj",    //Demon2  //  no demon2
    "../core/_resources/models/girl.obj",     //Girl2    //  no girl2
    "../core/_resources/models/monkey.obj",     //Girl3  //  no girl3
    "../core/_resources/models/hand_monster.obj",     //Hands
    "../core/_resources/models/monseter_plant.obj", //Plant
    "../core/_resources/models/skull.obj",     //Skull
    "../core/_resources/models/tree.obj",      //Tree
    "../core/_resources/models/wall.obj",      //Wall
};

static std::vector<const char*> imageNames = {
    "../core/_resources/img/Alice_baseColor.png",  //Alice
    "../core/_resources/img/glass.png",            //Ball
    "../core/_resources/img/board.png",            //Board
    "../core/_resources/img/red_brick.png",        //Corner
    "../core/_resources/img/wood.png",             //Cube
    "../core/_resources/img/demon.png",            //Demon
    "../core/_resources/img/demon2.png",           //Demon2
    "../core/_resources/img/stargirl.png",         //Girl2
    "../core/_resources/img/none.png",             //Girl3
    "../core/_resources/img/T_Hands_D02.png",      //Hands
    "../core/_resources/img/PLANT_CLR_002.png",    //Plant
    "../core/_resources/img/skull.png",            //Skull
    "../core/_resources/img/Tree_Texture.png",     //Tree
    "../core/_resources/img/wall.png",             //Wall
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