#include "../includes/rtv1.h"

int			ft_close(void)
{
	exit(1);
	return (0);
}

int			key_press(int keycode)
{
	if (keycode == 53)
		exit(1);
	return (0);
}

int			solve_quadratic(t_vector3 q)
{
	double	d;
    double  r1;
    double  r2;
    double  tmpval;

	r1 = -1;
	r2 = -1;
	d = q.y * q.y - 4 * q.x * q.z;
	if (d < 0)
		return (0);
	r1 = (-q.y + sqrtf(d)) / (2 * q.x);
	r2 = (-q.y - sqrtf(d)) / (2 * q.x);
    if (r2 > r1)
    {
        tmpval = r1;
        r1 = r2;
        r2 = tmpval;
    }
	return (1);
}

double		convert_to_deg(double radian)
{
	double degrees;

	degrees = radian * 180 / M_PI;
	return	(degrees);
}

double		convert_to_radian(double degrees)
{
	double radian;

	radian = degrees * M_PI / 180;
	return	(radian);
}

int ft_rm_char(char *dest, char c)
{
   int removed = 0;
   char *tmp;

   while (*dest)
   {
       tmp = strchr(dest,c);
       if (NULL==tmp)
           break;
       size_t len = strlen(tmp+1);
       memmove(tmp,tmp+1,len);
       tmp[len] = 0;
       ++removed;
       dest=tmp;
   }
   return (removed);
}