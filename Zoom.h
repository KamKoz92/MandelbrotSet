#ifndef ZOOM_H_
#define ZOOM_H_

class Zoom
{
public:
    Zoom(double x, double y, double scale):x(x),y(y),scale(scale)
    {
    }
    double x{0};
    double y{0};
    double scale{0};
};

#endif /* ZOOM_H_*/