#include "rtv1.h"

t_cone		*new_cone(t_vect *center, double alpha, t_color *color)
{
	t_cone	*c;

	c = (t_cone*)malloc(sizeof(t_cone));
	c->center = center;
	c->alpha = alpha;
	c->color = color;
	return (c);
}

void		add_cone(t_cone *start, t_cone *new)
{
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}

void		delete_cones(t_cone **start)
{
	t_cone	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		delete_vect((*start)->center);
		delete_color((*start)->color);
		(*start)->next = NULL;
		free(*start);
		*start = tmp;
	}
}
