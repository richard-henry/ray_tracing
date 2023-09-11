#ifndef __RAY_H_
#define __RAY_H_

#include "vec3.h"

class ray{
    public:
    ray(){}
    ray(const vec3&a, const vec3&b){A = a;B = b; }
    vec3 origin() const { return A; }
    vec3 direction() const {return B; }
    vec3 point_at_parameter(double t) const {return A + (t*B);}
    private:
    vec3 A; //source of ray
    vec3 B; //direction of ray
};
#endif