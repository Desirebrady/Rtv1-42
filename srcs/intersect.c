#include "../includes/rtv1.h"

int		intersect_sphere(t_ray *ray, t_object *object, double n)
{
	t_vector3	l;
	t_vector3	var;

	l = vector_sub(&ray->origin, &object->transform.position);
	var.x = vector_dot(&ray->direction, &ray->direction);
	var.y = 2 * vector_dot(&ray->direction, &l);
	var.z = vector_dot(&l, &l) - pow(object->shape.radius , 2);

	//printf("%f %f %f\n", ray->origin.x, ray->origin.y, ray->origin.z);

	if (solve_quadratic(var) == 1)
	{
		n = 0;//remove when getsurface is used
		//getsurface(n);
		return (1);
	}
	return (0);
}

int		intersect_cylinder(t_ray *ray, t_object *object, double n)
{

	t_vector3	l;
	t_vector3	var;

	l = vector_sub(&ray->origin, &object->transform.position);
	vector_normalize(&object->transform.rotation);
	var.x = vector_dot(&ray->direction, &ray->direction) -  pow(vector_dot(&ray->direction,	&object->transform.rotation), 2);
	var.y = 2 * vector_dot(&ray->direction, &l)- vector_dot(&ray->direction, &object->transform.rotation) * vector_dot(&object->transform.rotation, &l) ;
	var.z = vector_dot(&l, &l) - vector_dot(&object->transform.rotation, &l) - pow(object->shape.radius , 2);
	
if (solve_quadratic(var) == 1)
	{
		n = 0;//remove when getsurface is used
		//getsurface(n);
		return (1);
	}
	return (0);
}

int		intersect_plane(t_ray *ray, t_object *object, double n)
{
	double denom;

	n = 0;
	denom = (vector_dot(&object->transform.rotation, &object->transform.position) - vector_dot(&object->transform.rotation, &ray->origin)) / vector_dot(&object->transform.rotation, &ray->direction);
	if (denom < 0.0001)
		return (-1);
	else
		return (1);
	return (0);
}