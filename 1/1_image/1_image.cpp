#include<iostream>
#include<fstream>

int main(){
    int nx = 200;
    int ny = 100;
    std::ofstream fout;
    fout.open("P3.ppm");
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    fout << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i<nx; i++){
            float r = float(i) / float(nx);
            float g = float(j) / float(nx);
            float b = 0.5;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            //std::cout << ir << " " << ig << " " << ib << "\n";
            fout << ir << " " << ig << " " << ib << "\n";
         }
    }
    fout.close();
    return 0;
}