/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 11:55:53 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/28 11:55:55 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/rtv1.h"

t_object    *trace(t_ray *ray, t_app *app, double n)
{
    int i;
    t_object *hit_object;

    i = -1;
	hit_object = NULL;
    while (++i < app->objectcount)
    {
        if (app->objects[i].object_type == T_SPHERE)
        {
            if (intersect_sphere(ray, &app->objects[i], n) == 1)
                hit_object = &app->objects[i];
        }
        if (app->objects[i].object_type == T_CYLINDER)
        {
            if (intersect_cylinder(ray, &app->objects[i], n) == 1)
                hit_object = &app->objects[i];
        }
        /*if (app->objects[i].object_type == T_PLANE)
        {
            if (intersect_plane(ray, &app->objects[i], n) == 1)
                hit_object = &app->objects[i];
        }*/
    }
    if (hit_object != NULL)
	{
		//printf("Hit object: T_SPHERE\n");
        return (hit_object);
	}
	return (NULL);
}

int     get_colour_hit(t_ray *ray, t_app *app)
{
    double      n;
    t_object    *hitobject;

    n = INFINITY;
    hitobject = trace(ray, app, n);
    if (hitobject != NULL)
        return (hitobject->colour);
    return (0x000000);
}

void    raytracing(t_app *app)
{
    int	x;
	int y;
    double invheight;
    double invwidth;
    double angle = tan(M_PI * 60 * 0.5 / 180.0);
    double aspect_ratio = (double)WINWIDTH / (double)WINHEIGHT;
    t_ray   a;
    int     i;
    
    i = -1;
    invheight = 1 / (double)WINHEIGHT;
    invwidth = 1 / (double)WINWIDTH;
    
    //set origin from camera start pos in the .ds file
    
    while (++i < app->objectcount)
    {
        if (app->objects[i].object_type == T_CAMERA)
        {
            a.origin.x = app->objects[i].transform.position.x;
            a.origin.y = app->objects[i].transform.position.y;
            a.origin.z = app->objects[i].transform.position.z;
        }
    }
    y = -1;
    while (++y < WINHEIGHT)
    {
        x = -1;
        display_percentage(0);
        while (++x < WINWIDTH)
        {
                a.direction.z = -1;
                a.direction.y = (1 - 2 * (y + 0.5) * invheight) * angle;
                a.direction.x = (2 * (x + 0.5) * invwidth - 1) * aspect_ratio * angle;
                vector_normalize(&a.direction);
                app->colour = get_colour_hit(&a, app);
                mlx_pixel_put(app->mlx.mlx, app->mlx.window, x, y, app->colour);
                //putpixelimage(app->mlx.image, x,  y, (int)0xff0000);
        }
    }
    //mlx_put_image_to_window(app->mlx.mlx, app->mlx.window, app->mlx.image->img, 0, 0);
}
