/**
 *  Gets the animation components every frame and updates them:
 */

#include "animation_system.h"

AnimationSystem::AnimationSystem(ComponentSet<AnimationComponent>& animations):
    m_Animations(animations)
{
}


void AnimationSystem::update(float frameTime)
{
    //  Loop through all
    for (AnimationComponent& animation : m_Animations.m_Components){
        animation.frame += animation.speed * frameTime / 16.667f;
        if (animation.frame >= animation.frameCount){
            animation.frame -= animation.frameCount;
        }
    }
}