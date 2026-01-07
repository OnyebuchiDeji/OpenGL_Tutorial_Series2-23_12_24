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
};