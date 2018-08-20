#include "ray_tracer.h"

int main(int argc, char *argv){
	
	/* Our ray and a sphere */
	t_sphere s;
	t_ray r;
	
	/* x, y for screen 'resolution' */
	int x,y;	

	/* Intersect ray/sphere or not */
	int hit;

	/* Position the sphere */
	s.pos.x = 20;
	s.pos.y = 20;
	s.pos.z = 20;

	/* Sphere radius */
	s.radius = 10;

	/* Direction of the ray */
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;

	/* Start position of the ray, z coordinate */
	r.origin.z = 0;

	/* Iterate over every 'pixel' of our screen
	 * We use a 40x40 virtual ASCII screen for now
	 */
	for(y=0;y<40;y++){
		/* Set the y-coordinate of the start position of the ray */
		r.origin.y = y; 
		for(x=0;x<40;x++){
			/* Set the x-coordinate of the start position of the ray */
			r.origin.x = x;

			/* Check if the ray intersects with the shpere */
			hit = intersectRaySphere(&r, &s);
			if(hit)
				printf("++");
			else
				printf("--");
		}
		/* First row of the screen done, move to next row */
		printf("\n");
	}

}


int main(int argc, char *argv[])
{
        unsigned char img[winx * winy * 3];
        int i,j;
        i=0;
        while (i<winy)
        {   
            j=0; 
            while(j<winx)
            {
                        if( (j>=250 && j<350) || (i>=200 && i<300) )
                        {
                                img[(j + i*winx)*3 + 0] = 0;
                                img[(j + i*winx)*3 + 1] = 0;
                                img[(j + i*winx)*3 + 2] = 128;
                        }else
                        {
                                img[(j + i*winx)*3 + 0] = 255;
                                img[(j + i*winx)*3 + 1] = 255;
                                img[(j + i*winx)*3 + 2] = 255;
                        }
                        j++;
            } 
            i++;
        }
        saveppm("image.ppm", img, winx, winy);
return 0;
}
/*Within each iteration of the inner for loop, we draw one pixel. 
After one complete cycle of the outer for loop, one horizontal line is fully drawn. 
Within the inner for loop, we decide the colour each pixel will have, 
and set it's triplet (r,g,b) to the correct values. 
Whether a pixel becomes blue or wite is defined by the 
if statement in the inner for loop. It just checks if we are in the 
area of the flag that needs to be blue or white, 
calculated in advance knowing the width and height of the image. 
At the end, the image is written to a file, and you should be able to 
open it with an image viewer. The full version of this program is attached to this post (flag1.c).
Back to our ray tracer. 
We can now go back to the program we made last time and, instead of 
generating an ASCII output with a couple of printf() 
statements we can colour our sphere in any colour we want.
We can also generate an image that is much larger than the 40x40 'image' 
we created before. As an example, let's build an 800x600 image 
with a red sphere on a black background. 
The resulting program is also attached (raytrace_sphere_1.c).
Hardly realistic, but it provides a start to make things look much better. 
The reason why it doesn't look realistic is because we're missing probably 
the most important element of a scene: "Lights, Camera, Action". 
We have the camera and the action (the sphere) - now all we need is light! 
First thing we want to do is change the way colour is assigned. After all, 
colour is a property of the object in question and should hence be assigned as such.
We can change our code a little so that we have an element called 'colour' 
which contains the three colour components of the final shade. 
We can easily do this again with a structure*/