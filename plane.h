
#ifndef _PLANE_H
#define _PLANE_H

#include "math.h"
#include "object.h"
#include "vector.h"
#include "colour.h"

#include <iostream>
using namespace std;


class plane : public object {
    private:
        vector3 normal;
        float distance;
        CRGB color;
       

    public:
        plane();
        plane(vector3, float, CRGB);
        vector3 getNormal() { return normal; }
        float getDistance() { return distance; }
        CRGB getColor() { return color; }
        
        vector3 getNormalAt(vector3 point) { return normal; }

        float rayISect(ray r)
        {

            vector3 rayDirection = r.getDirection(); 
            
            float denominator = rayDirection.dot(normal);

            if (denominator == 0)
            {
                return -1;    
            } else {
                float numerator = normal.dot(r.getOrigin().add(normal.scalar(distance).negative()));
                return -1*numerator/denominator;
            }
        }       
              
};

plane::plane() {
    normal = vector3(1,0,0);
    distance = 0.0;
    color = CRGB(128,128,50);
}

plane::plane(vector3 u, float f, CRGB c) {
    normal = u;
    distance = f;
    color = c;
}

#endif
