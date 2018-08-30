#include "ray_tracer.h"

int		check_line(char *str)
{
	int i;

	i = 0;
	while (str[i] >= 0 && str[i] <= 9)
		i++;
	return (1);
}


int		obj_type(char *line)
{
	int	type;

	ft_strstr(line, "cone") ? type = CONE : 0;
	ft_strstr(line, "plane") ? type = PLANE : 0;
	ft_strstr(line, "sphere") ? type = SPHERE : 0;
	ft_strstr(line, "cylinder") ? type = CYLINDER : 0;
	return (type);
}

t_vec	read_vector(char *line)
{
	int		i;
	int		n;
	char	**split;
	t_vec	vec;

	i = 0;
	n = 0;
	vec = (t_vec) { 0, 0, 0 };
	split = ft_strsplit(line, ' ');
	while (split[i] != NULL && n != 3)
	{
		check_line(split[i]) == 1 ? n++ : 0;
		n == 1 ? vec.x = atof(split[i]) : 0;
		n == 2 ? vec.y = atof(split[i]) : 0;
		n == 3 ? vec.z = atof(split[i]) : 0;
		ft_strdel(&split[i]);
		i++;
	}
	ft_strdel(&split[i]);
	free(split);
	return (vec);
}