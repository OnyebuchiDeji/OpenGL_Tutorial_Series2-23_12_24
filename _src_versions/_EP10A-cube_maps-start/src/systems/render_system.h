#pragma once
#include "../config.h"
#include "../components/transform_component.h"
#include "../components/render_component.h"
#include "../components/animation_component.h"
#include "../components/component_set.h"

class RenderSystem
{
public:
    RenderSystem(std::vector<unsigned int>& shaders, GLFWwindow* window,
        ComponentSet<TransformComponent>& transforms,
        ComponentSet<RenderComponent>& renderables,
        ComponentSet<AnimationComponent>& animations);    
    ~RenderSystem();
    
    void update();
 
private:
    void build_models();
    void build_geometry();
    /**
     *  This is for the animations...
     *  it is used to keep track of the different frames for every object made... especially the
     *  objects with animations as they would have more than one VBO object
     * 
     *  If not animated, it is a collection with one frame in it; so one VBO.
     
     */
    std::vector<unsigned int>& m_Shaders;
    std::vector<unsigned int> m_VAOs;
    std::vector<unsigned int> m_VBOs;
    std::vector<unsigned int> m_EBOs;

    std::unordered_map<ObjectType, unsigned int> m_ElementsCount;
    std::unordered_map<ObjectType, std::unordered_map<AnimationType, unsigned int>> m_Offsets;

    std::vector<unsigned int> m_Textures;
    unsigned int m_ModelLocation;
    GLFWwindow* m_Window;

    ComponentSet<TransformComponent>& m_Transforms;
    ComponentSet<RenderComponent>& m_Renderables;
    ComponentSet<AnimationComponent>& m_Animations;
};