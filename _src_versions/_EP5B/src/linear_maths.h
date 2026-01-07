#   pragma once

#include <cmath>
#define PI 3.1415962

namespace lm
{
    struct mat4
    {
        float entries[16];
    };

    struct vec3
    {
        float entries[3];
    };


    mat4 create_matrix_transform(vec3 translation);

    mat4 create_z_rotation(float angle);

    mat4 create_model_transform(vec3 pos, float angle);
};