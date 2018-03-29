#include "trace.h"

namespace r_tracer {

    bool hit_sphere(const ygl::vec3f& center, float radius, ray& r) {
        //t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0 -> quadratic - discriminant
        ygl::vec3f oc = r.origin() - center;
        float a = ygl::dot(r.direction(), r.direction());
        float b = 2*ygl::dot(r.direction(), oc);
        float c = ygl::dot(oc, oc) - radius*radius;
        float discr = b*b - 4*a*c;
        return discr>0;
    }

    ygl::vec3f color(ray& r) {
        //versore di v = v/norma(v)
        if(hit_sphere(ygl::vec3f(0,0,-1), 0.5, r)) return ygl::vec3f(1,0,0);
        ygl::vec3f versor = r.direction()/length(r.direction());
        float t = 0.5 *(versor.y + 1.0);
        return float((1.0-t))*ygl::vec3f(1,1,1)+t*ygl::vec3f(0.5,0.7,1.0);
    }

    ygl::vec3f ray_cast(ygl::vec3f A, ygl::vec3f B) {
        ray r{A,B};
        return color(r);
    }

    ygl::image4b draw_image(int width, int height) {

        ygl::vec3f llc(-2.0,-1.5,-1.0);
        ygl::vec3f horiz(4.0,0.0,0.0);
        ygl::vec3f vert(0.0,3.0,0.0);
        ygl::vec3f origin(0.0,0.0,0.0);

        ygl::image4b result(width,height);

        for(int j=height-1; j>=0; j--) {
            for(int i=0; i<width; i++) {
                float u = float(i) / float(width);
                float v = float(j) / float(height);
                ygl::vec3f color = ray_cast(origin, llc+u*horiz+v*vert);
                result.at(i,j) = ygl::vec4b(ygl::float_to_byte(color.x),
                                            ygl::float_to_byte(color.y),
                                            ygl::float_to_byte(color.z),
                                            ygl::float_to_byte(1));
            }
        }
        return result;
    }

}

