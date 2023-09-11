#include<iostream>
#include<fstream>
#include"sphere.h"
#include"hitablelist.h"
#include"float.h"
#include"camera.h"


vec3 color(const ray& r, hitable *world){
    double k = 0.75;
    hit_record rec;
    if(world->hit(r,0.0,DBL_MAX, rec)){
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return k*color(ray(rec.p, target - rec.p),world); 
    }
    else{
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5*(unit_direction.y() + 1);
        return (1-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1.0);
    }
}

int main(){
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::ofstream fout;
    fout.open("P3_7.ppm");
    fout << "P3\n" << nx << " " << ny << "\n255\n";
    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1),0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hitable *world = new hitable_list(list,2);
    camera cam;
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(0,0,0);
            for(int s = 0; s < ns; s++){
            double u = double(i + drand48()) / double(nx);
            double v = double(j+drand48()) / double(ny);
            ray r = cam.get_ray(u,v);
            vec3 p = r.point_at_parameter(2.0);
            col = col + color(r, world);
            }
            col = col / double(ns);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            fout << ir << " " << ig << " " << ib << "\n";
        }
    } 
    fout.close();
    return 0;
}