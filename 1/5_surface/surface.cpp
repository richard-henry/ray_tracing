#include<iostream>
#include<fstream>
#include<cmath>
#include"ray.h"

double hit_sphere(const vec3& center, double radius, const ray& r){
    vec3 d = r.origin() - center;
    double a = dot(r.direction(),r.direction());
    double b = 2 * dot(d, r.direction());
    double c = dot(d,d) - radius*radius;
    double delta = b*b - 4*a*c;
    if(delta < 0){
        return -1;
    }
    else{
        return (-b - sqrt(delta)) / (2*a);
    }
}

vec3 color(const ray &r){
    double t = hit_sphere(vec3(0,0,-1),0.5,r);
    if(t > 0.0){
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
        return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1);
    }
    else{
        vec3 u_d = unit_vector(r.direction());
        t = 0.5*(u_d.y()+1);
        return (1-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    std::ofstream fout;
    fout.open("P3_5.ppm");
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    fout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2,-1,-1);
    vec3 horizontal(4,0,0);
    vec3 vertical(0,2,0);
    vec3 origin(0,0,0);
    for(int j = ny-1; j >=0; j--){
        for(int i = 0; i < nx; i++){
            double u = double(i)/double(nx);
            double v = double(j)/double(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
    fout.close();
    return 0;
}