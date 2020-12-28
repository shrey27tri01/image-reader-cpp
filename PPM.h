#ifndef PPM_H

typedef struct {
    unsigned char red, green, blue;
} PPMPixel;

typedef struct {
    int x, y;
    PPMPixel *data;
} PPMImage;

class PPM {
    public:
        static PPMImage *readPPM(const char *filename);
        void writePPM(const char *filename, PPMImage *img);
        void changeColorPPM(PPMImage *img);
};

#endif