#include <iostream>
#include <SDL2\SDL.h>
#include "Fractal.h"

using namespace std;

int main(int argc, char *argv[])
{
    int const WIDTH = 800;
    int const HEIGHT = 600;
    Fractal fractal(WIDTH,HEIGHT);
    fractal.createFractal();
    return 0;
}