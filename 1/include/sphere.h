#ifndef __SPHERE_H_
#define __SPHERE_H_

#include"hitable.h"

class sphere: public hitable{
    private:
        vec3 center;
        double radius;
        material* m_ptr;
    public:
        sphere(){}
        sphere(vec3 cen, double r):center(cen), radius(r) {};
        sphere(vec3 cen, double r, material* m):center(cen),radius(r),m_ptr(m) {};
        virtual bool hit(const ray& r, double tmin, double tmax, hit_record & rec) const;
};

bool sphere::hit(const ray& r, double tmin, double tmax, hit_record & rec) const {
    vec3 d = r.origin() - center;
    double a = dot(r.direction(),r.direction());
    double b = 2*dot(d,r.direction());
    double c = dot(d,d) - radius*radius;
    double delta = b*b - 4*a*c;
    if (delta > 0){
        double tmp = (-b - sqrt(delta)) / (2*a);
        if(tmp < tmax && tmp > tmin){
            rec.p = r.point_at_parameter(tmp);
            rec.t = tmp;
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = m_ptr;
            return true;
        }
        tmp = (-b + sqrt(delta)) / (2*a);
        if(tmp < tmax && tmp > tmin){
            rec.p = r.point_at_parameter(tmp);
            rec.t = tmp;
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = m_ptr;
            return true;
        }
    }
    return false;
}

#endif