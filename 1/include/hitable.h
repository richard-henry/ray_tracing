#ifndef __HITABLE_H_
#define __HITABLE_H_

#include"ray.h"

vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    }while(p.squared_length() >= 1.0);
    return p;
}

class material;

struct hit_record
{
    double t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record &rec) const = 0;
};

class material {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian: public material{
    public:
    lambertian(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
    private:
        vec3 albedo;
};

vec3 reflect(const vec3& v,const vec3& n){
    vec3 N;
    N = unit_vector(n);
    return v - 2*dot(v,N)*N;
}

class metal : public material{
    public:
        metal(const vec3& a): albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return(dot(scattered.direction(), rec.normal) > 0);
        }
        private:
        vec3 albedo;
};

bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted){
    vec3 uv = unit_vector(v);
    double dt = dot(uv, n);
    double delta = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if(delta > 0){
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(delta);
        return true;
    }
    else
        return false;
}

double schlick(double cos, double ref_idx){
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0+(1-r0)*pow((1-cos),5);
}

class dialectric : public material{
    public:
        dialectric(double ri): ref_idx(ri){}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
            vec3 outward_normal;
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            double ni_over_nt;
            attenuation = vec3(1,1,1);
            vec3 refracted;
            double reflect_prob;
            double cosine;
            if(dot(r_in.direction(), rec.normal) > 0){
                outward_normal = -rec.normal;
                ni_over_nt = ref_idx;
                cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }
            else{
                outward_normal = rec.normal;
                ni_over_nt = 1/ref_idx;
                cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }
            if(refract(r_in.direction(),outward_normal,ni_over_nt,refracted)){
                reflect_prob = schlick(cosine,ref_idx);
            }
            else{
                scattered = ray(rec.p, reflected);
                reflect_prob = 1.0;
            }
            if(drand48() < reflect_prob){
                scattered = ray(rec.p, reflected);
            }
            else{
                scattered = ray(rec.p, refracted);
            }
            return true;
        }   
        private:
        double ref_idx;
};
#endif