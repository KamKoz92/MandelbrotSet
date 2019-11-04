#ifndef FRACTAL_H_
#define FRACTAL_H_
#include "Bitmap.h"
#include <iostream>
#include <vector>
#include "Zoom.h"
#include "Screen.h"

class Fractal
{
public:
    static const int MAX_ITERATIONS = 1000;    
private:
    // Bitmap bitmap;
    uint8_t color;
    double xFractal, yFractal;
    int WIDTH, HEIGHT;
    double xCenter{0}, yCenter{0}, m_scale{1.0};
    vector<Zoom> zoomList;

public:
    Fractal(int width, int height);
    ~Fractal();
    static int getIterations(double x, double y);
    void createFractal();
    void zoomIn(int xx, int yy, double scale);
    void zoomOut();
    void calculateFractal(Screen &screen);
};
#endif /* FRACTAL_H_ */