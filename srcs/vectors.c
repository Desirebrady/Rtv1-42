#include "../includes/rtv1.h"

void	vector_normalize(t_vector3 *vector3)
{
	double length_normalized;

   length_normalized = (float)sqrt(vector3->x * vector3->x +
                                   vector3->y * vector3->y +
                                   vector3->z * vector3->z);
   vector3->x /= length_normalized;
   vector3->y /= length_normalized;
   vector3->z /= length_normalized;
}

t_vector3	vector_mult(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3 result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->z * v2->x - v1->x * v2->z;
	result.z = v1->x * v2->y - v1->y * v2->x;
	return (result);
}

t_vector3	vector_sub(t_vector3 v1, t_vector3 v2)
{
	t_vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

double		vector_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vector_scale(double t, t_vector3 *v)
{
	t_vector3 result;

	result.x = v->x * t;
	result.y = v->y * t;
	result.z = v->z * t;
	return (result);
}

t_vector3	vector_add(t_vector3 v1, t_vector3 v2)
{
	t_vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}