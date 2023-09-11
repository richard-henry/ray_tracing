#ifndef _HITABLE_LIST_H
#define _HITABLE_LIST_H

#include"hitable.h"

class hitable_list: public hitable {
    private:
        hitable **list;
        int size;
    public:
        hitable_list(){}
        hitable_list(hitable** l, int n){list = l; size = n;}
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
};

bool hitable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
    hit_record temp_rec;
    bool hit = false;
    double closest = t_max;
    for(int i = 0; i < size; i++){
        if(list[i]->hit(r,t_min, closest, temp_rec)){
            hit = true;
            closest = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit;
}
#endif