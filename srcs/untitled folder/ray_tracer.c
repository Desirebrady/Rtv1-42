#include "ray_tracer.h"

void        ray_tracer(t_bag *e)
{
   int x = -1;
   int y = -1;

    while (++y < winy)
    {
        while (++x < winx)
        {
            mlx_pixel_put(e->win.mlx, e->win.adr,0,0,0x0000ff);
        }
    }
}