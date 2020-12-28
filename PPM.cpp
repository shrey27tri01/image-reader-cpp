#include "PPM.h"
#include <stdio.h>
#include <stdlib.h>

#define RGBCOMPONENTCOLOR 255

PPMImage *PPM::readPPM(const char *filename) {
    char buff[16];
    PPMImage *img;
    FILE *fp;
    int c, rgbCompColor;
    
    //open PPM file for reading
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '3') {
        fprintf(stderr, "Invalid image format (must be 'P3')\n");
        exit(1);
    }

    //alloc memory form image
    img = (PPMImage*)malloc(sizeof(PPMImage));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n') ;
        c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
        exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgbCompColor) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
        exit(1);
    }

    //check rgb component depth
    if (rgbCompColor!= RGBCOMPONENTCOLOR) {
        fprintf(stderr, "'%s' does not have correct color components\n", filename);
        exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
        fprintf(stderr, "Error loading image '%s'\n", filename);
        exit(1);
    }

    fclose(fp);
    return img;
}


void PPM::writePPM(const char *filename, PPMImage *img)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P3\n");

    //image size
    fprintf(fp, "%d %d\n",img->x, img->y);

    // rgb component depth
    fprintf(fp, "%d\n", RGBCOMPONENTCOLOR);

    // pixel data
    fwrite(img->data, 3 * img->x, img->x * img->y, fp);
    fclose(fp);
}

void PPM::changeColorPPM(PPMImage *img)
{
    if(img) {
        for(int i = 0 ; i < img->x * img->y; i++){
            PPMPixel originalData = img->data[i];
            img->data[i].red = originalData.blue;
            img->data[i].green = originalData.red;
            img->data[i].blue = originalData.green;
        }
    }
}