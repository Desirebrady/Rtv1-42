#include "../includes/rtv1.h"

void    vector3_multiply_float(t_vector3 v1, float value, t_vector3 *ret)
{
   ret->x = v1.x * value;
   ret->y = v1.y * value;
   ret->z = v1.z * value;
}

float    vector_points_to_distance(t_vector3 v1, t_vector3 v2)
{
    float deltaX;
    float deltaY;
    float deltaZ;
    float distance;

    deltaX = v1.x - v2.x;
    deltaY = v1.y - v2.y;
    deltaZ = v1.z - v2.z;
    distance = (float) sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
    return (distance);
}

t_vector3       get_vector3(char *str)
{
    t_vector3   vector;
    char        **vector_arr;

    ft_rm_char(str, '\n');
    str = ft_strrchr(str++, '(');
    vector_arr = ft_strsplit(str, ' ');
    vector.x = ft_atoi(vector_arr[0]);
    vector.y = ft_atoi(vector_arr[1]);
    vector.z = ft_atoi(vector_arr[2]);
    return (vector);
}

void		vector_free(t_vector3 *v)
{
	if (v)
		free(v);
}