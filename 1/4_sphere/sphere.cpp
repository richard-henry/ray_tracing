#include<iostream>
#include<fstream>
#include"ray.h"

bool hit_sphere(const vec3& center, double radius, const ray&r){
    vec3 d = r.origin() - center; 
    double a = dot(r.direction(),r.direction());
    double b = 2*dot(d,r.direction());
    double c = dot(d,d) - radius*radius;
    double delta = b*b - 4*a*c;
    return (delta > 0);

}
vec3 color(const ray &r){
    if(hit_sphere(vec3(0,0,-1),0.3,r))
        return vec3(0,1,0);
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1.0);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::ofstream fout;
    fout.open("P3_4.ppm");
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