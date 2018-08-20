#ifndef RAY_TRACER_H
#define RAY_TRACER_H

//https://www.purplealienplanet.com/node/23
//https://github.com/PurpleAlien/Raytracer/blob/master/triangle.c
//http://fuzzyphoton.tripod.com/howtowrt.htm#step1
//http://flipcode.com/archives/Raytracing_Topics_Techniques-Part_2_Phong_Mirrors_and_Shadows.shtml
#define winx 800
#define winy 800  

//vector
typedef struct s_vec
{
    double  x;
    double  y;
    double  z; 
}               t_vec;

//sphere
typedef struct  s_sphere
{
    t_vec   pos;
    double  radius;
}               t_sphere;

//Colour definition
typedef struct  s_colour
{
    double red;
    double green;
    double blue;
}               t_colour;

//ray
typedef struct  S_ray
{
    t_vec   origin;
    t_vec   dir;
}               t_ray;

// Light definition
typedef struct s_light
{
        t_vec pos;
        t_colour intensity;
}              t_light;


#endif