#include "ray_tracer.h"

void	mlx_win_init(t_win *t)
{
	t->adr = mlx_init();
	t->adr = mlx_new_window(t->adr, winx, winy, win_name);
}