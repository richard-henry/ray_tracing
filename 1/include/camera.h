#ifndef _CAMERA__H
#define _CAMERA__H

#include "ray.h"

class camera{
    public:
    camera(){
        lower_left_corner = vec3(-2.0,-1.0,-1.0);
        horizontal = vec3(4.0,0.0,0.0);
        vertical = vec3(0.0,2.0,0.0);
        origin = vec3(0,0,0);
    }
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect){
        vec3 u,v,w;
        double theta = vfov*M_PI/180;
        double half_height = tan(theta/2);
        double half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup,w));
        v = cross(w,u);
        lower_left_corner = vec3(-half_width,-half_height,-1);
        lower_left_corner = origin - half_width*u - half_height*v-w;
        horizontal = 2*half_width*u;
        vertical = 2*half_height*v;
        
    }
    ray get_ray(double u, double v){
        return ray(origin, lower_left_corner+u*horizontal+v*vertical-origin);
    }
    private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif