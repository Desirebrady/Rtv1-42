/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 09:35:24 by dshumba           #+#    #+#             */
/*   Updated: 2018/09/10 07:10:59 by dshumba          ###   ########.fr       */
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
# define BLACK 0x000000
# define EPSILON 0.0001

# define TRUE 1
# define FALSE 0
# define ANGLE tan(M_PI * 60 * 0.5 / 180.0)
# define ASPECT_RATIO (double)WINWIDTH / (double)WINHEIGHT
# define HIEGHT_INV  1 / (double)WINHEIGHT
# define WIDTH_INV 1 / (double)WINWIDTH
# define ABS(x)  (x >= 0 ? (x) : -(x))

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

typedef struct		s_color
{
	float			r;
	float   		g;
	float			b;
}					t_color;

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
    double          angle; 
}                   t_shape;

typedef struct      s_transform
{
    t_vector3       position;
    t_vector3       rotation;
    double          **to_local;
    double          **to_world;

}                   t_transform;

typedef enum        e_objecttype
{
    T_CAMERA = -2,
    T_PLANE = 1,
    T_CUBE = 2,
    T_SPHERE = 3,
    T_CONE = 4,
    T_CYLINDER = 5,
    T_PYRAMID = 6,
}                   t_objecttype;

typedef struct      s_object
{
    t_vector3       center; 
    double          distance;
    t_vector3       normal;
    t_transform     transform;
    t_shape         shape;
    t_objecttype    object_type;
    int             colour;
    int             material;
}                   t_object;

typedef struct		s_hitpoint
{
	t_vector3		pos;
	t_vector3		normal;
	t_color			color;
	t_object		*object;
}					t_hitpoint;




//Ray

typedef struct      s_ray
{
    t_vector3       origin;
    t_vector3       direction;
    t_hitpoint      hitpoint;
    int             t;
}                   t_ray;

typedef struct		s_light
{
	int				type;
	float			intensity;
	t_vector3		pos;
	t_vector3		dir;
	t_color		    color;
	struct s_light	*next;
}				    t_light;

//App
typedef struct      s_app
{
    t_ray           ray;
    t_mlx           mlx;
    t_list          *read_list;
    t_object        *objects;
    int             objectcount;
    int             colour;
    t_hitpoint      hit;
    t_light         *light;
	int             n;
}                   t_app;

//mlx
void                init_mlx(t_mlx  *mlx, int winwidth, int winheight,
                             char *title);
void                putpixelimage(t_image *image, int winwidth, int x, int y, int colour);
void                initimage(t_mlx *mlx, int winwidth, int winheight);

//Reader
t_list              *read_to_list_arg(int argc, char **argv, t_list *ret);
t_list              *read_to_list(char *path, t_list *ret);
t_list              *read_file(char *path);

//Parse
void                parse_list(t_list *lst, t_app *app);


//Ray Tracing
void                raytracing(t_app *app);
t_object            *trace(t_ray *ray, t_app *app, double n);

//Intercect calculations
int                 intersect_sphere(t_ray *ray, t_object *object, double n);
//t_object		    *intersect_plane(t_ray *ray, t_object *obj, double *n);
float               intersect_cylinder(t_object *cylinder, t_ray *ray, double n);
int	                intersect_plane(t_ray ray, t_object *plane, double *dis);
float               intersect_cone(t_ray *ray, t_object *cone);


//utils
int                 solve_quadratic(t_vector3 q);
void                display_percentage(int num);
int                 key_press(int keycode);
int                 ft_close(void);
double		        convert_to_deg(double radian);
double		        convert_to_radian(double degrees);
int                 ft_rm_char(char *dest, char c);

//color
t_color 			scalar_color(float scalar, t_color color);
t_color             diffuse(t_vector3 n, t_color surfaceColor, int lightNum);
t_color 			average_color(t_color color);
t_color	    		mult_color(t_color color1, t_color color2);
t_color		    	new_color(int color);
int		    		get_colour_hit(t_ray *ray, t_app *app);


//vectors
t_vector3           vector_scale(double t, t_vector3 *v);
t_vector3           vector_add(t_vector3 v1, t_vector3 v2);
double              vector_dot(t_vector3 v1, t_vector3 v2);
t_vector3	        vector_sub(t_vector3 v1, t_vector3 v2);
t_vector3	        vector_mult(t_vector3 *v1, t_vector3 *v2);
void	            vector_normalize(t_vector3 *vector3);
float               vector_points_to_distance(t_vector3 v1, t_vector3 v2);
void                vector3_multiply_float(t_vector3 v1, float value, t_vector3 *ret);
void		        vector_free(t_vector3 *v);
t_vector3           get_vector3(char *str);

//Matrix
double              **set_matrix_identity();
double              **matrix_multiply(double **m1, double **m2);
int                 matrix_inverse(double **m, double **out);

//Object
t_vector3           transform_all(double **m, t_vector3 dir);
t_vector3           transform_rot(double **m, t_vector3 dir);

//shadow
int                 inShadow(t_ray ray);
t_ray               calcShadowRay(t_vector3 p, t_light lightSource);
#endif

