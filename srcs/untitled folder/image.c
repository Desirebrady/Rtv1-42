#include "ray_tracer.h"

t_img			*init_img(void)
{
	t_win	*win;
	t_img	*img;

	win = init_env();
	img = (t_img*)malloc(sizeof(t_img));
	img->adr = mlx_new_image(win->adr, winx, winy);
	img->img = mlx_get_data_addr(img->adr, &img->bpp,
									&img->size_lne, &img->end);
	return (img);
}