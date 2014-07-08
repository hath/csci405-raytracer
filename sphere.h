
#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include "object.h"
#include "vector.h"
#include "colour.h"

#include <iostream>
using namespace std;


class sphere : public object {
    private:
        vector3 center;
        float radius;
        CRGB color;
       

    public:
        sphere();
        sphere(vector3, float, CRGB);
        vector3 getCenter() { return center; }
        float getRadius() { return radius; }
        CRGB getColor() { return color; }

        vector3 getNormalAt(vector3 point)
        {
            //normal always point away from the center
            vector3 normal = point.add(center.negative()).normalize();
            return normal;
        }

        float rayISect(ray r)
        {

            vector3 rayStart = r.getOrigin();
            float rayStart_x = rayStart.getX(); 
            float rayStart_y = rayStart.getY();            
            float rayStart_z = rayStart.getZ();

            vector3 rayDir = r.getDirection();
            float rayDir_x = rayDir.getX(); 
            float rayDir_y = rayDir.getY();            
            float rayDir_z = rayDir.getZ();

            float a = 1;
            float b = (2*(rayStart_x - center.getX())*rayDir_x)
                    + (2*(rayStart_y - center.getY())*rayDir_y)
                    + (2*(rayStart_z - center.getZ())*rayDir_z);

            float c = pow(rayStart_x - center.getX(), 2)
                    + pow(rayStart_y - center.getY(), 2) 
                    + pow(rayStart_z - center.getZ(), 2)
                    - (radius*radius);

            float discriminant = b*b - 4*a*c;

            if (discriminant >= 0)
            {
                // ray intersects the sphere twice
                float root1 = ((-1*b - sqrt(discriminant))/2);
                
                if (root1 > 0)
                {
                    //the first root is the smallest positive root
                    return root1;
                } 
                else
                {
                    //the second root is the only positive root
                    float root2 = ((sqrt(discriminant)-b)/2)-2;
                    return root2;
                }

            }
            else
            {
                return -1; //ray missed the sphere
            }              
        }

      
};

sphere::sphere() {
    center = vector3(0,0,0);
    radius = 1.0;
    color = CRGB(128,128,128);
}

sphere::sphere(vector3 u, float f, CRGB c) {
    center = u;
    radius = f;
    color = c;
}

#endif
