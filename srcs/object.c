#include "../includes/rtv1.h"

t_vector3       transform_all(double **m, t_vector3 dir)
{
    t_vector3   vec;

    //Handle all
    vec.x = dir.x * m[0][0] + dir.y * m[0][1] + dir.z * m[0][2] + m[0][3];
    vec.y = dir.x * m[1][0] + dir.y * m[1][1] + dir.z * m[1][2] + m[1][3];
    vec.z = dir.x * m[2][0] + dir.y * m[2][1] + dir.z * m[2][2] + m[2][3];
    return (vec);
}

t_vector3       transform_rot(double **m, t_vector3 dir)
{
    t_vector3   vec;

    vec.x = dir.x * m[0][0] + dir.y * m[0][1] + dir.z * m[0][2];
    vec.y = dir.x * m[1][0] + dir.y * m[1][1] + dir.z * m[1][2];
    vec.z = dir.x * m[2][0] + dir.y * m[2][1] + dir.z * m[2][2];
    return (vec);
}