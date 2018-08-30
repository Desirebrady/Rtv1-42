#include "../includes/rtv1.h"

int     intersects(t_app *a, t_ray *ray, t_object *obj)
{
	if (obj->object_type == T_SPHERE)
		return(the spehere)
	else if (obj->object_type == T_PLANE)
		return (get_plane_intersection(r, ray, obj));
	else if (obj->object_type  == T_DISK)
		return (get_disk_intersection(r, ray, obj));
	else if (obj->object_type == T_CYLINDER)
		return (get_cylinder_intersection(r, ray, obj));
	else if (obj->object_type  == T_CONE)
		return (get_cone_intersection(r, ray, obj));
	return (0);
}