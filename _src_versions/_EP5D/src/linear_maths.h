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

    /**
     *  The below are needed to create the Orthonormal bases of the camera...
     *  the forward, right, and up vector. 
     *  These need to be normalized and orthogonal
     * 
     *  A cross product works by taking two vectors, calculating the cross product which results
     *  in a thrid vector perpendicular to the 2 other vectors.
     */
    mat4 create_look_at(vec3 from, vec3 to);

    float dot(vec3 u, vec3 v);

    vec3 normalize(vec3 v);

    vec3 cross(vec3 u, vec3 v);

    mat4 create_perspective_projection(
        float fovy, float aspect, float near, float far
    );
};