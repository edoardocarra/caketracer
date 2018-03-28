#include "trace.h"

int main(int argc, char* argv[]) {

    ygl::image4f img = r_tracer::draw_image(200,100);

    return 0;

}