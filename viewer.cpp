#include "trace.h"

int main(int argc, char* argv[]) {

    ygl::image4b img = r_tracer::draw_image(800,600);

    ygl::save_image4b("../results/prova.png",img);

    return 0;

}