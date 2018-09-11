#include "../includes/rtv1.h"

int inShadow(t_ray ray) 
{
	t_object	*object;
	int i;
	double n;
	t_app app;

	i = 0;
    while (&object[i]) 
	{
        if (trace(&ray, &app, n) > 0) 
            return (TRUE);
    }
    return (FALSE);
}

t_ray calcShadowRay(t_vector3 p, t_light lightSource) 
{
    t_ray shadowRay;
    shadowRay.origin = p;
    shadowRay.direction = vector_scale(-1, &lightSource);
    return shadowRay;
}