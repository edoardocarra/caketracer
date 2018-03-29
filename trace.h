#include <iostream>
#include "yocto/yocto_gl.h"

#ifndef _TRACE_H_
#define _TRACE_H_

namespace r_tracer {

    struct ray{
        ygl::vec3f A;
        ygl::vec3f B;

        ygl::vec3f origin() {return A;};
        ygl::vec3f direction() {return B;};
        ygl::vec3f ray_point(float t) {return A + t*B;};
    };

    ygl::vec3f color(ray& r);
    ygl::vec3f ray_cast(ygl::vec3f A, ygl::vec3f B);
    ygl::image4b draw_image(int width, int height);
}

#endif

