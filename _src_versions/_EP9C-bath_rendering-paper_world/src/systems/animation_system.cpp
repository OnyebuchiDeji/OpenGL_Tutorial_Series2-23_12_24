/**
 *  Gets the animation components every frame and updates them:
 */

#include "animation_system.h"

void AnimationSystem::update(
    std::unordered_map<unsigned int, AnimationComponent>& animationComponents, float frameTime)
{
    //  Loop through all
    for (auto& [entity, animation] : animationComponents)
    {
        //  Increment the frame number.
        //  the /16.667  ensures to display the frame rate about 60 times a second
        animation.frame += animation.speed * frameTime / 16.667;

        //  Loop Back
        if (animation.frame >= animation.frameCount){
            animation.frame -= animation.frameCount;
        }
    }
}