//#include "ray_tracer.h"
#include "../includes/rtv1.h"

//MLX
void   init_mlx(t_mlx  *mlx, int winwidth, int winheight, char *title)
{
    mlx->mlx = mlx_init();
    ft_putstr("Initialized mlx\n");
    mlx->window = mlx_new_window(mlx->mlx, winwidth, winheight, title);
    ft_putstr("Initialized window\n");
    initimage(mlx, winwidth, winheight);
    ft_putstr("Initialized image\n");
}

void    initimage(t_mlx *mlx, int winwidth, int winheight)
{
    t_image    *img;
    
    if ((img = (t_image *)malloc(sizeof(t_image))) == NULL)
        return ;
    img->img = mlx_new_image(mlx->mlx, winwidth, winheight);
    img->data = mlx_get_data_addr(img->img,
                                 &img->bpp,
                                 &img->sizeline,
                                 &img->endian);
    img->bpp /= 8;
}

void    putpixelimage(t_image *img, int x, int y, int colour)
{
    //t_image    *image;
    
    //image = mlx->image;
    //if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        //return ;
    *(int *)(img->data + ((x + y * WINWIDTH) * img->bpp)) = colour;
}

//Main

int main(void)//int argc, char *argv[])
{
	t_app	*app;
    t_list  *environment_list;
    
	environment_list = NULL;
	//argv = NULL;
	//if (argc != 2)
	//	ft_putstr("Usage : program   <scene/scene_path>");
	if (!(app = (t_app *)malloc(sizeof(t_app))))
		return (-1);
	init_mlx(&app->mlx, WINWIDTH, WINHEIGHT, "Ray Tracing.");
    environment_list = read_file("./cylinder.ds");
	parse_list(environment_list, app);
	raytracing(app);
	mlx_hook(app->mlx.window, 2, 0, &key_press, &app);
	mlx_hook(app->mlx.window, 17, 0, &ft_close, &app);
	mlx_loop(app->mlx.mlx);
}
