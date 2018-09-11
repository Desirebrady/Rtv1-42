/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 07:01:16 by dshumba           #+#    #+#             */
/*   Updated: 2018/09/10 07:07:50 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				intersect_sphere(t_ray *ray, t_object *object, double n)
{
	t_vector3	l;
	t_vector3	var;

	l = vector_sub(ray->origin, object->transform.position);
	var.x = vector_dot(ray->direction, ray->direction);
	var.y = 2 * vector_dot(ray->direction, l);
	var.z = vector_dot(l, l) - pow(object->shape.radius, 2);
	if (solve_quadratic(var) == 1)
	{
		n = 0;
		/*remove when getsurface is used
		getsurface(n);*/
		return (1);
	}
	return (0);
}

float			intersect_cylinder(t_object *cylinder, t_ray *ray, double n)
{
	float		tmp[2];
	t_vector3	var;
	t_vector3	l;
	
	n = 0;
	l = vector_sub(ray->origin, cylinder->transform.position);
	tmp[0] = vector_dot(ray->direction, cylinder->transform.rotation);
	tmp[1] = vector_dot(l, cylinder->transform.rotation);
	var.x = vector_dot(ray->direction, ray->direction) - pow(tmp[0], 2);
	var.y = 2 * (vector_dot(ray->direction, l) - (tmp[0] * tmp[1]));
	var.z = vector_dot(l, l) - pow(tmp[1], 2) -
			pow(cylinder->shape.radius, 2);
	
	if (solve_quadratic(var) == 1)
	{
		n = 0;
		return (1);
	}
	return (0);
}

/*t_object		*intersect_plane(t_ray *ray, t_object *obj, double *n)
{
	t_ray            tmp_ray;
    t_vector3         normal;
    t_vector3         distacne_to_object;
    t_vector3        hit_point;
    t_vector3        vector_multi;
    float            denominator;
    
    if (obj->object_type != T_PLANE)
        return (NULL);

    tmp_ray.origin = transform_all(obj->transform.to_local, ray->origin);
    tmp_ray.direction = transform_rot(obj->transform.to_local, ray->direction);
    //set_vector3(0, 0, 1, &normal);
	normal = (t_vector3) { 0, 0, 1 };
	denominator = vector_dot(normal, tmp_ray.direction);
    if (denominator < -0.001f)
    {
        double relative_width_min = obj->transform.position.x - (obj->shape.width / 2);
        double relative_width_max = obj->transform.position.x + (obj->shape.width / 2);
        double relative_height_min = obj->transform.position.y - (obj->shape.height / 2);
        double relative_height_max = obj->transform.position.y + (obj->shape.height / 2);
        
        distacne_to_object = vector_sub(obj->transform.position, tmp_ray.origin);
        *n = vector_dot(distacne_to_object, normal) / denominator;
        if (n < 0)
        {
            *n = INFINITY;
            return(NULL);
        }
        //Where the ray intersects with a plane
        vector3_multiply_float(tmp_ray.direction, *n, &vector_multi);
        hit_point = vector_add(tmp_ray.origin, vector_multi);

        if (hit_point.x >= relative_width_min && hit_point.x <= relative_width_max &&
            hit_point.y >= relative_height_min && hit_point.y <= relative_height_max)
        {
            *n = vector_points_to_distance(tmp_ray.origin, hit_point);
            //obj->normal = normal;
            //printf("%f %f %f\n", obj->normal.x, obj->normal.y, obj->normal.z);
            return (obj);
        }
    }
    return (NULL);
}*/

int	intersect_plane(t_ray ray, t_object *plane, double *dis)
{
	double	denom;
	t_vector3	diffrence;
	double	t;

	denom = vector_dot(plane->normal, ray.direction);
	
	if (fabs(denom) > 0.0001)
	{
		diffrence = vector_sub(plane->center, ray.origin);
		vector_normalize(&diffrence);
		t = vector_dot(diffrence, plane->normal) / denom;
		if (t > 0.0001)
		{
			*dis = t;
			return (TRUE);
		}
	}
	return (FALSE);
}

float				inetersect_cone(t_ray *ray, t_object *cone)
{
	t_vector3 		var;
	float			tmp[2];
	t_vector3		l;
	float			taN;

	taN = tan(cone->shape.angle * M_PI / 180);
	l = vector_sub(ray->origin, cone->transform.rotation);
	tmp[0] = vector_dot(ray->direction, cone->transform.rotation);
	tmp[1] = vector_dot(l, cone->transform.rotation);
	var.x = vector_dot(ray->direction, ray->direction) -
			((1 + pow(taN, 2)) * pow(tmp[0], 2));
	var.y = 2 * (vector_dot(ray->direction, l) -
			((1 + pow(taN, 2)) * tmp[0] * tmp[1]));
	var.z = vector_dot(l, l) - (1 + pow(taN, 2) * pow(tmp[1], 2));
	if (solve_quadratic(var) == 1)
		{
			//getsurface(n);
			return (1);
	}
	return (0);
}
