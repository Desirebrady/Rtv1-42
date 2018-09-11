#include "../includes/rtv1.h"

t_color			limit_color(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (color);
}

t_color			average_color(t_color color)
{
	float	max;

	max = color.r;
	max = color.g > max ? color.g : max;
	max = color.b > max ? color.b : max;
	if (max > 255)
	{
		color.r *= 255 / max;
		color.g *= 255 / max;
		color.b *= 255 / max;
	}
	return (color);
}

t_color			add_color(t_color color1, t_color color2)
{
	color1.r = color1.r + color2.r;
	color1.g = color1.g + color2.g;
	color1.b = color1.b + color2.b;
	return (limit_color(color1));
}

t_color			new_color(int color)
{
	t_color		new_color;

	new_color.b = (color % 256);
	color /= 256;
	new_color.g = (color % 256);
	color /= 256;
	new_color.r = (color % 256);
	return (new_color);
}

t_color			scalar_color(float scalar, t_color color)
{
	color.r *= scalar;
	color.g *= scalar;
	color.b *= scalar;
	return (color);
}

t_color			mult_color(t_color color1, t_color color2)
{
	color1.r = color1.r * color2.r;
	color1.g = color1.g * color2.g;
	color1.b = color1.b * color2.b;
	return (average_color(color1));
}

int				get_colour_hit(t_ray *ray, t_app *app)
{
	double		n;
	t_object	*hitobject;

	n = INFINITY;
	hitobject = trace(ray, app, n);
	if (hitobject != NULL)
		return (hitobject->colour);
	return (0x000000);
}

t_color diffuse(t_vector3 n, t_color surfaceColor, int lightNum) 
{
	t_vector3 *light = NULL;
	float		lightI = 0.0;
	vector_normalize(light);
    float nl = vector_dot(n, light[lightNum]);
    float max = (nl > 0) ? nl : 0;
    float scale = lightI * max;

    return scalar_color(scale,surfaceColor);
}