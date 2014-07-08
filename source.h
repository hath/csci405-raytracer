
#ifndef _SOURCE_H
#define _SOURCE_H

#include "ray.h"
#include "vector.h"
#include "colour.h"



class source {

    private:
       

    public:
        source();

        virtual vector3 getPos() { return vector3(0,0,0); }
        virtual CRGB getColor() { return CRGB(1,1,1); }
      
};

source::source() {

}


#endif
