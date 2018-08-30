#include "ray_tracer.h"

t_scene	*new_scene(void)
{
	t_scene	*s;

	s = (t_scene*)malloc(sizeof(t_scene));
	s->cam = NULL;
	s->lights = NULL;
	s->planes = NULL;
	s->spheres = NULL;
	return (s);
}

t_scene	*get_scene(void)
{
	t_scene	*s;


	s = new_scene();
	return (s);
}