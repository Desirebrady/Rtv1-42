#include "ray_tracer.h"

void	init_material(t_material *mat)
{
	mat->color.blue = 0.1;
    mat->color.red = 0.1;
    mat->color.green = 0.1;
	mat->diffuse.diffuse = 0.0;
}

void	init_camera(t_bag *e)
{
	e->ray.pos = (t_vec) { 0.0, 0.0, 0.0 };
	e->ray.dir = (t_vec) { 0.0, 0.0, 1.0 };
	e->ray.rot = (t_vec) { 0.0, 0.0, 0.0 };
	e->ray.fov = 60;
}

void	init_object(t_obj *obj)
{
	obj->type = SPHERE;
	obj->pos = (t_vec) { 0.0, 0.0, 0.0 };
	obj->dir = (t_vec) { 0.0, 0.0, 0.0 };
	obj->scale = 1.0;
}