#include "ray_tracer.h"

int intersectRaySphere(t_ray *r, t_sphere *s)
{
	double A;
    t_vec dist;
    double B;
    double C;
    double discr;
	/* A = d.d, the vector dot product of the direction */
    A = vec_mult(&r->dir, &r->dir); 
	
	/* We need a vector representing the distance between the start of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	dist = vec_sub(&r->origin, &s->pos);
	
	/* 2d.(p0 - c) */  
	B = 2 * vec_multi(&r->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	C = vec_mult(&dist, &dist) - (s->radius * s->radius);
	
	/* Solving the discriminant */
	discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	if(discr < 0)
		return (0);
	else
		return (1);
}