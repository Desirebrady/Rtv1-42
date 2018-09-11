#include "../includes/rtv1.h"

int				is_in_shadow(t_object *objects, t_ray *ray, t_object *hit_obj)
{
	float		t;
	t_object	*object;
    t_app          *app;
    int i;

	object = objects;
	while (object != NULL)
	{
		if (hit_obj != object)
		{
			if (object->object_type == T_SPHERE)
				t = intersect_sphere(ray, &app->objects[i], app->n);
			if (t > EPSILON && t < ray->t)
				return (TRUE);
		}
		//object = object->next;
	}
	return (FALSE);
}

t_color			specular(t_ray *v_ray, t_light *spot, t_ray *l_ray)
{
	t_color		color;
	t_ray		r_ray;
	float		cos_angle;
	float		spe;
	float		dot;

	cos_angle = 2 * vector_dot(&v_ray->hitpoint.normal, &l_ray->direction);
	r_ray.direction = vector_sub(&vector_scale((double)cos_angle, &v_ray->hitpoint.normal),
		&l_ray->direction);
	//r_ray.direction = vector_normalize(&r_ray.direction);
	dot = vector_dot(&r_ray.direction, &v_ray->direction);
	//if (dot >= 0)
	//	return (new_color(BLACK));
	spe = pow(dot, v_ray->hitpoint.object->material);
	color = scalar_color(spe, spot->color);
	return (color);
}

t_color			diffuse(t_hitpoint hitpoint, t_light *spot, t_ray *ray)
{
	t_color		color;
	float		dot;

	dot = vector_dot(&hitpoint.normal, &ray->direction);
	if (hitpoint.object->object_type == T_PLANE)
		dot = fabs(dot);
	//if (dot <= 0)
	//	return (new_color(BLACK));
	color = scalar_color(dot, mult_color(hitpoint.color, spot->color));
	return (color);
}