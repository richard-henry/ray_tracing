#ifndef _VEC3__H_
#define _VEC3__H_

#include<math.h>
#include<stdlib.h>
#include<iostream>

class vec3 {
public:
    vec3(){}
    vec3(double e0, double e1, double e2){
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
        }
    double x() const{return e[0];}
    double y() const{return e[1];}
    double z() const{return e[2];}
    double r() const{return e[0];}
    double g() const{return e[1];}
    double b() const{return e[2];}

    const vec3& operator+() const {return *this;}
    vec3 operator-() const {return vec3(-e[0],-e[1],-e[2]);}
    double operator[](int i) const {return e[i]; }
    double& operator[](int i) { return e[i]; }


    double length() const{
        return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
    }
    friend std::istream& operator>>(std::istream &is, vec3& t){
        is >> t.e[0] >> t.e[1] >> t.e[2];
        return is;
    }
    friend std::ostream& operator<<(std::ostream &os, vec3& t){
        os << t.e[0] << t.e[1] << t.e[2];
        return os;
    }
    void make_unit_vector(){
        double k = 1.0/ ((*this).length());
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }

    vec3 operator+(const vec3& rhs){
        return vec3(e[0]+rhs.e[0],e[1]+rhs.e[1],e[2]+rhs.e[2]);
    }
    vec3 operator-(const vec3& rhs){
        return vec3(e[0]-rhs.e[0],e[1]-rhs.e[1],e[2]-rhs.e[2]);
    }
    vec3 operator*(const vec3& rhs){
        return vec3(e[0]*rhs.e[0],e[1]*rhs.e[1],e[2]*rhs.e[2]);
    }
    vec3 operator/(const vec3& rhs){
        return vec3(e[0]/rhs.e[0],e[1]/rhs.e[1],e[2]/rhs.e[2]);
    }
    vec3 operator*(double t){
        return vec3(e[0]*t,e[1]*t,e[2]*t);
    }
    vec3 operator/(double t){
        return vec3(e[0]/t,e[1]/t,e[2]/t);
    }
    double dot(const vec3& v1, const vec3& v2){
        return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1]+ v1.e[2]*v2.e[2] ;
    }
    vec3 cross(const vec3& v1, const vec3& v2){
        double n_x,n_y,n_z;
        n_x = v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1];
        n_y = v1.e[2]*v2.e[0]-v1.e[0]*v2.e[2];
        n_z = v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0];
        return vec3(n_x,n_y,n_z);
    }
    double squared_length(){
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
private:
    double e[3];
};

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}
inline vec3 operator*(const vec3& v,double t){
    return vec3(t*v.x(),t*v.y(),t*v.z());
}   //A*t
inline vec3 operator*(double t, const vec3& v){
    return vec3(t*v.x(),t*v.y(),t*v.z());
}   //t*A
inline vec3 operator+(const vec3& v1, const vec3& v2){
    return vec3(v1.x()+v2.x(),v1.y()+v2.y(),v1.z()+v2.z());
}
inline vec3 operator-(const vec3& v1, const vec3& v2){
    return vec3(v1.x()-v2.x(),v1.y()-v2.y(),v1.z()-v2.z());
}
inline vec3 operator*(const vec3& v1, const vec3& v2){
    return vec3(v1.x()*v2.x(),v1.y()*v2.y(),v1.z()*v2.z());
}
inline vec3 operator/(const vec3& v1, const vec3& v2){
    return vec3(v1.x()/v2.x(),v1.y()/v2.y(),v1.z()/v2.z());
}
inline double dot(const vec3& v1, const vec3& v2){
    return v1.x()*v2.x()+v1.y()*v2.y()+v1.z()*v2.z();
}
inline vec3 cross(const vec3& v1, const vec3& v2){
    vec3 v;
    v[0] = v1[1]*v2[2]-v1[2]*v2[1];
    v[1] = v1[2]*v2[0]-v2[2]*v1[0];
    v[2] = v1[0]*v2[1]-v1[1]*v2[0];
    return v;
}

#endif