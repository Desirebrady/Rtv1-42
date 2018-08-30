/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 09:35:24 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/28 09:35:26 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>

#define ABS(x)  (x >= 0 ? (x) : -(x))

# define WINWIDTH 800
# define WINHEIGHT 600

//MLX
typedef struct      s_image
{
    void            *img;
    char            *data;
    int             bpp;
    int             sizeline;
    int             endian;
}                   t_image;

typedef struct      s_mlx
{
    void            *mlx;
    void            *window;
    t_image         *image;
    //t_camera        camera;
}                   t_mlx;

//Objects
typedef struct      s_vector3
{
    double x;
    double y;
    double z;
}                   t_vector3;

typedef struct      s_shape
{
    double          width;
    double          height;
    double          depth;
    double          radius;
    double          origin;
}                   t_shape;

typedef struct      s_transform
{
    t_vector3       position;
    t_vector3       rotation;
}                   t_transform;

typedef enum        e_objecttype
{
    T_CAMERA,
    T_PLANE,
    T_CUBE,
    T_SPHERE,
    T_CONE,
    T_CYLINDER,
    T_PYRAMID,
}                   t_objecttype;

typedef struct      s_object
{
    t_transform     transform;
    t_shape         shape;
    t_objecttype    object_type;
    int             colour;
}                   t_object;

//Ray

typedef struct      s_ray
{
    t_vector3       origin;
    t_vector3       direction;
}                   t_ray;

//App
typedef struct      s_app
{
    t_mlx           mlx;
    t_list          *read_list;
    t_object        *objects;
    int             objectcount;
    int             colour;
}                   t_app;

//mlx
void                init_mlx(t_mlx  *mlx, int winwidth, int winheight,
                             char *title);
void                putpixelimage(t_image *img, int x, int y, int colour);
void                initimage(t_mlx *mlx, int winwidth, int winheight);

//Reader
t_list                *read_to_list_arg(int argc, char **argv, t_list *ret);
t_list                *read_to_list(char *path, t_list *ret);
t_list                *read_file(char *path);

//Parse
void    parse_list(t_list *lst, t_app *app);


//Ray Tracing
void    raytracing(t_app *app);

//All Intercect calculations
int	    intersect_sphere(t_ray *ray, t_object *object, double n);
int		intersect_cylinder(t_ray *ray, t_object *object, double n);
int		intersect_plane(t_ray *ray, t_object *object, double n);

//utils
int	        solve_quadratic(t_vector3 q);
void	    display_percentage(int num);
int		    key_press(int keycode);
int		    ft_close(void);

//vectors
t_vector3	vector_scale(double t, t_vector3 *v);
t_vector3	vector_add(t_vector3 *v1, t_vector3 *v2);
double		vector_dot(t_vector3 *v1, t_vector3 *v2);
t_vector3	vector_sub(t_vector3 *v1, t_vector3 *v2);
t_vector3	vector_mult(t_vector3 *v1, t_vector3 *v2);
void	    vector_normalize(t_vector3 *vector3);
#endif

