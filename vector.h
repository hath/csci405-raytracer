#ifndef _VECTOR_H
#define _VECTOR_H

class vector3 {
    private:
        float x,y,z;

    public:
        vector3();
        vector3(float,float,float);
        float getX() { return x; }
        float getY() { return y; }
        float getZ() { return z; }

        float length() { return sqrt(x*x + y*y + z*z); }    
        vector3 normalize () { float m = length(); return vector3(x/m,y/m,z/m); }
        
        vector3 negative () { return vector3(-x,-y,-z); }

        float dot(vector3 v) { return (v.getX()*x + v.getY()*y + v.getZ()*z); }     

        vector3 cross(vector3 v) {
            return vector3 (y*v.getZ() - z*v.getY(),
                            z*v.getX() - x*v.getZ(),
                            x*v.getY() - y*v.getX());
        }

        vector3 add(vector3 v) { return vector3( x+v.getX(),y+v.getY(),z+v.getZ()); }

        vector3 scalar(float k) { return vector3( x*k, y*k, z*k ); }
};

vector3::vector3() {
    x = 0;
    y = 0;
    z = 0;
}

vector3::vector3(float x0, float y0, float z0) {
    x = x0;
    y = y0;
    z = z0;
}

#endif
