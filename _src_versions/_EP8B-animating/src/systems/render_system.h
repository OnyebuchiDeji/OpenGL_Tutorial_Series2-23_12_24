#pragma once
#include "../config.h"
#include "../components/transform_component.h"
#include "../components/render_component.h"
#include "../components/animation_component.h"
#include "../factories/mesh_factory.h"

class RenderSystem
{
public:
    RenderSystem(unsigned int shader, GLFWwindow* window);    

    void update(
        std::unordered_map<unsigned int,TransformComponent>& transformComponents,
        std::unordered_map<unsigned int,RenderComponent>& renderComponents,
        std::unordered_map<unsigned int,AnimationComponent>& animationComponents);
 
private:
    /**
     *  This is for the animations...
     *  it is used to keep track of the different frames for every object made... especially the
     *  objects with animations as they would have more than one VBO object
     * 
     *  If not animated, it is a collection with one frame in it; so one VBO.
     
     */
    std::unordered_map<ObjectType, std::unordered_map<AnimationType, std::vector<unsigned int>>> m_VAOs;
    std::unordered_map<ObjectType, std::unordered_map<AnimationType, std::vector<unsigned int>>> m_VBOs;
    //  Same object has same number of points, despite different frame .obj files
    std::unordered_map<ObjectType, unsigned int> m_VertexCounts;
    //  likewise the same object has the same no. of textures.
    std::unordered_map<ObjectType, unsigned int> m_Textures;
    unsigned int m_ModelLocation;
    GLFWwindow* m_Window;
};