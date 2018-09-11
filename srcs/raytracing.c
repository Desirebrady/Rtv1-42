/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 11:55:53 by dshumba           #+#    #+#             */
/*   Updated: 2018/09/10 07:30:35 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object		*trace(t_ray *ray, t_app *app, double n)
{
	int			i;
	t_object	*hit_object;

	i = -1;
	hit_object = NULL;
	while (++i < app->objectcount)
	{
		if (app->objects[i].object_type == T_SPHERE)
		{
			if (intersect_sphere(ray, &app->objects[i], n) == 1)
				hit_object = &app->objects[i];
		}
		else if (app->objects[i].object_type == T_CYLINDER)
		{
			if (intersect_cylinder(&app->objects[i], ray, n) == 1)
				hit_object = &app->objects[i];
		}
		else if (app->objects[i].object_type == T_PLANE)
		{
			if (intersect_plane(*ray, &app->objects[i], &n) == 1)
				hit_object = &app->objects[i];
		}
		/*else if (app->objects[i].object_type == T_CONE)
		 * {
            if (intersect_cone(ray, &app->objects[i]) == 1)
			hit_object = &app->objects[i];
			}*/
	}
	return (hit_object);
}

double			**rotate_x(double angle)
{
	double		**matrix;
	double		radian;

	radian = convert_to_radian(angle);
	matrix = set_matrix_identity();
	matrix[1][1] = cos(radian);
	matrix[1][2] = sin(radian);
	matrix[2][1] = -sin(radian);
	matrix[2][2] = cos(radian);
	return (matrix);
}

double			**rotate_y(double angle)
{
	double		**matrix;
	double		radian;

	radian = convert_to_radian(angle);
	matrix = set_matrix_identity();
	matrix[0][0] = cos(radian);
	matrix[0][2] = -(sin(radian));
	matrix[2][0] = sin(radian);
	matrix[2][2] = cos(radian);
   return matrix;
}

double			**rotate_z(double angle)
{
	double		**matrix;
	double		radian;

	radian = convert_to_radian(angle);
	matrix = set_matrix_identity(radian);
	matrix[0][0] = cos(radian);
	matrix[0][1] = sin(radian);
	matrix[1][0] = -(sin(radian));
	matrix[1][1] = cos(radian);
	return matrix;
}

void			init_matrices(t_app *app)
{
	int		i;
	double	**temp_matrix;
	i = -1;
	while (++i < app->objectcount)
	{
		//Set rotation
		app->objects[i].transform.to_local = set_matrix_identity();
		app->objects[i].transform.to_world = rotate_x(app->objects[i].transform.rotation.x);
		temp_matrix = rotate_y(app->objects[i].transform.rotation.y);
		app->objects[i].transform.to_world = matrix_multiply(app->objects[i].transform.to_world, temp_matrix);
		temp_matrix = rotate_z(app->objects[i].transform.rotation.z);
		app->objects[i].transform.to_world = matrix_multiply(app->objects[i].transform.to_world, temp_matrix);

		//set position
		temp_matrix = set_matrix_identity();
		temp_matrix[0][3] = app->objects[i].transform.position.x;
		temp_matrix[1][3] = app->objects[i].transform.position.y;
		temp_matrix[2][3] = app->objects[i].transform.position.z;
		app->objects[i].transform.to_world = matrix_multiply(app->objects[i].transform.to_world, temp_matrix);
		matrix_inverse(app->objects[i].transform.to_world, app->objects[i].transform.to_local);//change matrix_local to matrix_localtoworld
	}
}

t_object		*init_ray(t_app *app)
{
	int			i;
	
	i = -1;
	
	while (++i < app->objectcount)
    {
		if (app->objects[i].object_type == T_CAMERA)
		{
			app->ray.origin.x = app->objects[i].transform.position.x;
			app->ray.origin.y = app->objects[i].transform.position.y;
			app->ray.origin.z = app->objects[i].transform.position.z;
			return (&app->objects[i]);
		}
	}
	return (NULL);
}

void			raytracing(t_app *app)
{
	double			n = 0.0;
	int			x;
	int 		y;
	t_object	*camera;
//	t_object	*object;
//	t_color		color;
//	int			i = 0;
	
	init_matrices(app);
	if ((camera = init_ray(app)) == NULL)
		return ;
	y = -1;
	t_vector3	light = (t_vector3) { 0, 5, 0};
	
	while (++y < WINHEIGHT)
	{
		x = -1;
		while (++x < WINWIDTH)
		{
			app->ray.direction.z = -1;
			app->ray.direction.y = (1 - 2 * (y + 0.5) * HIEGHT_INV) * ANGLE;
			app->ray.direction.x = (2 * (x + 0.5) * WIDTH_INV - 1) * ASPECT_RATIO * ANGLE;
			app->ray.direction = transform_rot(camera->transform.to_world, app->ray.direction);

			//double t  = 2000;
			vector_normalize(&app->ray.direction);
			app->colour = get_colour_hit(&app->ray, app);
			if(intersect_sphere(&app->ray, app->objects, n) == 1)
			{
				t_vector3 point = vector_add(app->ray.origin, app->ray.direction);
				t_vector3 l = vector_sub(app->objects->transform.position,  point);
				vector_normalize(&l);
				t_vector3 lraydir = vector_sub(light, l);
				vector_normalize(&lraydir);
				//get_sphere_normal(app);
				//t_vector3 n = point;
				 
				float dt = vector_dot(lraydir, point);
				if (dt < 0.0f)
					dt = 0.0f;

				app->colour = app->colour * dt;
				putpixelimage(app->mlx.image,WINWIDTH, x,  y, app->colour);
			}
		}
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.window, app->mlx.image->img, 0, 0);
}
