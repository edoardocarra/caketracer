#include <iostream>
#include "yocto/yocto_gl.h"

#ifndef _TRACE_H_
#define _TRACE_H_

namespace r_tracer {

    struct ray{


        ygl::vec3f origin() {return A};
        ygl::vec3f direction() {return A};
        ygl::vec3f ray_point(float t) {return A + t*B};

        ygl::vec3f A;
        ygl::vec3f B;


    };


    void raytrace();

}

#endif

