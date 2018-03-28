#include "trace.h"

namespace r_tracer {

    ygl::vec3f color(ray r) {
        //versore di v = v/norma(v)
        ygl::vec3f versor = r.direction()/length(r.direction());
        float t = 0.5 *(versor.y + 1.0);
        return float((1.0-t))*ygl::vec3f(1,1,1)+t*ygl::vec3f(0.5,0.7,1.0);
    }

    ygl::vec3f ray_cast(ygl::vec3f A, ygl::vec3f B) {
        ray r{A,B};
        return color(r);
    }

    ygl::image4f draw_image(int width, int height) {

        ygl::vec3f llc(-2.0,-1.0,-1.0);
        ygl::vec3f horiz(4.0,0.0,0.0);
        ygl::vec3f vert(0.0,2.0,0.0);
        ygl::vec3f origin(0.0,0.0,0.0);

        ygl::image4f result = ygl::image4f();

        for(int j=height-1; j>=0; j--) {
            for(int i=0; i<width; i++) {
                float u = float(i) / float(width);
                float v = float(j) / float(height);
                ygl::vec3f color = ray_cast(origin, llc+u*horiz+v*vert);
                result.at(i,j) = ygl::vec4f(float(255.99)*color.x,float(255.99)*color.y,float(255.99)*color.z,1);
            }
        }

        return result;
    }

}

