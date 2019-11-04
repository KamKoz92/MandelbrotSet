#include "Fractal.h"
#include "Bitmap.h"
#include "Screen.h"
#include <complex>
#include <iostream>
#include <memory>
#include <math.h>
#include "Zoom.h"
#include <vector>

using namespace std;

Fractal::Fractal(int width, int height):color(0), xFractal(0), yFractal(0), WIDTH(width), HEIGHT(height)
{
}
Fractal::~Fractal()
{
}
int Fractal::getIterations(double x, double y)
{
    complex<double> z = 0;
    complex<double> c(x, y);

    int iterations = 0;

    while (iterations < MAX_ITERATIONS)
    {
        z = z * z + c;
        iterations++;
        if (abs(z) > 2)
        {
            break;
        }
    }
    return iterations;
}
void Fractal::createFractal()
{
    Screen screen(WIDTH,HEIGHT);
    if (screen.init() == false)
    {
        cout << "SDL initialization failed." << endl;
    }
    bool flag = false;
    SDL_Event event;
    int x{0}, y{0};
    bool buttonL = false;
    bool buttonR = false;
    zoomIn(WIDTH/2, HEIGHT/2 , 4.0/ WIDTH); //standard view base parameters
    calculateFractal(screen);
    screen.update();
    cout << "Normal view." << endl;
    while (!flag)
    {
        if(buttonL == true)
        {
            cout << "Zooming In!." << endl;
            zoomIn(x,y,0.5);
            calculateFractal(screen);
            screen.update();
            cout << "Zooming In Done!." <<endl;
            buttonL = false;
        }
        if(buttonR == true)
        {
            if(m_scale < 4.0/ WIDTH)
            {
                cout << "Zooming Out!." << endl;
                zoomOut();
                calculateFractal(screen);
                screen.update();
                cout << "Zooming Out Done!." << endl;    
            }
            else
            {
                cout << "Maximum Zoom Out!." << endl;           
            }
            buttonR = false;
        }


        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                flag = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    x = event.button.x;
                    y = event.button.y;
                    buttonL = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    buttonR = true;
                    break;      
                default:
                    break; 
                }
            }
        }
    }
    screen.close();
}
void Fractal::zoomIn(int xx, int yy, double scale)
{
    xCenter += (xx - WIDTH/2)*m_scale;
    yCenter += (yy - HEIGHT/2)*m_scale;
    m_scale *= scale; 
    zoomList.push_back(Zoom(xCenter,yCenter,m_scale));
    //cout << xCenter << ", " << yCenter << ", " << m_scale << endl; debugg
}
void Fractal::zoomOut()
{
    zoomList.pop_back();
    Zoom temp = zoomList.back();
    xCenter = temp.x;
    yCenter = temp.y;
    m_scale = temp.scale;
    //cout << xCenter << ", " << yCenter << ", " << m_scale << endl; debug
}

void Fractal::calculateFractal(Screen &screen)
{
    unique_ptr<int[]> histogram(new int[MAX_ITERATIONS]{0});
    unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{0});
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            xFractal = (x - WIDTH/2)*m_scale + xCenter;
            yFractal = (y - HEIGHT/2)*m_scale + yCenter;

            int iterations = getIterations(xFractal, yFractal);
            fractal[y * WIDTH + x] = iterations;

            if (iterations != MAX_ITERATIONS)
            {
                histogram[iterations]++;
            }
        }
    }
    int total = 0;
    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        total += histogram[i];
    }
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            uint8_t color = 0;
            int iterations = fractal[y * WIDTH + x];

            if (iterations != MAX_ITERATIONS)
            {
                double hue = 0.0;
                for (int i = 0; i <= iterations; i++)
                {
                    hue += ((double)histogram[i]) / total;
                }
                color = pow(255,hue);
            }
            screen.setPixel(x, y, 0, color, 0);
        }
    }
}