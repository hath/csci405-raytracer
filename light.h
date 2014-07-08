
#ifndef _LIGHT_H
#define _LIGHT_H

#include "source.h"
#include "vector.h"
#include "colour.h"


class light : public source {
    private:
        vector3 position;
        CRGB color;

        

    public:
        light();
        light(vector3, CRGB);
        virtual vector3 getPos() { return position; }
        virtual CRGB getColor() { return color; }

      
};

light::light() {
    position = vector3(0,0,0);
    color = CRGB(255,255,255);
}

light::light(vector3 u,CRGB v) {
    position = u;
    color = v;
}

#endif
