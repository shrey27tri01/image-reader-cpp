#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PPM.h"

int main(int argc, char** argv) {
    PPM ppm;
    PPMImage *image;
    char* filename = argv[1];
    image = ppm.readPPM(filename);
    ppm.changeColorPPM(image);
    ppm.writePPM("outfile.ppm", image);
    return 0;
}