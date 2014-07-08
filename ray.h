
#ifndef _RAY_H
#define _RAY_H


class ray {
    private:
        vector3 origin, direction;
        

    public:
        ray();
        ray(vector3, vector3);
        vector3 getOrigin() { return origin; }
        vector3 getDirection() { return direction; }

      
};

ray::ray() {
    origin = vector3(0,0,0);
    direction = vector3(1,0,0);
}

ray::ray(vector3 u,vector3 v) {
    origin = u;
    direction = v;
}

#endif
