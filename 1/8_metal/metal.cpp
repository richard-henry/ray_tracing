#include<iostream>
#include<fstream>
#include<math.h>
#include"sphere.h"
#include"hitablelist.h"
#include"float.h"
#include"camera.h"

vec3 color(const ray& r, hitable *world, int depth){
    hit_record rec;
    if(world->hit(r,0.001,DBL_MAX,rec)) {
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            return attenuation*color(scattered, world, depth+1);
        }
        else{
            return vec3(0,0,0);
        }
    }
    else{
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5*(unit_direction.y() + 1.0);
        return (1-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1.0);
    }
    
}

int main(){
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::ofstream fout;
     fout.open("P3_8.ppm");
     fout << "P3\n" << nx << " " << ny << "\n255\n";
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    hitable *list[4];
    list[0] = new sphere(vec3(0,0,-1),0.5, new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1),0.5,new metal(vec3(0.8,0.6,0.2)));
    list[3] = new sphere(vec3(-1,0,-1),0.5, new metal(vec3(0.8,0.8,0.8)));
    hitable *world = new hitable_list(list,4);
    camera cam;
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(0,0,0);
            for(int s = 0; s < ns; s++){
                double u = double(i+drand48()) / double(nx);
                double v = double(j+drand48()) / double(ny);
                ray r = cam.get_ray(u,v);
                vec3 p = r.point_at_parameter(2.0);
                col = col + color(r,world,0);
            }
            col = col / double(ns);
            col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            //std::cout << ir << " " << ig << " " << ib << "\n";
            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
    fout.close();
    return 0;
}