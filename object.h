
#ifndef _OBJECT_H
#define _OBJECT_H

#include "ray.h"
#include "vector.h"
#include "colour.h"


class object {

    private:
       

    public:
        object();

        virtual CRGB getColor() { return CRGB(0,0,0); }
        virtual float rayISect(ray r) { return 0; }
        virtual vector3 getNormalAt(vector3 point) { return vector3(0,0,0); }
      
};

object::object() {

}


#endif
