#ifndef _CAMERA_H
#define _CAMERA_H

class camera {
    private:
        vector3 pos, at, right, up;
        

    public:
        camera();
        camera(vector3, vector3, vector3, vector3);
        vector3 getPos() { return pos; }
        vector3 getAt() { return at; }
        vector3 getRight() { return right; }
        vector3 getUp() { return up; }
      
};

camera::camera() {
    pos = vector3(0,0,0);
    at = vector3(0,0,1);
    right = vector3(1,0,0);
    up = vector3(0,1,0);
}

camera::camera(vector3 u,vector3 v, vector3 p, vector3 q) {
    pos = u;
    at = v;
    right = p;
    up = q;
}

#endif
