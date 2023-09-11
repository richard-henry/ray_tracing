#include<iostream>
#include<fstream>
#include"vec3.h"

int main(){
    int nx = 200;
    int ny = 100;
    std::ofstream fout;
    fout.open("P3_2.ppm");
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    fout << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i<nx; i++){
            float r = float(i) / float(nx);
            float g = float(j) / float(nx);
            float b = 0.5;
            vec3 col(r,g,b);
            int ir = int(255.99*col.x());
            int ig = int(255.99*col.y());
            int ib = int(255.99*col.z());
            //std::cout << ir << " " << ig << " " << ib << "\n";
            fout << ir << " " << ig << " " << ib << "\n";
         }
    }
    fout.close();
    return 0;
}