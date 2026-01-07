#include "linear_maths.h"

namespace lm
{
    /**
     *  The Translation Matrix:
     *  A = 
     *  (
     *      1 0 0 a
     *      0 1 0 b
     *      0 0 1 c
     *      0 0 0 1
     *  )
     * 
     *  Here, (a, b, c) are the values by which you want to displace the vector the matrix A
     *  multiplies.
     * 
     *  A * vec3(x, y, z)
     *   = (
     *          x + a
     *          y + b
     *          z + c
     *      )
     */
    mat4 create_matrix_transform(vec3 translation)
    {
        mat4 matrix;

        //  Column-Major order
        matrix.entries[0] = 1.0f;
        matrix.entries[1] = 0.0f;
        matrix.entries[2] = 0.0f;
        matrix.entries[3] = 0.0f;

        matrix.entries[4] = 0.0f;
        matrix.entries[5] = 1.0f;
        matrix.entries[6] = 0.0f;
        matrix.entries[7] = 0.0f;

        matrix.entries[8] = 0.0f;
        matrix.entries[9] = 0.0f;
        matrix.entries[10] = 1.0f;
        matrix.entries[11] = 0.0f;

        matrix.entries[12] = translation.entries[0];
        matrix.entries[13] = translation.entries[1];
        matrix.entries[14] = translation.entries[2];
        matrix.entries[15] = 1.0f;

        return matrix;
    }

    /**
     *      (
     *          cosa -sina
     *          sina  cosa
     *      )
    */
    mat4 create_z_rotation(float angle)
    {
        angle = angle * PI / 180.0f;

        mat4 matrix;

        //  The -f species it'll return a floating point value.
        float c = cosf(angle);
        float s = sinf(angle);

        //  Column-Major order
        matrix.entries[0] = c;
        matrix.entries[1] = s;
        matrix.entries[2] = 0.0f;
        matrix.entries[3] = 0.0f;

        matrix.entries[4] = -s;
        matrix.entries[5] =  c;
        matrix.entries[6] = 0.0f;
        matrix.entries[7] = 0.0f;

        matrix.entries[8] = 0.0f;
        matrix.entries[9] = 0.0f;
        matrix.entries[10] = 1.0f;
        matrix.entries[11] = 0.0f;

        matrix.entries[12] = 0.0f;
        matrix.entries[13] = 0.0f;
        matrix.entries[14] = 0.0f;
        matrix.entries[15] = 1.0f;

        return matrix;

    }

    //  Applies both translation and rotation transfroms.
    mat4 create_model_transform(vec3 pos, float angle)
    {
        angle = angle * PI / 180.0f;

        mat4 matrix;

        //  The -f species it'll return a floating point value.
        float c = cosf(angle);
        float s = sinf(angle);

        //  Column-Major order
        matrix.entries[0] = c;
        matrix.entries[1] = s;
        matrix.entries[2] = 0.0f;
        matrix.entries[3] = 0.0f;

        matrix.entries[4] = -s;
        matrix.entries[5] =  c;
        matrix.entries[6] = 0.0f;
        matrix.entries[7] = 0.0f;

        matrix.entries[8] = 0.0f;
        matrix.entries[9] = 0.0f;
        matrix.entries[10] = 1.0f;
        matrix.entries[11] = 0.0f;

        matrix.entries[12] = pos.entries[0];
        matrix.entries[13] = pos.entries[1];
        matrix.entries[14] = pos.entries[2];
        matrix.entries[15] = 1.0f;

        return matrix;
    }

    mat4 create_look_at(vec3 from, vec3 to)
    {
        vec3 global_up = {0.0f, 0.0f, 1.0f};

        //  The point where the camera is looking at - point looking from
        vec3 f = {
            to.entries[0] - from.entries[0],
            to.entries[1] - from.entries[1],
            to.entries[2] - from.entries[2]
        };
        f = normalize(f);

        vec3 r = normalize(cross(f, global_up));    //  ALso uses right-hand rule.
        //  Doesn't this just give back the global_up again?
        vec3 u = normalize(cross(r, f));    //  Results in Up by right-hand rule   

        //  Now construct the View Matrix
        // angle = angle * PI / 180.0f;

        mat4 matrix;

        //  The -f species it'll return a floating point value.
        // float c = cosf(angle);
        // float s = sinf(angle);

        //  Column-Major order
        matrix.entries[0]  = r.entries[0];
        matrix.entries[1]  = u.entries[0];
        matrix.entries[2]  = -f.entries[0];
        matrix.entries[3]  = 0.0f;

        matrix.entries[4]  = r.entries[1];
        matrix.entries[5]  = u.entries[1];
        matrix.entries[6]  = -f.entries[1];
        matrix.entries[7]  = 0.0f;

        matrix.entries[8]  = r.entries[2];
        matrix.entries[9]  = u.entries[2];
        matrix.entries[10] = -f.entries[2];
        matrix.entries[11] = 0.0f;

        matrix.entries[12] = -dot(r, from);
        matrix.entries[13] = -dot(u, from);
        matrix.entries[14] =  dot(f, from);
        matrix.entries[15] = 1.0f;

        return matrix;
    }

    float dot(vec3 u, vec3 v)
    {
        return u.entries[0] * v.entries[0]
             + u.entries[1] * v.entries[1]
             + u.entries[2] * v.entries[2];
    }


    vec3 normalize(vec3 v)
    {
        vec3 u;
        /*
        *   When one takes the dot product of a vector with itself, the result is the
        *   magnitude squared
        */
        float magnitude = sqrtf(dot(v, v));

        u.entries[0] = v.entries[0] / magnitude;
        u.entries[1] = v.entries[1] / magnitude;
        u.entries[2] = v.entries[2] / magnitude;

        return u;
    }
    

    vec3 cross(vec3 u, vec3 v)
    {
        /**
         *  Produces a 3rd vector orthogonal to the other two vectors.
         */
        vec3 w;

        w.entries[0] = u.entries[1] * v.entries[2] - u.entries[2] * v.entries[1];
        w.entries[1] = -(u.entries[0] * v.entries[2] - u.entries[2] * v.entries[0]);
        w.entries[2] = u.entries[0] * v.entries[1] - u.entries[1] * v.entries[0];

        return w;
    }
};