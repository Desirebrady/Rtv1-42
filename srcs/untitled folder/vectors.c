#include "ray_tracer.h"

t_vec    vec_sub(t_vec *v1, t_vec *v2)
{
    t_vec result;
    result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return (result);
}

int    vec_mult(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/* Calculate Vector x Scalar and return resulting Vector*/
t_vec vec_scale(float c, t_vec *v)
{
        t_vec result = {v->x * c, v->y * c, v->z * c };
        return result;
}
/* Add two vectors and return the resulting vector */
t_vec vec_add(t_vec *v1, t_vec *v2)
{
        t_vec result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
        return result;
}

